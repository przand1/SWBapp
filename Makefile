SRCDIR:=src
OBJDIR:=obj
LIBDIR:=lib
BINDIR:=bin
CC:=gcc
CFLAGS:=-c -Wall

$(BINDIR)/SWBapp: $(OBJDIR)/main.o $(LIBDIR)/mylib.a | $(BINDIR)
	$(CC) $^ -o $@ -lm
$(LIBDIR)/mylib.a: $(OBJDIR)/sqrt.o $(OBJDIR)/power.o $(OBJDIR)/bas_ops.o | $(LIBDIR)
	ar rsv $@ $^
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/mylib.h | $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $@
$(OBJDIR):
	mkdir $(OBJDIR)
$(SRCDIR):
	mkdir $(SRCDIR)
$(LIBDIR):
	mkdir $(LIBDIR)
$(BINDIR):
	mkdir $(BINDIR)
.PHONY: clean
clean:
	rm -f $(OBJDIR)/* $(LIBDIR)/* history $(BINDIR)/*
