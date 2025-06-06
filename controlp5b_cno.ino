#include <Controllino.h>

typedef enum {
  ESTADO_A_VERDE,     // Semáforo A en verde, B en rojo
  ESTADO_A_AMARILLO,  // Semáforo A en amarillo, B en rojo
  ESTADO_B_VERDE,     // Semáforo B en verde, A en rojo
  ESTADO_B_AMARILLO   // Semáforo B en amarillo, A en rojo
} EstadoSemaforo_t;

// Estructura para un semáforo
typedef struct {
  uint8_t pinRojo;
  uint8_t pinAmarillo;
  uint8_t pinVerde;
} Semaforo_t;

// Pines asignados
// Semáforo A: rojo-0, amarillo-1, verde-2
// Semáforo B: rojo-6, amarillo-7, verde-8
const Semaforo_t semA = {CONTROLLINO_D0, CONTROLLINO_D1, CONTROLLINO_D2};
const Semaforo_t semB = {CONTROLLINO_D6, CONTROLLINO_D7, CONTROLLINO_D8};

// Tiempos de cada fase (ms)
const unsigned long TIEMPO_VERDE   = 5000;  // 5 s
const unsigned long TIEMPO_AMARILLO =  1000;  //  1 s

// Variables de la ME
EstadoSemaforo_t estadoActual = ESTADO_A_VERDE;
unsigned long     tiempoAnterior = 0;
  
void setup() {
  // Configura los pines de ambos semáforos
  pinMode(semA.pinRojo,     OUTPUT);
  pinMode(semA.pinAmarillo, OUTPUT);
  pinMode(semA.pinVerde,    OUTPUT);
  pinMode(semB.pinRojo,     OUTPUT);
  pinMode(semB.pinAmarillo, OUTPUT);
  pinMode(semB.pinVerde,    OUTPUT);
  // Inicializa todo 
  digitalWrite(semA.pinRojo,     LOW);
  digitalWrite(semA.pinAmarillo, LOW);
  digitalWrite(semA.pinVerde,    LOW);
  digitalWrite(semB.pinRojo,     LOW);
  digitalWrite(semB.pinAmarillo, LOW);
  digitalWrite(semB.pinVerde,    LOW);
  tiempoAnterior = millis();
}

void loop() {
  unsigned long ahora = millis();
  switch (estadoActual) {
    
    case ESTADO_A_VERDE:
      // A verde, B rojo
      digitalWrite(semA.pinVerde, HIGH);
      digitalWrite(semA.pinAmarillo, LOW);
      digitalWrite(semA.pinRojo, LOW);
      digitalWrite(semB.pinRojo, HIGH);
      digitalWrite(semB.pinAmarillo, LOW);
      digitalWrite(semB.pinVerde, LOW);
      // Transición tras TIEMPO_VERDE
      if (ahora - tiempoAnterior >= TIEMPO_VERDE) {
        estadoActual   = ESTADO_A_AMARILLO;
        tiempoAnterior = ahora;
      }
      break;
    
    case ESTADO_A_AMARILLO:
      // A amarillo, B rojo
      digitalWrite(semA.pinVerde, LOW);
      digitalWrite(semA.pinAmarillo, HIGH);
      digitalWrite(semA.pinRojo, LOW);
      digitalWrite(semB.pinRojo, HIGH);
      digitalWrite(semB.pinAmarillo, LOW);
      digitalWrite(semB.pinVerde, LOW);
      // Transición tras TIEMPO_AMARILLO
      if (ahora - tiempoAnterior >= TIEMPO_AMARILLO) {
        estadoActual   = ESTADO_B_VERDE;
        tiempoAnterior = ahora;
      }
      break;
    
    case ESTADO_B_VERDE:
      // B verde, A rojo
      digitalWrite(semB.pinVerde, HIGH);
      digitalWrite(semB.pinAmarillo, LOW);
      digitalWrite(semB.pinRojo, LOW);
      digitalWrite(semA.pinRojo, HIGH);
      digitalWrite(semA.pinAmarillo, LOW);
      digitalWrite(semA.pinVerde, LOW);
      // Transición tras TIEMPO_VERDE
      if (ahora - tiempoAnterior >= TIEMPO_VERDE) {
        estadoActual   = ESTADO_B_AMARILLO;
        tiempoAnterior = ahora;
      }
      break;
    
    case ESTADO_B_AMARILLO:
      // B amarillo, A rojo
      digitalWrite(semB.pinVerde, LOW);
      digitalWrite(semB.pinAmarillo, HIGH);
      digitalWrite(semB.pinRojo, LOW);
      digitalWrite(semA.pinRojo, HIGH);
      digitalWrite(semA.pinAmarillo, LOW);
      digitalWrite(semA.pinVerde, LOW);
      // Transición tras TIEMPO_AMARILLO
      if (ahora - tiempoAnterior >= TIEMPO_AMARILLO) {
        estadoActual   = ESTADO_A_VERDE;
        tiempoAnterior = ahora;
      }
      break;
  }
}
