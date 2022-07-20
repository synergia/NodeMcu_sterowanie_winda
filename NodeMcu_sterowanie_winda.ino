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

//#define led D1
volatile bool status = false;

#include "BT.h"
#include "IR.h"
#include "MQTT.h"
#include "Sterowanie_Servo.h"



// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
    setup_BT();
    setup_IR();
	pinMode(LED_BUILTIN, OUTPUT);
    delay(100);
    Serial.println("Rozpoczecie programu");
    
   // pwm.begin();
   // pwm.setOscillatorFrequency(27000000); //PCA9685 chip is a range between about 23-27MHz
   // pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
    //MQTT
    //setup_wifi();
    //client.setServer(mqtt_server, 1883);
   // client.setCallback(callback);
    //set_sub_pub_mqtt();

}

// the loop function runs over and over again until power down or reset
void loop(){
    
    sprawdzanie_bufora_BT();
    if (status) {
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200);
        status = false;
    }
}
