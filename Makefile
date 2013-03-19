CC = clang
CFLAGS = -g -Wall
LIBS = # None yet...
OUTPUT = main smoker.bin agent.bin

all: $(OUTPUT)

smoker.bin: smoker.c
	$(CC) $(LIBS) $(CFLAGS) -o $@ $<

agent.bin: agent.c
	$(CC) $(LIBS) $(CFLAGS) -o $@ $<

main: main.c
	$(CC) $(LIBS) $(CFLAGS) -o $@ $<

clean:
	@rm -f $(OUTPUT)
