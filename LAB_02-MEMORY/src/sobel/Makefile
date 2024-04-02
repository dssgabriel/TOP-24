BASE_OFLAGS := -march=native -O0

GCC := gcc
CFLAGS := -Wall -Wextra -g -fopenmp -fno-omit-frame-pointer
OFLAGS := -march=native -Ofast -finline-functions -funroll-loops -ftree-vectorize

LCC := clang

SRCDIR := src
BINDIR := build

.PHONY: all baseline clean

all: baseline baseline-gcc baseline-clang

baselines: baseline baseline-gcc baseline-clang

baseline: $(SRCDIR)/sobel.c $(SRCDIR)/common.c $(SRCDIR)/baseline.c
	@mkdir -p $(BINDIR)
	$(GCC) -DBASELINE $(GCC_CFLAGS) $(BASE_OFLAGS) $(DFLAGS) $^ -o $(BINDIR)/$@ -lm

baseline-gcc: $(SRCDIR)/sobel.c $(SRCDIR)/common.c $(SRCDIR)/baseline.c
	@mkdir -p $(BINDIR)
	$(GCC) -DBASELINE $(GCC_CFLAGS) $(GCC_OFLAGS) $(DFLAGS) $^ -o $(BINDIR)/$@ -lm

baseline-clang: $(SRCDIR)/sobel.c $(SRCDIR)/common.c $(SRCDIR)/baseline.c
	@mkdir -p $(BINDIR)
	$(LCC) -DBASELINE $(LCC_CFLAGS) $(LCC_OFLAGS) $(DFLAGS) $^ -o $(BINDIR)/$@ -lm

clean:
	@rm -Rf $(BINDIR)
