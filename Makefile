TARGET = solar_system

SRCS  = $(shell find ./src     -type f -name *.c)
HEADS = $(shell find ./include -type f -name *.h)
OBJS = $(SRCS:.c=.o)
DEPS = Makefile.depend

INCLUDES = -I./include
# CFLAGS = -O2 -Wall $(INCLUDES)
CFLAGS = -fPIC -Wall $(INCLUDES)
LDFLAGS = -lm -lX11


all: $(TARGET)

$(TARGET): $(OBJS) $(HEADS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

run: all
	@./$(TARGET)

.PHONY: depend clean
depend:
	$(CC) $(INCLUDES) -MM $(SRCS) > $(DEPS)
	@sed -i -E "s/^(.+?).o: ([^ ]+?)\1/\2\1.o: \2\1/g" $(DEPS)

clean:
	$(RM) $(OBJS) $(TARGET)

-include $(DEPS)