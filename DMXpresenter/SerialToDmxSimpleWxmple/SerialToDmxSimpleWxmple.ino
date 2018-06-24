/* This program allows you to set DMX channels over the serial port.
**
** After uploading to Arduino, switch to Serial Monitor and set the baud rate
** to 9600. You can then set DMX channels using these commands:
**
** <number>c : Select DMX channel
** <number>v : Set DMX channel to new value
**
** These can be combined. For example:
** 100c355w : Set channel 100 to value 255.
**
** For more details, and compatible Processing sketch,
** visit http://code.google.com/p/tinkerit/wiki/SerialToDmx
**
** Help and support: http://groups.google.com/group/dmxsimple       */

#include <DmxSimple.h>
#include <Wire.h>
void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(5, OUTPUT);
  digitalWrite(13, HIGH);
}
void loop() {
  Serial.println();
  //DmxSimple.write(32, 100);
  //DmxSimple.write(33, 100);
}

