/*
 * puerta.h - Maquina de estados de una puerta con control de acceso.
 * Demostracion de CI/CD embebido con Jenkins.
 *
 * El modulo es puro: sin hardware ni E/S, de modo que las pruebas
 * pueden ejecutarse dentro del contenedor de Jenkins.
 */
#ifndef PUERTA_H
#define PUERTA_H

#include <stdint.h>

#define MAX_INTENTOS 2u   /* bloqueo tras este numero de fallos */

typedef enum {
    EST_CERRADO = 0,
    EST_AUTORIZANDO,
    EST_ABIERTO,
    EST_BLOQUEADO
} estado_t;

typedef enum {
    EV_CREDENCIAL = 0,
    EV_OK,
    EV_FALLO,
    EV_TIEMPO
} evento_t;

typedef struct {
    estado_t estado;
    uint8_t  intentos;
} puerta_t;

/* Inicializa la maquina en estado CERRADO y sin intentos fallidos. */
void puerta_init(puerta_t *p);

/* Procesa un evento y devuelve el estado resultante.
   Un evento no valido para el estado actual lo deja sin cambios. */
estado_t puerta_evento(puerta_t *p, evento_t ev);

/* Nombre legible del estado, para trazas. */
const char *puerta_nombre(estado_t e);

#endif /* PUERTA_H */
