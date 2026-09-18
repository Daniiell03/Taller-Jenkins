# Dockerfile - Controlador de Jenkins con entorno de compilacion en C
#
# La imagen oficial de Jenkins trae Java y el servidor, pero NO trae
# compilador. Si el pipeline va a ejecutar "make", el entorno de
# construccion tiene que existir en la imagen.

FROM jenkins/jenkins:lts-jdk21

# Las instalaciones de paquetes requieren privilegios de root.
USER root

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      build-essential \
      make \
      file \
      cppcheck \
 && rm -rf /var/lib/apt/lists/*

# Zona horaria de la JVM: las marcas de tiempo del log en hora local.
ENV JAVA_OPTS="-Duser.timezone=America/Costa_Rica -Djenkins.install.runSetupWizard=true"

# Plugins precargados: evita depender de la red del aula.
COPY plugins.txt /usr/share/jenkins/ref/plugins.txt
RUN jenkins-plugin-cli --plugin-file /usr/share/jenkins/ref/plugins.txt

# Se vuelve al usuario sin privilegios para ejecutar el servicio.
USER jenkins
