CC = clang
CFLAGS = -g -Wall
LIBS = # None yet...
OUTPUT = main smoker.bin agent.bin
HEADERS = main.h

all: $(OUTPUT)

smoker.bin: smoker.c $(HEADERS)
	$(CC) $(LIBS) $(CFLAGS) -o $@ $<

agent.bin: agent.c $(HEADERS)
	$(CC) $(LIBS) $(CFLAGS) -o $@ $<

main: main.c $(HEADERS)
	$(CC) $(LIBS) $(CFLAGS) -o $@ $<

clean:
	@rm -f $(OUTPUT)
