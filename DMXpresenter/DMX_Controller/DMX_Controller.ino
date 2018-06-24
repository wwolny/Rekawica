#include <DMXSerial.h>

int tmp;
 
void setup() {
  DMXSerial.init(DMXController);
  //Serial.begin(9600);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);//init for USART
  delay(2000);
  DMXSerial.write(1,222); //Sterowanie Auto100/SD/Manual(222+
  delay(100);
  //DMXSerial.write(2, 100);//Wzorki
  tmp = 0;
} // setup


// loop through the rainbow colors 
void loop() { 
  if(tmp >254) { 
    tmp=0;
  }
  tmp++;
  delay(100);
  DMXSerial.write(2, tmp);//WZORKI tmp wszytskie//AUTO:100 losowe wzorki geometryczne
  delay(100);
  DMXSerial.write(3, 0);//flashing 0 //AUTO: 
  //SZYBKOSC
  DMXSerial.write(4, 0);//Moving X
  delay(100);
  DMXSerial.write(5, 0);//Moving Y
  delay(100);
  DMXSerial.write(6, 30);//Zoom - 30
  delay(100);
  DMXSerial.write(7, 0);//rozplywanie sie X
  delay(100);
  DMXSerial.write(8, 0);//rozplywanie sie Y
  delay(100);
  DMXSerial.write(9, 0);//rozplywanie sie Z
  delay(100);
  DMXSerial.write(10, 100);//size100
  delay(100);
  DMXSerial.write(11, 0);//falowanie
  delay(100);
  DMXSerial.write(12, 0);//color50
  delay(1000);//delay 1000
} // loop
