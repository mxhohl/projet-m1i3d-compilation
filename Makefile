EXE = compiler

LEX = lex
YACC = yacc

OBJ_DIR = ./obj
LYO_DIR = ./lyout
INC_DIR = include $(LYO_DIR)
SRC_DIR = src

CFLAGS = -I$(INC_DIR) -pedantic -Wall -Wextra -Wconversion
LDFLAGS = 
LDLIBS = -lm

SRC = $(wildcard $(SRC_DIR)/*.c)
LSRC = $(wildcard $(SRC_DIR)/*.l)
YSRC = $(wildcard $(SRC_DIR)/*.y)

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LEX_OUT = $(LSRC:$(SRC_DIR)/%.l=$(LYO_DIR)/%.yy.c)
YACC_SRC_OUT = $(YSRC:$(SRC_DIR)/%.y=$(LYO_DIR)/%.tab.c)
YACC_HDR_OUT = $(YSRC:$(SRC_DIR)/%.y=$(LYO_DIR)/%.tab.h)


all: $(EXE)


$(EXE): $(OBJ) $(LEX_OUT) $(YACC_SRC_OUT)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c object_folder
	$(CC) $(CFLAGS) -c $< -o $@

$(LYO_DIR)/%.yy.c: $(SRC_DIR)/%.l lexyacc_folder
	$(LEX) --outfile=$@ $<

$(LYO_DIR)/%.tab.c: $(SRC_DIR)/%.y lexyacc_folder
	$(YACC) --defines=$(YACC_HDR_OUT) --output=$(YACC_SRC_OUT) $<


object_folder:
	@mkdir -p $(OBJ_DIR)

lexyacc_folder:
	@mkdir -p $(LYO_DIR)


clean:
	@rm -rf $(OBJ) $(LEX_OUT) $(YACC_SRC_OUT) $(YACC_HDR_OUT)

cleanall: clean
	@rm -rf $(EXE) doc

doc:
	@doxygen Doxyfile

.PHONY: all clean cleanall object_folder lexyacc_folder doc
