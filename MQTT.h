#pragma once
/*
 Name:		mqtt1.ino
 Created:	6/16/2022 6:37:30 PM
 Author:	wojci
*/
/*/
https://pubsubclient.knolleary.net/
https://c2plabs.com/blog/2022/01/02/esp8266-mqtt-client-tutorial-using-pubsubclient-library/
https://github.com/knolleary/pubsubclient/blob/master/LICENSE.txt
*/
// the setup function runs once when you press reset or power the board


//#include <ESP8266WiFi.h>
//#include <PubSubClient.h>


// Update these with values suitable for your network.

const char* ssid = "NameOfNetwork";
const char* password = "niemampomyslunahaslo";
const char* mqtt_server = "mqtt.local";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
#define ilosc_pieter 10
char msg[MSG_BUFFER_SIZE];
int value = 0;

String received_message;

void setup_wifi() {

    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");

        sprawdzanie_bufora_BT();
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
void test_mruganie(int ilosc) {
    int i;
        for (i = 1; i <= ilosc; i++) {
            digitalWrite(LED_BUILTIN, LOW);
            delay(750);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(500);
        }
}
void test_take_lift() {
    
        digitalWrite(LED_BUILTIN, LOW);
        delay(1500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1500);
    
}
void sterowanie_winda_MQTT() {
    int i = -2;
    int wybor = 0;

    if (received_message == String("call")) {
       // test_take_lift();
        moveServo(przywolanie_dol_serwo);
        Serial.println("Przywilanie windy");
    }
    else {
        while (i < ilosc_pieter) {
            if (received_message == String(i)) {
                moveServo(i+2);
                test_mruganie(i);
                Serial.println("Wybranie pietra");
                break;
            }
            i++;
        }
    }
    /*
    while (i < 10) {
        if (received_message = (char)i) {
            wybor = i;
        }
    }

    switch (wybor)
    {
    case 1:
        Serial.println("Wybranie pietra 1");
        //tutaj w kazdym funkcja przekodowywania danych
        //moveServo(0);
        break;
    case 2:
        Serial.println("Wybranie pietra 2");
        //moveServo(1);

        break;
    case 3:
        Serial.println("Wybranie pietra 3");


        break;
    case 4:
        Serial.println("Wybranie pietra 4");


        break;
    case 5:
        Serial.println("Wybranie pietra 5");

        break;
    case 0:
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
    */
}
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        //Serial.print((char)payload[i]);
        received_message += (char)payload[i];
        Serial.print(received_message[i]);
    }
    Serial.println();

 
    if (strcmp(topic, "/lift/status") == 0) {
        Serial.println("Sprawdzenie statusu polaczenia MQTT");
        BTSerial.write("Sprawdzenie statusu polaczenia MQTT");
        client.publish("/B5/lift/", "ok");
    }
    if (strcmp(topic, "/lift/floor0") == 0) {
        sterowanie_winda_MQTT();
    }
    received_message.clear();
    /*
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        received_message += (char)payload[i];
        Serial.print(received_message[i]);
    }
    Serial.println();

    if (topic == "B5/lift/check") {
        client.publish("B5/lift/check", "ok");
    }
    if (topic == "B5/lift") {
        sterowanie_winda_MQTT();
    }
    */
    /*
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1') {
        digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
        // but actually the LED is on; this is because
        // it is active low on the ESP-01)
    }
    else {
        digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
    }
    if ((char)payload[0] == 'o') {
        digitalWrite(led, HIGH);
        delay(1000);
        digitalWrite(led, LOW);
        delay(1000);
    }
    */
}
void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str())) {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.publish("outTopic", "hello world");
            // ... and resubscribe
            client.subscribe("inTopic");
            client.subscribe("/lift/status");
            client.subscribe("/lift/floor0");
        }
        else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
           
        }
    }
}
/*
void mqtt() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    unsigned long now = millis();
    if (now - lastMsg > 2000) {
        lastMsg = now;
        ++value;
        //snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
        //Serial.print("Publish message: ");
        //Serial.println(msg);
        //client.publish("outTopic", msg);
    }
    
    /*
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    unsigned long now = millis();
    if (now - lastMsg > 2000) {
        lastMsg = now;
        ++value;
        snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
        Serial.print("Publish message: ");
        Serial.println(msg);
        client.publish("outTopic", msg);
    }
    
}
*/
/*
void setup() {
    pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop() {

    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    unsigned long now = millis();
    if (now - lastMsg > 2000) {
        lastMsg = now;
        ++value;
        snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
        Serial.print("Publish message: ");
        Serial.println(msg);
        client.publish("outTopic", msg);
    }
}
*/