EXE = compiler

INC_DIR = include
SRC_DIR = src
OBJ_DIR = ./obj

CFLAGS = -I$(INC_DIR) -pedantic -Wall -Wextra -Wconversion
LDFLAGS = 
LDLIBS = -lm

SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c object
	$(CC) $(CFLAGS) -c $< -o $@

object:
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ)

cleanall: clean
	@rm -rf $(EXE) doc

doc:
	@doxygen Doxyfile

.PHONY: all clean cleanall object doc
