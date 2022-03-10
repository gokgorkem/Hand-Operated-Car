#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
const int motorIN1 = 3; // L298N IN1 Girişi
const int motorIN2 = 4; // L298N IN2 Girişi
const int motorIN3 = 5; // L298N IN3 Girişi
const int motorIN4 = 6; // L298N IN4 Girişi
int xdeger;
int ydeger;
struct veri_paketi {
  int xEkseni;
  int yEkseni;
};
veri_paketi veri;
RF24 radio(7,8); // CE, CSN
const byte address[6] = "00001";
void setup() {
  pinMode(motorIN1, OUTPUT);
  pinMode(motorIN2, OUTPUT);
  pinMode(motorIN3, OUTPUT);
  pinMode(motorIN4, OUTPUT);
  Serial.begin(9600);
  veri.xEkseni = 0;
  veri.yEkseni = 0;
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    radio.read(&veri, sizeof(veri_paketi));
    Serial.print("X Map Değeri : ");
    Serial.print(veri.xEkseni);
    Serial.print("\t");
    Serial.print("Y Map Değeri : ");
    Serial.println(veri.yEkseni);
    xdeger = veri.xEkseni;
    ydeger = veri.yEkseni;
 
    xdeger = xdeger >= 50 ? xdeger : xdeger <= -50 ? xdeger : 0;
    ydeger = ydeger >= 50 ? ydeger : ydeger <= -50 ? ydeger : 0;
      Serial.print(xdeger);
      Serial.print("\t");
      Serial.println(ydeger);
    if (xdeger<-50 && ydeger < 100 && ydeger >-100) {
      xdeger = abs(xdeger);                           //ileri
      analogWrite(motorIN1, xdeger); 
      analogWrite(motorIN2, 0);
      analogWrite(motorIN3, xdeger); 
      analogWrite(motorIN4, 0);
}
    else if (xdeger > 50 && ydeger < 100 && ydeger >-100) { //geri
      analogWrite(motorIN1, 0); 
      analogWrite(motorIN2, xdeger);
      analogWrite(motorIN3, 0); 
      analogWrite(motorIN4, xdeger);
}
    else if (ydeger <-50 && xdeger < 100 && xdeger >-100) { //sola dönme
      ydeger = abs(ydeger);
      analogWrite(motorIN1, ydeger); 
      analogWrite(motorIN2, 0);
      analogWrite(motorIN3, 0); 
      analogWrite(motorIN4, 0);
}
    else if (ydeger >50 && xdeger < 100 && xdeger >-100) { //sağa dönme
      analogWrite(motorIN1, 0); 
      analogWrite(motorIN2, 0);
      analogWrite(motorIN3, ydeger); 
      analogWrite(motorIN4, 0);
}
    else  {
      analogWrite(motorIN1, 0); 
      analogWrite(motorIN2, 0);
      analogWrite(motorIN3, 0); 
      analogWrite(motorIN4, 0);
}}
}
