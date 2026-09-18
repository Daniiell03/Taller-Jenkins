/*
 * puerta.c - Implementacion de la maquina de estados.
 * Demostracion de CI/CD embebido con Jenkins.
 */
#include "puerta.h"
#include <stddef.h>

void puerta_init(puerta_t *p)
{
    if (p == NULL) {
        return;
    }
    p->estado   = EST_CERRADO;
    p->intentos = 0u;
}

estado_t puerta_evento(puerta_t *p, evento_t ev)
{
    if (p == NULL) {
        return EST_BLOQUEADO;   /* falla segura */
    }

    switch (p->estado) {

    case EST_CERRADO:
        if (ev == EV_CREDENCIAL) {
            p->estado = EST_AUTORIZANDO;
        }
        break;

    case EST_AUTORIZANDO:
        if (ev == EV_OK) {
            p->estado   = EST_ABIERTO;
            p->intentos = 0u;           /* exito: se reinicia el contador */
        } else if (ev == EV_FALLO) {
            p->intentos++;
            p->estado = (p->intentos >= MAX_INTENTOS)
                      ? EST_BLOQUEADO
                      : EST_CERRADO;
        }
        break;

    case EST_ABIERTO:
        if (ev == EV_TIEMPO) {
            p->estado = EST_CERRADO;    /* cierre automatico */
        }
        break;

    case EST_BLOQUEADO:
    default:
        /* Estado terminal: solo se sale reinicializando el modulo. */
        break;
    }

    return p->estado;
}

const char *puerta_nombre(estado_t e)
{
    switch (e) {
    case EST_CERRADO:     return "CERRADO";
    case EST_AUTORIZANDO: return "AUTORIZANDO";
    case EST_ABIERTO:     return "ABIERTO";
    case EST_BLOQUEADO:   return "BLOQUEADO";
    default:              return "DESCONOCIDO";
    }
}
