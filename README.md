# Taller de Jenkins

Bienvenido al repositorio del Taller de Jenkins. Este proyecto está diseñado para introducir y poner en práctica los conceptos fundamentales de Integración Continua (CI) y automatización utilizando Jenkins, Docker y herramientas de construcción.

## Estructura del Repositorio

El repositorio está organizado para separar el material de guía del entorno de práctica, facilitando así el flujo de la clase:

```text
minitaller-jenkins/
├── index.html            <- Guía web del taller (se publica en GitHub Pages).
├── demostracion/         <- Código y configuraciones mostradas en clase por el expositor.
│   ├── docker/
│   ├── src/
│   ├── tests/
│   ├── Jenkinsfile
│   └── Makefile
├── taller-estudiantes/   <- Material base que descargan los estudiantes.
│   ├── docker/           <- Dockerfile, compose y lista de complementos.
│   ├── src/              <- credencial.h (contrato), credencial.c (esqueleto), main.c
│   ├── tests/            <- minitest.h y la prueba de ejemplo
│   ├── Jenkinsfile
│   ├── Makefile
│   ├── guia.html         <- Copia local de la guía, por si falla la red.
│   └── .gitignore
└── README.md
```

## Requisitos Previos
Para participar en este taller, asegúrate de tener instalado y configurado lo siguiente en tu entorno local:

## Requisitos Previos

* WSL2 con Ubuntu 22.04 o superior, o Linux nativo. También sirve macOS con Docker Desktop.
* Docker Engine 24 o superior con Compose v2.
* Git.
* `gcc`, `make`, `nano` y `cppcheck` en el sistema anfitrión.
* Puerto 8080 libre.
* Cuenta de GitHub con un **token de acceso personal tipo _classic_** y alcance `repo`.

No hace falta instalar Jenkins: corre dentro de un contenedor construido a partir del
`Dockerfile` incluido. La imagen oficial no trae compilador de C, por eso el taller
provee uno propio que sí lo incluye.

```bash
sudo apt update
sudo apt install -y build-essential make git curl zip unzip nano cppcheck
```

## Dinámica del Taller
El taller está diseñado para ejecutarse en dos fases:

### 1. Fase de Demostración (Directorio demostracion/)
En esta etapa, el instructor utilizará los archivos dentro de la carpeta `demostracion/` para mostrar cómo funciona un flujo completo de CI/CD. Se explicará paso a paso la estructura del Jenkinsfile, cómo se integran las pruebas y cómo se construye la imagen de Docker utilizando el Makefile.

### 2. Fase Práctica (Directorio taller-estudiantes/)

Los estudiantes trabajan **en parejas**, identificados como A y B. Cada uno ejecuta su
propio Jenkins, pero ambos publican al mismo repositorio: esa es la situación que la
integración continua existe para resolver.

El proyecto es un **validador de credenciales** en C. El material entrega el contrato
(`credencial.h`) y un esqueleto de implementación que compila pero no hace nada, de modo
que el primer build sale en amarillo y hay algo concreto que arreglar.

**Lo que construyen:**

| Ronda | Integrante A | Integrante B |
|---|---|---|
| 1 | Implementa `cred_formato_valido` y `cred_checksum` | Escribe las pruebas de ambas |
| 2 | Escribe las pruebas de `cred_autorizar` | Implementa `cred_autorizar` |

Cada ronda se trabaja en una rama propia, se publica como *pull request* y se revisa
cruzado antes de fusionar.

**Además del código, el taller cubre:**

* Levantar Jenkins en un contenedor con el entorno de construcción incluido.
* Conectar el pipeline a GitHub mediante *Pipeline script from SCM*.
* Distinguir un build rojo (no compiló) de uno amarillo (compiló, falló una prueba).
* Comprobar que una rama de trabajo no genera artefacto y `main` sí.
* Provocar y resolver un conflicto de fusión.
* Agregar una etapa de análisis estático al `Jenkinsfile` y publicarla por *pull request*.
* Romper el build a propósito y observar la reacción del pipeline.

**Cómo empezar:**

```bash
cd ~
git clone https://github.com/Daniiell03/Taller-Jenkins.git material-taller
mkdir -p ~/validador-ci
cp -r ~/material-taller/taller-estudiantes/. ~/validador-ci/
rm -rf ~/material-taller
cd ~/validador-ci
```

El resto está en la guía, paso por paso y con todos los comandos.

## Guía del taller

La guía completa, con comandos copiables y seguimiento de avance, está en:

**https://daniiell03.github.io/Taller-Jenkins/**

También viaja como `taller-estudiantes/guia.html` dentro del material descargado, por si
falla la red del aula.

## Recursos Adicionales

* Preguntas iniciales: https://wordwall.net/resource/119393396?wwmethod=link
* Cuestionario final: https://es.educaplay.com/recursos-educativos/30654575-cuestionario_ci_cd_en_sistemas_embebidos.html
