#pragma once

#define BT_rx D5
#define BT_tx D6

String sygnal_BT;
SoftwareSerial BTSerial(BT_rx, BT_tx);

void sterowanie_winda_BT() {
    int i;
    String pietro;
    if (sygnal_BT == String("take_lift")) Serial.println("Przywolanie windy");
    else {
        for (i = 0; i < 8; i++) {
            pietro = String("set") + String(i);
            //Serial.println(pietro);
            if (sygnal_BT == pietro) {
                Serial.print("Wybrano pietro ");
                Serial.println(i);
            }
        }

    }
}
void sprawdzanie_bufora_BT() {
    if (BTSerial.available()) {

        sygnal_BT = BTSerial.readString();
        status = true;
        //Serial.println(sygnal_BT);
       // Serial.println(sygnal_BT.length());
        sygnal_BT.remove((sygnal_BT.length() - 2), 2);
        Serial.println(sygnal_BT);
        Serial.println(sygnal_BT.length());
        sterowanie_winda_BT();
    }
}
void setup_BT() {
    BTSerial.begin(34800);
}

/*
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

ICACHE_RAM_ATTR void odczyt_BT() {
    
    while (mySerial.available()) {
        Serial.print((char)mySerial.read());
        sygnal_BT += (char)(mySerial.read());
        Serial.println(" ");
        Serial.println("Otrzymany sygnal:");
        Serial.println(sygnal_BT);
    }
    
    if (mySerial.available()) {
        while (mySerial.available()) {
           // Serial.print((char)mySerial.read());
            sygnal_BT += (char)(mySerial.read());
        }
        Serial.println(" ");
        Serial.println("Otrzymany sygnal:");
        Serial.println(sygnal_BT);
        sygnal_BT.clear();
        status = true;
    }

    //Serial.println("Otrzymany sygnal:");
    //Serial.println(sygnal_BT);
}
*/
