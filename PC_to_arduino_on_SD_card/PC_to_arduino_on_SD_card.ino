#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h> // Solve problem with SPI library missing?

// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)

SoftwareSerial XBee(2, 3); // RX, TX
File myFile;

void setup()
{
  XBee.begin(9600);
  Serial.begin(9600);
  
  pinMode(10, OUTPUT);
  
  if(!SD.begin(4)) {
    Serial.println("SD init failed!");
  }
  
  myFile = SD.open("prop2.txt", FILE_WRITE);
}

void loop()
{
  char c;
  
  if (XBee.available()) {
    c = XBee.read();
    if (c != 'z') {
        Serial.print(c);
        Serial.print("");
        if (myFile) {
          myFile.print(c);
        } else {
          Serial.print("File not opened.");
        }
    } else {
      myFile.close();
      Serial.print("File closed.");
    }
  }
}
