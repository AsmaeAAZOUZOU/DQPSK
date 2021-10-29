#include <iostream>
#include <wiringPi.h>
using namespace std;

int ledPin = 29;  //Correspond à la pin 40

void setup(){

pinMode(ledPin,OUTPUT);

}

void turn_PA(int8_t n){
    if (n==1){
        digitalWrite(ledPin,HIGH);
        cout << "PA is on" << endl;}
    else if (n==0){
    digitalWrite(ledPin,LOW);
    cout << "PA is off" << endl;}

}

// control the power amplifier (ON if argv[1] = 1, else it's OFF )
int main(int argc, char* argv[])
{
	if(wiringPiSetup()<0){
	cout<<"setup wiring pi failed"<<endl;
	return 1;
	}
	setup();
	turn_PA(stoi(argv[1]));
	

return 0;
}
