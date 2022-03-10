#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8); // CE, CSN
const byte address[6] = "00001";

struct veri_paketi {
  int xEkseni;
  int yEkseni;
};
veri_paketi veri;
MPU6050 mpu6050(Wire);
int xdeger;
int ydeger;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  veri.xEkseni = 0;
  veri.yEkseni = 0;
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  mpu6050.update();
  Serial.print("X Açısı : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\t");
  Serial.print("Y Açısı : ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("\t");
  xdeger=mpu6050.getAngleX();
  ydeger=mpu6050.getAngleY();
  xdeger = xdeger >=75 ? 75 : xdeger <=-75 ? -75 : xdeger ;
  ydeger = ydeger >=75 ? 75 : ydeger <=-75 ? -75 : ydeger ;
  veri.xEkseni = map(xdeger,-75,75,-255,255);
  veri.yEkseni= map(ydeger,-75,75,-255,255);
  Serial.print("X Map Değeri : ");
  Serial.print(veri.xEkseni);
  Serial.print("\t");
  Serial.print("Y Map Değeri : ");
  Serial.println(veri.yEkseni);
  radio.write(&veri, sizeof(veri_paketi));
}
