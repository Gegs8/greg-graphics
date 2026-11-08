SRCDIR := src
OBJDIR := build
SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CFLAGS = -g -Wall -Wextra -Wshadow -Wpedantic -Werror -fsanitize=address
LDFLAGS = -g -fsanitize=address


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) -o $@ -c $^

main: $(OBJS)
	gcc $(LDFLAGS) -o $@ $^

clean:
	rm -rf main $(OBJDIR)

.PHONY: clean

