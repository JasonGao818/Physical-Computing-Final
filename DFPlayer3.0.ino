//Ultrasonic sensor control Mp3 module part is mine.Other part is my teammate's.
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
int TrigPin = 8;
int EchoPin = 9;
int LedPin = 12;
int LedPin1 = 13;
int val;
SoftwareSerial mySerial(10, 11);
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(LedPin, OUTPUT);
  pinMode(LedPin1, OUTPUT);
}
void loop()
{
 // static unsigned long timer = millis();

  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  int cm = pulseIn(EchoPin, HIGH) / 20.0;
  cm = (int(cm * 100.0)) / 100.0;
  Serial.println(cm);
  Serial.println("cm");
  delay(50);
  if (40 >= cm)
  {
    digitalWrite(LedPin, HIGH);
    digitalWrite(LedPin1, HIGH);
//    timer = millis();
    myDFPlayer.play(1);  //Play next mp3 every 3 second.
    delay(1000);
//    if (myDFPlayer.available()) {
//      printDetail(myDFPlayer.readType(), myDFPlayer.read()); 
//
//    }
  }
  digitalWrite(LedPin, LOW);
  digitalWrite(LedPin1, LOW);
}

void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
