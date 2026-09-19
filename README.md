# Taller de Jenkins

Bienvenido al repositorio del Taller de Jenkins. Este proyecto está diseñado para introducir y poner en práctica los conceptos fundamentales de Integración Continua (CI) y automatización utilizando Jenkins, Docker y herramientas de construcción.

## Estructura del Repositorio

El repositorio está organizado para separar el material de guía del entorno de práctica, facilitando así el flujo de la clase:

```text
minitaller-jenkins/
├── demostracion/         <- Código y configuraciones mostradas en clase por el instructor.
│   ├── docker/
│   ├── src/
│   ├── tests/
│   ├── Jenkinsfile
│   └── Makefile
├── taller-estudiantes/   <- Entorno de trabajo base para que los estudiantes desarrollen la práctica.
│   ├── docker/
│   ├── src/
│   ├── tests/
│   ├── Jenkinsfile
│   ├── Makefile
│   └── .gitignore
├── docs/                 <- Documentación de referencia, presentaciones y guías adicionales.
└── README.md
```

## Requisitos Previos
Para participar en este taller, asegúrate de tener instalado y configurado lo siguiente en tu entorno local:

* Git
* Docker (y Docker Compose)
* Acceso a una instancia de Jenkins (local o remota) con permisos para crear y ejecutar pipelines.
* Herramienta make instalada.

## Dinámica del Taller
El taller está diseñado para ejecutarse en dos fases:

### 1. Fase de Demostración (Directorio demostracion/)
En esta etapa, el instructor utilizará los archivos dentro de la carpeta `demostracion/` para mostrar cómo funciona un flujo completo de CI/CD. Se explicará paso a paso la estructura del Jenkinsfile, cómo se integran las pruebas y cómo se construye la imagen de Docker utilizando el Makefile.

### 2. Fase Práctica (Directorio taller-estudiantes/)
Los estudiantes trabajarán dentro de la carpeta `taller-estudiantes/`. 
El objetivo es que se logre completar el Jenkinsfile y las configuraciones necesarias para que el pipeline pase exitosamente por todas sus etapas (Build, Test, y Dockerize).

**Pasos para estudiantes:**

1. Haz un fork o clona este repositorio.
2. Navega al directorio `taller-estudiantes/`.
3. Revisa los archivos fuente y los tests.
4. Completa el Jenkinsfile siguiendo las instrucciones dadas en clase o en la carpeta `docs/`.
5. Ejecuta el pipeline en tu instancia de Jenkins y verifica los resultados.

## Recursos Adicionales
Puedes encontrar material de apoyo, diagramas de arquitectura y guías paso a paso dentro del directorio `docs/`.
Link para preguntas iniciales: https://wordwall.net/resource/119393396?wwmethod=link
Preguntas finales del taller: https://es.educaplay.com/recursos-educativos/30654575-cuestionario_ci_cd_en_sistemas_embebidos.html
