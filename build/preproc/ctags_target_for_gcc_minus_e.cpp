# 1 "C:\\Users\\lgiuliano\\OneDrive\\Lenguajes\\C\\extra\\mef\\mef.ino"
# 13 "C:\\Users\\lgiuliano\\OneDrive\\Lenguajes\\C\\extra\\mef\\mef.ino"
unsigned long time; /* Tiempo desde que se prendió el Arduino */

typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RAISING,
}debounceState_t;

debounceState_t buttonState;

void debounceFSM_init(); // debe cargar el estado inicial
void debounceFSM_update(); // debe leer las entradas, resolver la lógica de
                         // transición de estados y actualizar las salidas
debounceState_t buttonPressed(); // debe invertir el estado del LED1
debounceState_t buttonReleased(); // debe invertir el estado del LED2



void setup() {
    pinMode(2 /* Entrada de la señal */, 0x0);

    pinMode(3 /* Salida */, 0x1);
    pinMode(3 /* Led que indica si se presiona el botón */, 0x1);
    pinMode(8 /* Led que indica si se soltó el botón */, 0x1);
    pinMode(5 /* Led que indica algún tipo de error */, 0x1);

    debounceFSM_init();
}

void loop() {
    debounceFSM_update();
}



void debounceFSM_init() { // debe cargar el estado inicial
    digitalWrite(3 /* Led que indica si se presiona el botón */, 0x0);
    digitalWrite(8 /* Led que indica si se soltó el botón */, 0x0);
    digitalWrite(3 /* Salida */, 0x0);

    buttonState = BUTTON_UP;
}

/* 

    Debe leer las entradas, resolver la lógica de

    transición de estados y actualizar las salidas

*/
# 61 "C:\\Users\\lgiuliano\\OneDrive\\Lenguajes\\C\\extra\\mef\\mef.ino"
void debounceFSM_update() {
    switch (buttonState) {

    case BUTTON_UP:
        if(!digitalRead(2 /* Entrada de la señal */) /* Valor digital de la entrada */) break;

        buttonState = BUTTON_FALLING;
        time = millis(); /* Inicia un tiempo para comparar según el DELAY */

        break;

    case BUTTON_FALLING:
        if(millis() - time < 40 /* Retardo para considerar la señal */) break; /* No hace nada si es menor al DELAY */

        buttonState = (digitalRead(2 /* Entrada de la señal */) /* Valor digital de la entrada */) ? buttonPressed() : BUTTON_UP;
        /* En caso de que siga apretado, avanza. Sino, retrocede */

        break;

    case BUTTON_DOWN:
        if(digitalRead(2 /* Entrada de la señal */) /* Valor digital de la entrada */) break;

        buttonState = BUTTON_RAISING;
        time = millis(); /* Inicia un tiempo para comparar según el DELAY */

        break;

    case BUTTON_RAISING:
        if(millis() - time < 40 /* Retardo para considerar la señal */) break; /* No hace nada si es menor al DELAY */

        buttonState = (!digitalRead(2 /* Entrada de la señal */) /* Valor digital de la entrada */) ? buttonReleased() : BUTTON_DOWN;
        /* En caso de que no se aprete, vuelve al estado inicial. Sino, retrocede */

        break;

    default:
        debounceFSM_init();
        digitalWrite(5 /* Led que indica algún tipo de error */, 0x1);
        delay(500);
        digitalWrite(5 /* Led que indica algún tipo de error */, 0x0);

        break;
    }
}

debounceState_t buttonPressed() { // debe invertir el estado del LED1
    digitalWrite(3 /* Led que indica si se presiona el botón */, !digitalRead(3 /* Led que indica si se presiona el botón */));
    digitalWrite(3 /* Salida */, 0x1);

    return BUTTON_DOWN;
}

debounceState_t buttonReleased() { // debe invertir el estado del LED2
    digitalWrite(8 /* Led que indica si se soltó el botón */, !digitalRead(8 /* Led que indica si se soltó el botón */));
    digitalWrite(3 /* Salida */, 0x0);

    return BUTTON_UP;
}
