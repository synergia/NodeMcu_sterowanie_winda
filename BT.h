#pragma once
#include <SoftwareSerial.h>

boolean NL = false;
String sygnal_BT;
SoftwareSerial mySerial(D3, D4); //rx, tx
char a='z';

String inputString = "";
boolean stringComplete = false;

void ustaw_BT() {
	mySerial.begin(38400);
}
void mySerialEvent() {
    while (mySerial.available()) {
        // get the new byte:
        char inChar = (char)mySerial.read();
        // add it to the inputString:
        inputString += inChar;
        // if the incoming character is a newline, set a flag so the main loop can
        // do something about it:
        if (inChar == '\n' || inChar == 32) {
            stringComplete = true;
        }
    }
    Serial.println(inputString[0]);
}
void mruganie()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
}
void odczyt_BT() {
    /*
    while (mySerial.available()) {
        Serial.print((char)mySerial.read());
        sygnal_BT += (char)(mySerial.read());
        Serial.println(" ");
        Serial.println("Otrzymany sygnal:");
        Serial.println(sygnal_BT);
    }
    */
    if (mySerial.available()) {
        while (mySerial.available()) {
           // Serial.print((char)mySerial.read());
            sygnal_BT += (char)(mySerial.read());
        }
        Serial.println(" ");
        Serial.println("Otrzymany sygnal:");
        Serial.println(sygnal_BT);
        sygnal_BT.clear();
    }

    //Serial.println("Otrzymany sygnal:");
    //Serial.println(sygnal_BT);
}

