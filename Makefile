SRCDIR = src
BUILDDIR = build

CC = gcc
LEX = lex
YACC = yacc

SRC_DIR = src
SRC_BUILDDIR = $(BUILDDIR)/$(SRC_DIR)
SRC_GENDIR = $(BUILDDIR)/gen

BASE_FLAGS = -pipe -MMD -MP \
	-I$(SRC_GENDIR)/lex/ -I$(SRC_GENDIR)/yacc/ -Iinclude $(ADDFLAGS)
LDFLAGS = -Wl,-undefined -Wl,dynamic_lookup -lm

ifeq ($(MODE),release)
	BASE_FLAGS += -O2 -flto -DNDEBUG
	LDFLAGS += -s -flto
else
	BASE_FLAGS += -g3 -DDEBUG
	LDFLAGS +=
endif

BASE_CFLAGS = $(BASE_FLAGS) -std=c89 $(ADDCFLAGS)
CFLAGS = -Wall -Wextra $(BASE_CFLAGS)

SRC_C = $(wildcard $(SRC_DIR)/*.c)

SRC_LEX = $(wildcard $(SRC_DIR)/*.l)
LEX_GEN_C = $(addprefix $(SRC_GENDIR)/lex/,$(notdir $(SRC_LEX:.l=.yy.c)))
LEX_GEN_HDR = $(addprefix $(SRC_GENDIR)/lex/,$(notdir $(SRC_LEX:.l=.yy.h)))

SRC_YACC = $(wildcard $(SRC_DIR)/*.y)
YACC_GEN_C = $(addprefix $(SRC_GENDIR)/yacc/,$(notdir $(SRC_YACC:.y=.tab.c)))
YACC_GEN_HDR = $(addprefix $(SRC_GENDIR)/yacc/,$(notdir $(SRC_YACC:.y=.tab.h)))

GEN = $(LEX_GEN_C) $(LEX_GEN_HDR) $(YACC_GEN_C) $(YACC_GEN_HDR)

SRC_OBJS = $(addprefix $(SRC_BUILDDIR)/,$(notdir $(SRC_C:.c=.c.o))) \
	$(LEX_GEN_C:.c=.o) $(YACC_GEN_C:.c=.o)
SRC_DEPENDS = $(SRC_OBJS:.o=.d)

OBJS = $(SRC_OBJS)
EXE = $(BUILDDIR)/ib3m
ARTIFACTS = $(OBJS) $(EXE) $(SRC_DEPENDS) $(GEN)

DIR_GUARD = @if [ ! -d $(@D) ]; then echo "	MKDIR	$(@D)"; \
	mkdir -p $(@D); fi

all: $(EXE)

-include $(SRC_DEPENDS)

$(SRC_BUILDDIR)/%.c.o: $(SRC_DIR)/%.c
	$(DIR_GUARD)
	@echo "	CC	$< -> $@"
	@$(CC) $(CFLAGS) $< -c -o $@

$(SRC_GENDIR)/lex/%.yy.o: $(SRC_GENDIR)/lex/%.yy.c $(SRC_GENDIR)/yacc/%.tab.c
	$(DIR_GUARD)
	@echo "	CC	$< -> $@"
	@$(CC) $(BASE_CFLAGS) $< -c -o $@

$(SRC_GENDIR)/lex/%.yy.c: $(SRC_DIR)/%.l
	$(DIR_GUARD)
	@echo "	LEX	$< -> $@"
	@$(LEX) --header-file=${@:.c=.h} --outfile=$@ $<

$(SRC_GENDIR)/yacc/%.tab.o: $(SRC_GENDIR)/yacc/%.tab.c $(SRC_GENDIR)/lex/%.yy.c
	$(DIR_GUARD)
	@echo "	CC	$< -> $@"
	@$(CC) $(BASE_CFLAGS) $< -c -o $@

$(SRC_GENDIR)/yacc/%.tab.c: $(SRC_DIR)/%.y
	$(DIR_GUARD)
	@echo "	YACC	$< -> $@"
	@$(YACC) --defines=${@:.c=.h} --output=$@ -v $<

$(EXE): $(SRC_OBJS)
	$(DIR_GUARD)
	@echo "	LD	$@"
	@$(CC) $^ -o $@ $(LDFLAGS)

clean:
	@echo "	RM	$(BUILDDIR)/*"
	@rm -rf $(ARTIFACTS)

mrproper:
	@echo "	RM	$(BUILDDIR)/ TAGS"
	@rm -rf $(BUILDDIR)/ TAGS
	@echo "	RM	doc/"
	@rm -rf doc/

rebuild: clean all

doc:
	@echo "	DOXYGEN	Doxyfile -> doc/"
	@doxygen Doxyfile > /dev/null 2> /dev/null

TAGS: $(SRC_C)
	@echo "	CTAGS"
	@ctags -e $(SRC_C)

.PHONY: all clean mrproper rebuild doc
