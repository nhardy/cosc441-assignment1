PROGRAMS = single # thread mutex atomic
SRC_DIR = .
TMP_DIR = .tmp
OUT_DIR = bin
CC = gcc
C_FLAGS =
LD_FLAGS = -pthread
EXECUTABLES = $(patsubst %,$(OUT_DIR)/%, $(PROGRAMS))

test: $(EXECUTABLES)
	$(OUT_DIR)/single
.PHONY: test

single:	$(OUT_DIR)/single
	$(OUT_DIR)/single
.PHONY: single

thread: $(OUT_DIR)/thread
	$(OUT_DIR)/thread 8
.PHONY: thread

mutex: $(OUT_DIR)/mutex
	$(OUT_DIR)/mutex 8
.PHONY: mutex

atomic: $(OUT_DIR)/atomic
	$(OUT_DIR)/atomic 8
.PHONY: atomic

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(TMP_DIR):
	mkdir -p $(TMP_DIR)

$(TMP_DIR)/%.o: $(SRC_DIR)/%.c $(TMP_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@

$(OUT_DIR)/%: $(TMP_DIR)/%.o $(OUT_DIR)
	$(CC) $(LD_FLAGS) -o $@ $<

clean:
	rm -rf $(OUT_DIR) $(TMP_DIR)
.PHONY: clean
