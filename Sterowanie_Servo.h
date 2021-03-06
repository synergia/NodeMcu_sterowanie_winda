#pragma once
//skarbnica wiedzy https://diyi0t.com/servo-motor-tutorial-for-arduino-and-esp8266/
#define przywolanie_dol_serwo 0
#define przywolanie_gora_serwo 1
#define parter_serwo 2
#define pietro1_serwo 3
#define pietro2_serwo 4
#define pietro3_serwo 5




// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter

uint8_t servonum = 0; //numer serwa
uint16_t pulselen = 250; //pulselenght

void moveServo(uint8_t servonum) {
    Serial.println("serwo");
    Serial.println(servonum);
    Serial.println("serwo1");
    uint16_t pulselen = 250; //dlugosc impulsu
    for (pulselen = 250; pulselen < 500; pulselen++) {
        pwm.setPWM(servonum, 0, pulselen);
        delay(10);
        Serial.println("serwo10");
        Serial.println(pulselen);
    }

    delay(100);

    for (pulselen = 500; pulselen > 250; pulselen--) {
        pwm.setPWM(servonum, 0, pulselen);
        delay(10);
        Serial.println("serwo11");
        Serial.println(pulselen);
    }
    Serial.println("serwo2");
    return;
}
void setServoPulse(uint8_t n, double pulse) {
    double pulselength;

    pulselength = 1000000;   // 1,000,000 us per second
    pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
    Serial.print(pulselength); Serial.println(" us per period");
    pulselength /= 4096;  // 12 bits of resolution
    Serial.print(pulselength); Serial.println(" us per bit");
    pulse *= 1000000;  // convert input seconds to us
    pulse /= pulselength;
    Serial.println(pulse);
    pwm.setPWM(n, 0, pulse);
}