%% RÃ©cepteur pi/4-DQPSK/QPSK avec prÃ©-synchronisation temporelle et frÃ©quentielle 
clear all, clc, close all;

%% ParamÃ¨tres 
%Te=2*1e-7; % temps d'Ã©chantillonnage des CNA et CAN
Ts=2e-6; % temps symbole
Fse = 6;
Te = Ts/Fse;
nb = 2; % nombre de bits/symbole
fe=1/Te;
Ds=1/Ts; % dÃ©bit symbole
Db=nb*Ds; % dÃ©bit binaire
M=2^nb;
rows = 400; columns = 600;
Nb=rows*columns*8*3;
%Fse=floor(Ts/Te); % facteur de sous-echantillonnage
f0=1.255e9; % porteuse pour le calcul du PL
seuil=0.76;
Ptx = 1; % Puissance d'Ã©mission (W)
roll_off=0.8;
A=127;
Nb_paquets=48;
Octet_verif = hexToBinaryVector('0xAA');
len_filter = 49;
n_conv = (((Nb+Nb_paquets*length(Octet_verif))/2/Nb_paquets)+3)*Fse+len_filter;


%% Modes de rÃ©ception

thetaInit = pi/4; % Theta initial pour le mode diffÃ©rentiel
ssd_Ts_1 = exp(1i*thetaInit); % premier symbol pilote pour correction de phase donc s_b(1:2) = [0 0]
Nfft=4096;


%% PrÃ©ambule 
preambule = [ones(1,Fse) zeros(1,Fse) ones(1,Fse) zeros(1,2*Fse) ones(1,Fse) zeros(1,Fse) ones(1,Fse) zeros(1,4*Fse-1)];
preambule = repmat(preambule,1,2); % repmat() : rÃ©pÃ¨te le motif de la matrice prÃ©ambule sur une fois en ligne et deux fois en colonne
Ep = sum(preambule.^2); %Ã©nergie de la sÃ©quence de prÃ©ambule

%% Filtre adaptÃ©

g=rcosdesign(roll_off,2*M, Fse, 'sqrt');
ga = conj(fliplr(g)); % ga(t) = g(Ts-t) (le retard de Ts est implicite en numÃ©rique car on travaille avec des vecteurs causaux)

%% Acquisition des donnÃ©es du rÃ©cepteur 
fileID = fopen('QPSK_Tx.raw','r');
rl=fread(fileID,'int8=>double');
fclose(fileID);

rl_I=rl(1:2:end);
rl_Q=rl(2:2:end);
yl_Te=transpose(rl_I+1j*rl_Q);


% % Canal
k = 1.38e-23; % Cte Boltzmann
T = 273.15 + 25; % TempÃ©rature bruit du rÃ©cepteurans
N0 = k*T;
varb = N0/2;
s=yl_Te;
tau0=1000*rand;
%tau0=1;
tau0=floor(tau0); %retard dÃ» Ã  la propagation
alpha0 = sqrt(1e-8);  % coefficient d'attÃ©nuation du canal
h_l = alpha0*[zeros(1,tau0) 1]; %dirac dÃ©calÃ© de tau0*Te
Ps = 1/Te*mean(abs(s).^2);
yl_Te = sqrt(Ptx/Ps)*yl_Te/127;
y = conv(yl_Te,h_l); % signal en sortie du canal

%% Recepteur
Deltaf = 50e-6*f0*2*(rand-0.5); % erreur de frÃ©quence OL prÃ©cis Ã  +-50ppm , 2*(rand-0.5)=nombre alÃ©atoire dans l'intervalle [-1,1]
%Deltaf = 0;
n = sqrt(varb/2)*(randn(1,length(y))+1i*randn(1,length(y)));
yl = y.*exp(1i*2*pi*[0:length(y)-1]*Te*Deltaf+1i*pi/8)+n ;
yl_Te=yl;

%% Recepteur
yl_Te = yl_Te./norm(yl_Te); %% normalisation : utile ? => sÃ»rement pour faire l'intercorrÃ©lation entre le prÃ©ambule et le prÃ©ambule reÃ§u
test=yl_Te;

%% fonction d'interrcorrélation
rho=filter(fliplr(preambule),1,abs(yl_Te))./(sqrt(Ep)*sqrt(...
    filter(ones(1,length(preambule)),1,abs(yl_Te).^2)));
figure, plot(rho),
title("fonction d'intercorrélation")
xlabel('Nombre d''échantillons')
ylabel ('ρ(u)')
%% Pré-synchronisation temporelle 
rl_Ts_conc=0;
for k=1:Nb_paquets %pb qui vient de la synchro tps
    disp(k);
    rho=filter(fliplr(preambule),1,abs(yl_Te))./(sqrt(Ep)*sqrt(...
    filter(ones(1,length(preambule)),1,abs(yl_Te).^2)));
    i=1;
    while i < length(rho)
        if rho(i)> seuil
            indice = i;
            break
        end
        i=i+1;    
    end
    temp =[];   
    ind =[];

    for j=indice:indice+n_conv
        if rho(j)> seuil
            temp = [temp,rho(j)];
            ind = [ind,j];
        end
    end

    M=max(temp);
    indSynch = ind(find(temp==M));    
    %disp(indSynch);
    %disp(M);
