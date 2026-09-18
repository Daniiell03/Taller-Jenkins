/*
 * test_puerta.c - Pruebas unitarias de la maquina de estados.
 * Demostracion de CI/CD embebido con Jenkins.
 */
#include "minitest.h"
#include "puerta.h"

static void test_init_arranca_cerrado(void)
{
    puerta_t p;
    puerta_init(&p);
    MT_ASSERT_EQ(p.estado, EST_CERRADO);
    MT_ASSERT_EQ(p.intentos, 0);
}

static void test_credencial_pasa_a_autorizando(void)
{
    puerta_t p;
    puerta_init(&p);
    MT_ASSERT_EQ(puerta_evento(&p, EV_CREDENCIAL), EST_AUTORIZANDO);
}

static void test_autorizacion_correcta_abre(void)
{
    puerta_t p;
    puerta_init(&p);
    puerta_evento(&p, EV_CREDENCIAL);
    MT_ASSERT_EQ(puerta_evento(&p, EV_OK), EST_ABIERTO);
}

static void test_cierre_por_tiempo(void)
{
    puerta_t p;
    puerta_init(&p);
    puerta_evento(&p, EV_CREDENCIAL);
    puerta_evento(&p, EV_OK);
    MT_ASSERT_EQ(puerta_evento(&p, EV_TIEMPO), EST_CERRADO);
}

static void test_bloqueo_tras_tres_fallos(void)
{
    puerta_t p;
    unsigned i;
    puerta_init(&p);
    /* Dos fallos: vuelve a CERRADO, aun sin bloquear. */
    for (i = 0u; i < 2u; ++i) {
        puerta_evento(&p, EV_CREDENCIAL);
        MT_ASSERT_EQ(puerta_evento(&p, EV_FALLO), EST_CERRADO);
    }
    /* Tercer fallo: bloqueo. */
    puerta_evento(&p, EV_CREDENCIAL);
    MT_ASSERT_EQ(puerta_evento(&p, EV_FALLO), EST_BLOQUEADO);
}

static void test_bloqueado_es_terminal(void)
{
    puerta_t p;
    unsigned i;
    puerta_init(&p);
    for (i = 0u; i < MAX_INTENTOS; ++i) {
        puerta_evento(&p, EV_CREDENCIAL);
        puerta_evento(&p, EV_FALLO);
    }
    /* Ningun evento saca de BLOQUEADO. */
    MT_ASSERT_EQ(puerta_evento(&p, EV_CREDENCIAL), EST_BLOQUEADO);
    MT_ASSERT_EQ(puerta_evento(&p, EV_OK), EST_BLOQUEADO);
}

int main(void)
{
    printf("Pruebas de la maquina de estados de la puerta\n");
    printf("--------------------------------------------\n");

    MT_PRUEBA(test_init_arranca_cerrado);
    MT_PRUEBA(test_credencial_pasa_a_autorizando);
    MT_PRUEBA(test_autorizacion_correcta_abre);
    MT_PRUEBA(test_cierre_por_tiempo);
    MT_PRUEBA(test_bloqueo_tras_tres_fallos);
    MT_PRUEBA(test_bloqueado_es_terminal);

    return mt_informe("build/reports/puerta.xml", "puerta");
}
