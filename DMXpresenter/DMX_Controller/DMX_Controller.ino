#include <DMXSerial.h>

int tmp;
 
void setup() {
  DMXSerial.init(DMXController);
  //Serial.begin(9600);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);//init for USART
  delay(2000);
  DMXSerial.write(1,222);//100); //Sterowanie Auto100/SD/Manual(222+
  delay(100);
  DMXSerial.write(2, 100);//Wzorki
  tmp = 0;
} // setup


// loop through the rainbow colors 
void loop() {
 
  if(tmp >254) { 
    tmp=10;
  }
  tmp++;
  delay(100);
  //DMXSerial.write(2, tmp);//WZORKI
  delay(100);
  DMXSerial.write(3, 10);//flashing
  //SZYBKOSC
  DMXSerial.write(4, 100);//Moving X
  delay(100);
  DMXSerial.write(5, 100);//Moving Y
  delay(100);
  DMXSerial.write(6, 30);//Zoom
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
  delay(1000);
} // loop
