# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra

# Executable names
EXEC_SET = test_set
EXEC_HASHTABLE = test_hashtable
EXEC_LRU = test_LRU

# Source files
SRC_SET = set.c test_set.c
SRC_HASHTABLE = set.c hashtable.c test_hashtable.c
SRC_LRU = set.c hashtable.c lru.c test_LRU.c

# Object files
OBJ_SET = $(SRC_SET:.c=.o)
OBJ_HASHTABLE = $(SRC_HASHTABLE:.c=.o)
OBJ_LRU = $(SRC_LRU:.c=.o)

# Default target
all: $(EXEC_SET) $(EXEC_HASHTABLE) $(EXEC_LRU)

# Executable rules
$(EXEC_SET): $(OBJ_SET)
	$(CC) $(CFLAGS) -o $@ $^

$(EXEC_HASHTABLE): $(OBJ_HASHTABLE)
	$(CC) $(CFLAGS) -o $@ $^

$(EXEC_LRU): $(OBJ_LRU)
	$(CC) $(CFLAGS) -o $@ $^

# Object file rules
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -f $(EXEC_SET) $(EXEC_HASHTABLE) $(EXEC_LRU) *.o *.txt
