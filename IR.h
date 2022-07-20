#pragma once
//https://html.alldatasheet.com/html-pdf/199976/VISHAY/TSOP31138/218/1/TSOP31138.html
#define IR_pin_odbieranie D3
uint32_t sygnal_IR;

#define przywolanie_windy 3810328320
#define pietro1 3125149440
#define pietro2 3108437760
#define pietro3 3091726080
#define pietro4 3141861120
#define pietro5 3208707840
#define pietro6 3158572800
#define pietro7 4161273600



void sterownie_winda_IR() {
    switch (sygnal_IR)
    {
    case pietro1:
        Serial.println("Ustawiono pietro 1");
        break;
    case pietro2:
        Serial.println("Ustawiono pietro 2");
        break;
    case pietro3:
        Serial.println("Ustawiono pietro 3");
        break;
    case pietro4:
        Serial.println("Ustawiono pietro 4");
        break;
    case pietro5:
        Serial.println("Ustawiono pietro 5");
        break;
    case pietro6:
        Serial.println("Ustawiono pietro 6");
        break;
    case pietro7:
        Serial.println("Ustawiono pietro 7");
        break;
    case przywolanie_windy:
        Serial.println("Przywolanie windy");
        break;
    default:
        Serial.println("blad IR");
        break;
    }
}
ICACHE_RAM_ATTR void odebranie() {
    if (IrReceiver.decode()) {
        sygnal_IR = IrReceiver.decodedIRData.decodedRawData;
        Serial.println();
        Serial.print("od IrReceiver:");
        IrReceiver.printIRResultMinimal(&Serial);
        Serial.println();
        Serial.print("od sygnal_IR:");
        Serial.println(sygnal_IR, DEC);
        IrReceiver.resume();
        status = true;

        sterownie_winda_IR();
    }

}
void setup_IR() {
    IrReceiver.begin(IR_pin_odbieranie);
    delay(100);
    pinMode(IR_pin_odbieranie, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(IR_pin_odbieranie), odebranie, RISING);
    delay(100);
}

/*
//PINy NodeMcu
#define pin_wysylanie D0
#define pin_odbieranie D1

//sygnal z pilota
#define pietro_1 0xFFA25D
#define pietro_2 0xFF629D
#define pietro_3 0xFFE21D
#define pietro_4 0xFF22DD
#define pietro_5 0xFF02FD
#define pietro_6 0xFFC23D
#define pietro_7 0xFFE01F
#define pietro_8 0xFFA857
#define wywolanie_windy_dol 0xFF4AB5
#define wywolanie_windy_gora 0xFF18E7

//klasa i atrybuty odbierania
IRrecv odbieranie(pin_odbieranie);
decode_results sygnal_IR;
unsigned long wczesniejszy_sygnal = 0;

void wlaczenie_odbierania() {
    odbieranie.enableIRIn();
    odbieranie.blink13(true);
}
void odbieranie_sygnalu() {
    decode_results temp;

    if (odbieranie.decode(&temp)) {
        if (temp.value == 0xFFFFFFFF) {
            Serial.println("sygnal powtorzony");
            temp.value = wczesniejszy_sygnal;
        }

        Serial.println(sygnal_IR.value, HEX);

        wczesniejszy_sygnal = temp.value;
        sygnal_IR = temp;

        odbieranie.resume();
    }
}

void wysylanie_sygnalu(uint32_t temp) {
    IrSender.begin(pin_wysylanie, true, LED_BUILTIN);
    IrSender.sendNEC(temp, 32);
}

void pisanie() {
	//Serial.println("dziala?");
}
*/