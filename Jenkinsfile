// Jenkinsfile - Pipeline declarativo de la demostracion
//
// Regla de oro: este archivo NO contiene logica de compilacion.
// Solo orquesta: invoca objetivos del Makefile, que el estudiante
// puede ejecutar igual en su maquina sin Jenkins.

pipeline {

    agent any

    options {
        timestamps()                       // marca de tiempo en cada linea
        timeout(time: 10, unit: "MINUTES") // corta un build colgado
        buildDiscarder(logRotator(numToKeepStr: "10"))
        disableConcurrentBuilds()          // un build a la vez
    }

    environment {
        VERSION = "0.1.${BUILD_NUMBER}"    // trazabilidad del artefacto
    }

    stages {

        stage("Preparar") {
            steps {
                echo "Construyendo version ${VERSION}"
                sh "make clean"
                sh "gcc --version | head -1"
            }
        }

        stage("Compilar") {
            steps {
                sh "make all VERSION=${VERSION}"
            }
        }

        stage("Probar") {
            steps {
                // catchError: una prueba fallida deja el build AMARILLO
                // (UNSTABLE), no rojo. Distingue "fallo de codigo" de
                // "fallo de infraestructura".
                catchError(buildResult: "UNSTABLE", stageResult: "UNSTABLE") {
                    sh "make test VERSION=${VERSION}"
                }
            }
            post {
                always {
                    junit allowEmptyResults: true,
                          testResults: "build/reports/*.xml"
                }
            }
        }

        stage("Empaquetar") {
            // Solo se empaqueta si las pruebas pasaron: no se publica
            // un artefacto que no supero la verificacion.
            when {
                expression { currentBuild.result == null ||
                             currentBuild.result == "SUCCESS" }
            }
            steps {
                sh "make package VERSION=${VERSION}"
            }
        }

        stage("Entregar") {
            when {
                expression { currentBuild.result == null ||
                             currentBuild.result == "SUCCESS" }
            }
            steps {
                archiveArtifacts artifacts: "build/dist/*.tar.gz",
                                 fingerprint: true
            }
        }

    }

    post {
        success   { echo "SUCCESS: artefacto ${VERSION} listo para entrega" }
        unstable  { echo "UNSTABLE: compilo, pero fallaron pruebas" }
        failure   { echo "FAILURE: revise la consola" }
        always    { cleanWs() }
    }

}
