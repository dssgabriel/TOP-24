CC := gcc
CFLAGS := -Wall -Wextra -Wconversion -Werror -g3 -march=native -O3

SRCDIR := .
INCLUDEDIR := .
BUILDDIR := build-make
DEPSDIR := $(BUILDDIR)/deps
BIN := $(BUILDDIR)/vector

SRCS := $(wildcard *.c)
DEPS := $(patsubst %.c,$(DEPSDIR)/%.o,$(SRCS))

CFLAGS += -I$(INCLUDEDIR)

.PHONY: build clean

build: $(BIN)

$(BIN): $(DEPS)
	$(CC) $(CFLAGS) $^ -o $@

$(DEPSDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(DEPSDIR)
	$(CC) $(CFLAGS) -c $? -o $@

clean:
	@rm -fr $(BUILDDIR)
