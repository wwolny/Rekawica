#include<Wire.h>
#define MPU 0x68
#define MPU_2G (0<<4)
#define MPU_4G (1<<4)
#define MPU_8G (2<<4)
#define MPU_16G (3<<4)

const float VCC = 4.98;
const float R_DIV = 47500.0;
const float STRAIGHT_RESISTANCE = 37300.0;//ZLE OPORY!!!!!!
const float BEND_RESISTANCE = 90000.0;//ZLE OPORY, bo dla 3,3kOhm

long  accelX,   accelY,   accelZ;
float gForceX,  gForceY,  gForceZ;
long  gyroX,    gyroY,    gyroZ;
float rotX,     rotY,     rotZ;
float outRotX=0,  outRotY=0,  outRotZ=0; //Info o obrocie, trzeba dodać sygnał 
int  sensorA0;
float flexV;
float flexR;

bool readingAngle; // Sprawdza czy zmieniamy kąt

const int sensorL = A0;    //first flex
const int sensorR = A1;    // select the pin for the LED

void setup(){
  Serial.begin(230400);
  Wire.begin();
  pinMode(sensorL,INPUT);
  setupMPU();/*
  outRotX = 0;
  outRotY= 0;
  outRotZ = 0;*/
  readingAngle = false;
}

void loop(){
  Serial.print("sensorVal = ");
  sensorA0 = analogRead(sensorL);
  Serial.println(sensorA0);
  flexV = sensorA0*VCC/1023.0;
  flexR = R_DIV * (VCC / flexV - 1.0);
  Serial.println( map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 90.0));
  if(sensorA0<700) { //fleks na A0 uruchamia sterowanie układem odniesienia
    readingAngle = true;
  }else {
    readingAngle = false;
  }/*
  if(analogRead(sensorR)>300) { //fleks na A1 zeruje rotację układu
    outRotX = 0.0;
    outRotY = 0.0;
    outRotZ = 0.0;
  }*/
  recordAccelRegisters();
  recordGyroRegisters();
  printData();
  //Serial.print(analogRead(sensorL)); //narzędzie debugujące
  delay(20);
}

void setupMPU() {
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU);
  Wire.write(0x1B); 
  Wire.write(0x00); 
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU);
  Wire.write(0x1C); 
  Wire.write(0x00); 
  Wire.endTransmission(true);
}

void recordAccelRegisters() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(MPU,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processAccelData();
}

void processAccelData(){
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0; 
  gForceZ = accelZ / 16384.0;
}

void recordGyroRegisters() {
  Wire.beginTransmission(MPU);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(MPU,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); 
  gyroY = Wire.read()<<8|Wire.read(); 
  gyroZ = Wire.read()<<8|Wire.read(); 
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
  rotX *= 0.0174532925;
  rotY *= 0.0174532925;
  rotZ *= 0.0174532925;
  if(readingAngle){
    outRotX += rotX;
    outRotY += rotY;
    outRotZ += rotZ;
    if(outRotX >= 6.28318530718)
      outRotX-=6.28318530718;
    if(outRotY >= 6.28318530718)
      outRotY-=6.28318530718;
    if(outRotZ >= 6.28318530718)
      outRotZ-=6.28318530718;
    if(outRotX <= -6.28318530718)
      outRotX+=6.28318530718;
    if(outRotY <= -6.28318530718)
      outRotY+=6.28318530718;
    if(outRotZ <= -6.28318530718)
      outRotZ+=6.28318530718;
  }
}

void printData() {
  Serial.print("accX= ");
  Serial.println(accelX-603);
  Serial.print("accY= ");
  Serial.println(accelY+371);
  Serial.print("accZ= ");
  Serial.println(accelZ+2267);
  Serial.print("RotX= ");
  Serial.println(outRotX/5.0);
  Serial.print("RotY= ");
  Serial.println(outRotY/5.0);
  Serial.print("RotZ= ");
  Serial.println(outRotZ/5.0);
}
