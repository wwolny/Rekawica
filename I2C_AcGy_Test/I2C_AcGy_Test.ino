/**
 * Adruino wysyła accelX, accelY, accelZ do processingu i laserów
 * Kiedy przycisk jest wciśnięty to wysyłamy sygnał z kątem o jaki się obraca, 
 * żeby obrócić widok.
 * Kiedy puszczamy przycisk wysyłamy dalej ostatnie wartości odczytane przy wciśniętym przecisku.
 * Potrzebuje 3 zmiennych, na które nakładam poprawki ciągle sa to outRot(X/Y/Z)
 */

#include<Wire.h>
#define MPU 0x68
#define MPU_2G (0<<4)
#define MPU_4G (1<<4)
#define MPU_8G (2<<4)
#define MPU_16G (3<<4)
#define TAX (1<<7)
#define TAY (1<<6)
#define TAZ (1<<5)

long  accelX,   accelY,   accelZ;
float gForceX,  gForceY,  gForceZ;
long  gyroX,    gyroY,    gyroZ;
float rotX,     rotY,     rotZ;
float outRotX,  outRotY,  outRotZ; //Info o obrocie, trzeba dodać sygnał 

bool readingAngel; // Sprawdza czy zeminiamy kąt

void setup(){
  Serial.begin(115200);
  Wire.begin();
  setupMPU();
  outRotX = 0;
  outRotY= 0;
  outRotZ = 0;
  readingAngel = true;
}

void loop(){
  recordAccelRegisters();
  recordGyroRegisters();
  printData();
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
  if(readingAngel){
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
  Serial.print("GyroStatic (deg)");
  Serial.print(" X=");
  Serial.print(outRotX);
  Serial.print(" Y=");
  Serial.print(outRotY);
  Serial.print(" Z=");
  Serial.print(outRotZ);
  Serial.print("Gyro (deg)");
  Serial.print(" X=");
  Serial.print(rotX);
  Serial.print(" Y=");
  Serial.print(rotY);
  Serial.print(" Z=");
  Serial.print(rotZ);
  Serial.print(" Accel (g)");
  Serial.print(" X=");
  Serial.print(gForceX);
  Serial.print(" Y=");
  Serial.print(gForceY);
  Serial.print(" Z=");
  Serial.println(gForceZ);
}
