%% Emmissiant de l'identifiant du club radio F6KQH
close all;
clear;
%% Parametres 
%Tp = 2*57e-3;     % durée d'un point
Tp = 0.1254;     % durée d'un point
Tem = 2e-4;     % période d'échantillonnage 
Ft = Tp/Tem;
% Durée du point : 1pt 
% Durée du trait : 3pt
% Espacement entre 2 signes : 1pt 
% Espacement entre 2 lettres : 3 pt 
% Espacement entre 2 mots : 7pt

f0=1e3;
%f0=1255000000;

%% vecteurs des caracères de l'identifiant
e_F = [ones(1,Ft) zeros(1,Ft) ones(1,Ft) zeros(1,Ft) ones(1,3*Ft) zeros(1,Ft) ones(1,Ft)];  % F en code morse ··−· 
e_6 = [ones(1,3*Ft) zeros(1,Ft) ones(1,Ft) zeros(1,Ft) ones(1,Ft) zeros(1,Ft) ones(1,Ft) zeros(1,Ft) ones(1,Ft)]; % 6 en code morse −····
e_K = [ones(1,3*Ft) zeros(1,Ft) ones(1,Ft) zeros(1,Ft) ones(1,3*Ft)]; % K en code morse   −·− 
e_Q = [ones(1,3*Ft) zeros(1,Ft) ones(1,3*Ft) zeros(1,Ft) ones(1,Ft) zeros(1,Ft) ones(1,3*Ft)]; % K en code morse −−·−
e_H = [ones(1,Ft) zeros(1,Ft) ones(1,Ft) zeros(1,Ft) ones(1,Ft) zeros(1,Ft) ones(1,Ft)];  % H en code morse ···· 

%% vecteur du premier mot de l'identifiant
e_F6KQH = [e_F zeros(1,3*Ft) e_6 zeros(1,3*Ft) e_K zeros(1,3*Ft) e_Q zeros(1,3*Ft) e_H];

%% vecteur de l'identifiant
vect_Identifiant = [e_F6KQH zeros(1,7*Ft) e_F6KQH];
vect_Ident = 127.*vect_Identifiant;
vect_Identifiant_audible = vect_Identifiant.*cos(2*pi*f0*[0:length(vect_Identifiant)-1]*Tem);

soundsc(vect_Identifiant_audible,1/Tem);

filename = 'F6KQH.wav';
audiowrite(filename,vect_Identifiant_audible,1/Tem);

%% Enregistrement de l'identifiant
fid = fopen('Identifiant.raw', 'w');
fwrite(fid,int8(vect_Ident),'int8');
fclose(fid);

