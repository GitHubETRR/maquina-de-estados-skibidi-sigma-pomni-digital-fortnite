#line 1 "C:\\Users\\lgiuliano\\OneDrive\\Lenguajes\\C\\extra\\mef\\README.md"
# MEF Anti-Rebote para pulsadores

Implementar una **MEF anti-rebote** que permita leer el estado del pulsador con un Arduino y generar acciones o eventos ante un flanco descendente o ascendente, de acuerdo con el siguiente diagrama:

![Mapa de estado de Mealy](./design/maquina_estado.png)

### Código a respetar:

El estado inicial de la MEF debe ser BUTTON_UP.

Implementar las funciones:

```
void debounceFSM_init();		// debe cargar el estado inicial
void debounceFSM_update();	// debe leer las entradas, resolver la lógica de
					// transición de estados y actualizar las salidas
void buttonPressed();			// debe invertir el estado del LED1
void buttonReleased();		// debe invertir el estado del LED2
```

El tiempo de anti-rebote debe ser de 40 ms con un retardo no bloqueante

La función debounceFSM_update() debe llamarse periódicamente.

```
typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
} debounceState_t;
```