%     %Verification des indices de synchro
%     rho=filter(fliplr(preambule),1,abs(yl_Te))./(sqrt(Ep)*sqrt(...
%     filter(ones(1,length(preambule)),1,abs(yl_Te).^2)));
% 
%     figure, plot(rho)
%     hold on,
%     plot(indSynch,M,'r*')
%     title("fonction d'intercorrélation"),
%     xlabel('temps')   
    if (indSynch+((Nb+Nb_paquets*length(Octet_verif))/2/Nb_paquets+2)*Fse)>length(yl_Te)
                yl_Te_synch = yl_Te(indSynch:end);  
                yl_Te(indSynch-length(preambule)+1:end)=[];
    else
        yl_Te_synch = yl_Te(indSynch:indSynch+((Nb+Nb_paquets*length(Octet_verif))/2/Nb_paquets+2)*Fse+length(ga));
        yl_Te(indSynch-length(preambule)+1:indSynch-length(preambule)+1+((Nb+Nb_paquets*length(Octet_verif))/2/Nb_paquets+2)*Fse+length(ga)-1)=[];

    end
    

    %% SÃ©lection du message utile
          [Rl_Te, f] = pwelch(yl_Te_synch.^8, ones(1,Nfft), 0, Nfft, fe, 'centered');
          %figure, pwelch(yl_Te_synch.^8, ones(1,Nfft), 0, Nfft, fe, 'centered');
          [~, indice] = max(Rl_Te);
          f0_8_esti = f(indice)/8;
          disp(f0_8_esti);
          yl_Te_synch=exp(-1j*(2*pi*f0_8_esti*(0:length(yl_Te_synch)-1)*Te)).*yl_Te_synch;
          %% Filtre adaptÃ©
          rl_Te = conv(yl_Te_synch,ga);  % convolution par le filtre adpatÃ©
          rl_Ts=rl_Te(length(ga)+1:Fse:length(ga)+((Nb+Nb_paquets*length(Octet_verif))/2/Nb_paquets+1)*Fse+1); % sous echantillonnage au rythme Fse (correspond Ã  un Ã©chantillonnage de r_l(t) au rythme Ts)
          % PrÃ©-synchronisation frÃ©quentielle tant que 2pi*Nb*f_erreur<pi/4
          Phase_correction =(angle(ssd_Ts_1)-angle(rl_Ts(1)));
          rl_Ts = rl_Ts*exp(1i*Phase_correction);
          rl_Ts = rl_Ts(3:end)./(rl_Ts(2:end-1));
          rl_Ts=rl_Ts./max(abs(rl_Ts));
          %disp(Phase_correction);      
          rl_Ts_conc=[rl_Ts_conc, rl_Ts];
          %figure, plot(rl_Ts,'*');

end  

%% DÃ©modulateur numÃ©rique
rl_Ts_conc=rl_Ts_conc(2:end);
figure, plot(rl_Ts,'*');
title('Constellation I/Q de r_{l}[n]')
xlabel('I')
ylabel ('Q')
sb_esti = zeros(1,(Nb+Nb_paquets*length(Octet_verif)));
sb_esti(2:2:end) = real(rl_Ts_conc)<0;
sb_esti(1:2:end) = imag(rl_Ts_conc)<0;
%% Verification de l'octet AA
octet = zeros(8,Nb_paquets);

for i=1:Nb_paquets    
    octet(:,i) = sb_esti(1+(i-1)*length(Octet_verif)+(i-1)*Nb/Nb_paquets:i*length(Octet_verif)+(i-1)*Nb/Nb_paquets);
end
%disp(sb_esti(1:8));
%% Supression de l'octet AA
for j = Nb_paquets:-1:1     
    sb_esti(1+(j-1)*length(Octet_verif)+(j-1)*Nb/Nb_paquets :j*length(Octet_verif)+(j-1)*Nb/Nb_paquets )=[];      
end



%% Enrengistrement

for i=0:length(sb_esti)/8 -1
   pixel_8(i+1) =  bin2dec(dec2bin(sb_esti(1+8*i:8+8*i))'); 

end

I_rgb = reshape(pixel_8,3,[]);
I_rgb = I_rgb';
I_r = reshape(I_rgb(:,1),rows,columns);
I_g = reshape(I_rgb(:,2),rows,columns);
I_b = reshape(I_rgb(:,3),rows,columns);


I = cat(3,I_r,I_g,I_b);
figure, imshow(uint8(I))

%% Filtrage méridian 
for c = 1 : 3
    I(:, :, c) = medfilt2(I(:, :, c), [3, 3]);
end
figure; imshow(uint8(I));


%% BER
sb=load("sb.mat","sb_Te");
sb=sb.sb_Te;
[n,r]=biterr(sb,sb_esti);

% Constellation I/Q
subplot 142
scatter(real(test),...
        imag(test),'.');
grid on
title('Constellation I/Q de rl_{Te}[n]')
xlabel('I')
ylabel ('Q')
subplot 144
scatter(real(rl_Ts_conc),...
        imag(rl_Ts_conc),'o');
grid on
title('Constellation I/Q de r_{l}[n]')
xlabel('I')
ylabel ('Q')