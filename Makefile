CC = gcc
LD = gold
CFLAGS = -Isrc/shared -Wall -Wextra -Werror
LFLAGS = -lc

CLIENT_TARG = bin/iop-client
CLIENT_SRCS = $(wildcard src/client/*.c src/client/**/*.c)
CLIENT_OBJS = $(patsubst src/%.c,bin/%.o,$(CLIENT_SRCS))
CLIENT_DEPS = $(patsubst src/%.c,bin/%.d,$(CLIENT_SRCS))

SERVER_TARG = bin/iop-server
SERVER_SRCS = $(wildcard src/server/*.c src/server/**/*.c)
SERVER_OBJS = $(patsubst src/%.c,bin/%.o,$(SERVER_SRCS))
SERVER_DEPS = $(patsubst src/%.c,bin/%.d,$(SERVER_SRCS))

all: $(CLIENT_TARG) $(SERVER_TARG)

client: $(CLIENT_TARG)

server: $(SERVER_TARG)

bin:
	mkdir -p bin bin/client bin/server bin/server/listeners

$(CLIENT_TARG): bin $(CLIENT_OBJS)
	@echo "[L] $(CLIENT_TARG)"
	@$(LD) $(LFLAGS) $(CLIENT_OBJS) -o $(CLIENT_TARG)

$(SERVER_TARG): bin $(SERVER_OBJS)
	@echo "[L] $(SERVER_TARG)"
	@$(LD) $(LFLAGS) $(SERVER_OBJS) -o $(SERVER_TARG)

bin/client/%.o: src/client/%.c
	@echo "[C] $<"
	@$(CC) -MM -MP -MT $@ -Isrc/client $(CFLAGS) $< > $(patsubst %.o,%.d,$@)
	@$(CC) -c $< -Isrc/client $(CFLAGS) -o $@

bin/server/%.o: src/server/%.c
	@echo "[C] $<"
	@$(CC) -MM -MP -MT $@ -Isrc/server $(CFLAGS) $< > $(patsubst %.o,%.d,$@)
	@$(CC) -c $< -Isrc/server $(CFLAGS) -o $@

-include $(CLIENT_DEPS) $(SERVER_DEPS)

clean:
	rm -rf bin/*.o bin/**/*.o bin/*.d bin/**/*.d

fclean: clean
	rm -rf bin

install:

uninstall:

.PHONY: all clean fclean re install uninstall
