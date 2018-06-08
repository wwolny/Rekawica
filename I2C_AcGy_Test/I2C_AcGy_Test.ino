/**
 * Adruino wysyła Ax, Ay, Az do processingu i laserów
 * Kiedy przycisk jest wciśnięty to wysyłamy sygnał z kątem o jaki się obraca, 
 * żeby obrócić widok.
 * Kiedy puszczamy przycisk wysyłamy dalej ostatnie wartości odczytane przy wciśniętym przecisku.
 * Potrzebuje 3 zmiennych, na które nakładam poprawki ciągle 
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

void setup(){
  Serial.begin(115200);
  Wire.begin();
  setupMPU();
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
  Wire.beginTransmission(MPU); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(MPU,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
}

void printData() {
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
