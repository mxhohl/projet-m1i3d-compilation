BLASTER = ../build/blaster

TEST_FILES = $(wildcard *.c)
TEST_OUT_FILES = $(addprefix out/,$(TEST_FILES))

DIR_GUARD = @if [ ! -d $(@D) ]; then echo "	MKDIR		$(@D)"; \
	mkdir -p $(@D); fi

all: $(TEST_OUT_FILES)

out/%.c: %.c
	$(DIR_GUARD)
	@echo "	BLASTER		$< -> $@"
	@$(BLASTER) -o $@ $<

clean:
	@echo "	RM		out/*"
	@rm -rf $(TEST_OUT_FILES)

mrproper:
	@echo "	RM		out"
	@rm -rf out

.PHONY: all clean mrproper
