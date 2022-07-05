/*
 Name:		NodeMcu_sterowanie_winda.ino
 Created:	6/28/2022 10:02:38 PM
 Author:	wojci
*/
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <IRremote.hpp>

#define led D1

#include "BT.h"
#include "IR.h"
#include "MQTT.h"
#include "Sterowanie_Servo.h"


const int RECV_PIN = D0;
IRrecv irrecv(RECV_PIN);
decode_results results;
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
    
    mySerial.begin(38400);

    //wlaczenie_odbierania();
    //Serial.println("Wlaczenie IR");
    pwm.begin();
    pwm.setOscillatorFrequency(27000000); //PCA9685 chip is a range between about 23-27MHz
    pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
    //MQTT
    //setup_wifi();
    //client.setServer(mqtt_server, 1883);
    //client.setCallback(callback);

	pinMode(LED_BUILTIN, OUTPUT);
    pinMode(led, OUTPUT);
   // irrecv.enableIRIn();
    //irrecv.blink13(true);

    delay(250);
    Serial.println("Rozpoczecie programu");
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);

}

// the loop function runs over and over again until power down or reset
void loop() {
    //odczyt_BT();
    //mqtt();
    //odbieranie_sygnalu();
    /*
    if (irrecv.decode(&results)) {
        Serial.println(results.value, HEX);
        irrecv.resume();
    }
    */
    digitalWrite(LED_BUILTIN, HIGH);
    moveServo(0);
    digitalWrite(LED_BUILTIN, LOW);
    delay(2000);
    //sprawdzenie czy dziala
}
/*
void sterowanie_winda() {

    switch (sygnal_IR.value)
    {
    case pietro_1:
        Serial.println("Wybranie pietra 1");
        //tutaj w kazdym funkcja przekodowywania danych
        //moveServo(0);
        break;
    case pietro_2:
        Serial.println("Wybranie pietra 2");
        //moveServo(1);

        break;
    case pietro_3:
        Serial.println("Wybranie pietra 3");


        break;
    case pietro_4:
        Serial.println("Wybranie pietra 4");


        break;
    case pietro_5:
        Serial.println("Wybranie pietra 5");

        break;
    case wywolanie_windy_gora:
        Serial.println("Wywolanie windy gora");
        // wywolanie_windy(sygnal);
        //moveServo(servonum);
        break;
    case wywolanie_windy_dol:
        Serial.println("Wywolanie windy dol");
        // wywolanie_windy(sygnal);
        break;


    default:
        Serial.println("coœ nie pyklo");
        break;
    }
}
*/
