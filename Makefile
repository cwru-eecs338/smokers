CC = clang
CFLAGS = -g -Wall
LIBS = # None yet...
OUTPUT = main smoker.bin agent.bin

all: $(OUTPUT)

smoker.bin: smoker.c
	$(CC) $(LIBS) $(FLAGS) -o $@ $<

agent.bin: agent.c
	$(CC) $(LIBS) $(FLAGS) -o $@ $<

main: main.c
	$(CC) $(LIBS) $(FLAGS) -o $@ $<

clean:
	@rm -f $(OUTPUT)
