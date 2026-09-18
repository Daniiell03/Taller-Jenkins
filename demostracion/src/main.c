/*
 * main.c - Demostracion de consola de la maquina de estados.
 * Este ejecutable es el producto que el pipeline compila y empaqueta.
 */
#include <stdio.h>
#include "puerta.h"

#ifndef APP_VERSION
#define APP_VERSION "0.0.0-dev"
#endif

static const char *nombre_evento(evento_t ev)
{
    switch (ev) {
    case EV_CREDENCIAL: return "CREDENCIAL";
    case EV_OK:         return "OK";
    case EV_FALLO:      return "FALLO";
    case EV_TIEMPO:     return "TIEMPO";
    default:            return "?";
    }
}

int main(void)
{
    /* Secuencia: dos intentos fallidos, luego uno correcto. */
    const evento_t guion[] = {
        EV_CREDENCIAL, EV_FALLO,
        EV_CREDENCIAL, EV_FALLO,
        EV_CREDENCIAL, EV_OK,
        EV_TIEMPO
    };
    const size_t n = sizeof(guion) / sizeof(guion[0]);
    puerta_t p;
    size_t i;

    printf("control-acceso %s\n", APP_VERSION);
    printf("Maquina de estados de puerta (bloqueo tras %u fallos)\n\n",
           (unsigned)MAX_INTENTOS);
    printf("  %-12s | %-12s | %s\n", "evento", "estado", "intentos");
    printf("  -------------+--------------+---------\n");

    puerta_init(&p);
    for (i = 0u; i < n; ++i) {
        estado_t e = puerta_evento(&p, guion[i]);
        printf("  %-12s | %-12s | %u\n",
               nombre_evento(guion[i]), puerta_nombre(e),
               (unsigned)p.intentos);
    }

    printf("\nEstado final: %s\n", puerta_nombre(p.estado));
    return 0;
}
