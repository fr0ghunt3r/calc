.SUFFIXIES: .c .o
CC=gcc
CFLAGS=-O2 -I$(INCLUDE_DIR) -lm -std=c99 -fsanitize=signed-integer-overflow

BUILD_DIR:=build
SRC_DIR:=src
INCLUDE_DIR:=include
TEST_DIR:=test
TARGET:=$(BUILD_DIR)/calc
DOCS_DIR:=docs

SRCS:=$(shell find $(SRC_DIR) -name '*.c')
OBJS:=$(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRCS:.c=.o))
OBJS:=$(filter-out $(BUILD_DIR)/main.o, $(OBJS))

TEST_OBJ = $(TEST_DIR)/test.o

.PHONY: all
all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR): 
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS) $(BUILD_DIR)/main.o
	@echo "Linking objects..."
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean
clean: 
	@echo "Cleaning..."
	@rm -rf $(BUILD_DIR) $(DOCS_DIR)/*
	@rm $(TEST_DIR)/test.o $(TEST_DIR)/test

.PHONY: test
test: $(BUILD_DIR) $(TEST_DIR)/test

$(TEST_DIR)%.o: $(TEST_DIR)%.c
		$(CC) -c -o $@ $< $(CFLAGS)

$(TEST_DIR)/test: $(TEST_OBJ) $(OBJS)
		$(CC) -o $@ $^ $(CFLAGS)


.PHONY: docs
docs: 
	@echo "Building docs..."
	@doxygen ./Doxyfile
