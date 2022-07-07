#pragma once
//https://html.alldatasheet.com/html-pdf/199976/VISHAY/TSOP31138/218/1/TSOP31138.html

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
/*
void wysylanie_sygnalu(uint32_t temp) {
    IrSender.begin(pin_wysylanie, true, LED_BUILTIN);
    IrSender.sendNEC(temp, 32);
}
*/
void pisanie() {
	//Serial.println("dziala?");
}