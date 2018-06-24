#include <DMXSerial.h>

int tmp;
 
void setup() {
  DMXSerial.init(DMXController);
  //Serial.begin(9600);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);//init for USART
  delay(2000);
  DMXSerial.write(1,222);
  delay(100);
  DMXSerial.write(2, 200);
  tmp = 0;
  //DMXSerial.write(0,0);
} // setup


// loop through the rainbow colors 
void loop() {
 
  if(tmp >254) { 
    tmp=10;
  }
  tmp++;
  delay(100);
  //DMXSerial.write(2, tmp);
  //PATTERN!!!!
  DMXSerial.write(3, 10);
  delay(100);
  //SZYBKOSC
  DMXSerial.write(4, 100);
  delay(100);
  DMXSerial.write(5, tmp);
  delay(100);
  DMXSerial.write(6, 120);//Zoom
  delay(100);
  DMXSerial.write(7, 0);//rozplywanie sie X
  delay(100);
  DMXSerial.write(8, 0);//rozplywanie sie Y
  delay(100);
  DMXSerial.write(9, 0);//rozplywanie sie Z
  delay(100);
  DMXSerial.write(10, 100);//size
  delay(100);
  DMXSerial.write(11, 0);//falowanie
  delay(100);
  DMXSerial.write(12, 50);//color
  
} // loop
/*
 * 
  //ZNACZACY!!!!
  DMXSerial.write(36, 50);
  delay(100);
  //NIEZNACZACY
  //DMXSerial.write(37,100);
  delay(100);
  //NIEZNACZACY
  //DMXSerial.write(38, 100);
  delay(100);
 */

/*
//figura
   *
   * Pattern
   * 1-127 fixed pattern
   * 128-255 clipping Speed
   *
  DMXSerial.write(34, 0);
  delay(100);
  //szybkość
  DMXSerial.write(35, 100);
  delay(100);
  //faza - w szerz
  DMXSerial.write(36,200);
  delay(100);
  ////faza- w gore
  DMXSerial.write(37,100);
  delay(100);
  //przesuniecie
  //DMXSerial.write(38, 100);
  //delay(100);
  
  //DMXSerial.write(36,200);
  //delay(100);
  for(int nn=37;nn<59;nn++){
    delay(1000);
    DMXSerial.write(nn,0);
  }*/

