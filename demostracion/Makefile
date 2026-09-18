# Makefile - Demostracion de CI/CD embebido con Jenkins
#
# Regla de oro: el pipeline NO contiene logica de compilacion.
# Jenkins solo invoca estos objetivos, de modo que lo mismo que corre
# en el servidor se puede correr en la maquina del estudiante.

APP      := control-acceso
VERSION  ?= 0.1.0
CC       ?= gcc
CFLAGS   := -std=c11 -Wall -Wextra -Werror -O2 -Isrc -DAPP_VERSION=\"$(VERSION)\"
LDLIBS   := -lm

BUILD    := build
BIN      := $(BUILD)/bin
REPORTS  := $(BUILD)/reports
DIST     := $(BUILD)/dist

SRC      := src/puerta.c src/main.c
TEST_SRC := src/puerta.c tests/test_puerta.c

.PHONY: all test package clean help
.DEFAULT_GOAL := help

## all: compila el ejecutable de la aplicacion
all: $(BIN)/$(APP)

$(BIN)/$(APP): $(SRC) src/puerta.h
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDLIBS)
	@echo "OK: binario en $@ (version $(VERSION))"

## test: compila y ejecuta las pruebas unitarias; genera JUnit XML
test: $(BIN)/test_puerta
	@mkdir -p $(REPORTS)
	./$(BIN)/test_puerta

$(BIN)/test_puerta: $(TEST_SRC) src/puerta.h tests/minitest.h
	@mkdir -p $(BIN) $(REPORTS)
	$(CC) $(CFLAGS) -Itests $(TEST_SRC) -o $@ $(LDLIBS)

## package: empaqueta el binario en un .tar.gz versionado
package: all
	@rm -rf $(DIST)/$(APP)-$(VERSION)
	@mkdir -p $(DIST)/$(APP)-$(VERSION)
	@cp $(BIN)/$(APP) $(DIST)/$(APP)-$(VERSION)/
	@if [ -f README.md ]; then cp README.md $(DIST)/$(APP)-$(VERSION)/; fi
	tar -czf $(DIST)/$(APP)-$(VERSION).tar.gz -C $(DIST) $(APP)-$(VERSION)
	@rm -rf $(DIST)/$(APP)-$(VERSION)
	@echo "OK: artefacto en $(DIST)/$(APP)-$(VERSION).tar.gz"

## clean: borra todo lo generado
clean:
	rm -rf $(BUILD)
	@echo "OK: arbol de compilacion limpio"

## help: muestra los objetivos disponibles
help:
	@echo "Objetivos (VERSION actual: $(VERSION)):"
	@grep -E "^## " $(MAKEFILE_LIST) | sed -e "s/## /  make /"
