APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

# Detecta o sistema operacional
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist "$(1)" mkdir "$(1)"
    RM = if exist "$(1)" del /Q "$(1)"
    EXE = .exe
    RUN_CMD =
else
    MKDIR = mkdir -p $(1)
    RM = rm -f $(1)
    EXE =
    RUN_CMD = ./
endif

# Encontra AUTOMATICAMENTE todos os arquivos .c
SRC_FILES = $(wildcard $(SRC)/*.c)
APP_FILES = $(wildcard $(APPS)/*.c)

# Nome do executável (usa o primeiro .c da pasta apps)
EXEC_NAME = $(basename $(notdir $(firstword $(APP_FILES))))

all:
	@$(call MKDIR,$(BIN))
	@echo "Compilando arquivos fonte..."
	gcc $(SRC_FILES) $(APP_FILES) -I $(INCLUDE) -o $(BIN)/$(EXEC_NAME)$(EXE) -lm
	@$(MAKE) -s run

run:
	#@echo "Executando programa..."
	$(RUN_CMD)$(BIN)/$(EXEC_NAME)$(EXE)

clean:
	@echo "Limpando..."
	@$(call RM,$(BIN)/$(EXEC_NAME)$(EXE))
	@$(call RM,$(BIN)/*.exe)

help:
	@echo "=== MAKEFILE GENÉRICO ==="
	@echo "make all    - Compila tudo"
	@echo "make run    - Executa o programa" 
	@echo "make clean  - Limpa arquivos compilados"
	@echo "make help   - Mostra esta ajuda"
	@echo ""
	@echo "Arquivos detectados:"
	@echo "Source: $(SRC_FILES)"
	@echo "Apps:   $(APP_FILES)"

.PHONY: all run clean help
