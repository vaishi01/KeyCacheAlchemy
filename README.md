

# KeyCacheAlchemy

**KeyCacheAlchemy** is a project focused on implementing three key Abstract Data Types (ADTs) in C: **Set**, **Hash Table**, and **Least Recently Used (LRU) Cache**. Each ADT provides a unique method for storing and accessing key-value pairs, optimized for different use cases. This project demonstrates efficient data structure implementation and showcases the interplay between sets, hash tables, and caches.

## Overview
This project is divided into three parts:

1. **Set ADT**: A simple collection of (key, item) pairs with no duplicate keys allowed.
2. **Hash Table ADT**: An efficient set implementation using hash functions to organize data into bins.
3. **LRU Cache**: A cache that retains the most recently used items and discards the least recently used ones when full.

Each ADT uses dynamically allocated memory and generic data types, making the implementations flexible for various data types. The LRU Cache combines the efficiency of both Set and Hash Table ADTs with additional logic to maintain a fixed-size cache.



## Features

### Set ADT
The Set ADT maintains an unordered collection of key-item pairs, where each key must be unique. The Set provides basic functionality like:
- **Set_insert()**: Insert a new key-item pair.
- **Set_find()**: Retrieve an item using its key.
- **Set_print()**: Print all key-item pairs.
- **Set_iterate()**: Iterate through the set.

### Hash Table ADT
The Hash Table ADT builds on top of the Set ADT, providing a more efficient structure for large datasets. It uses a hash function to divide key-item pairs into bins for fast access. Key features include:
- **Hashtable_insert()**: Insert a key-item pair into the correct bin.
- **Hashtable_find()**: Find an item by its key.
- **Hashtable_print()**: Print all key-item pairs in the table.
- **Hashtable_iterate()**: Iterate through all bins and their contents.

### LRU Cache ADT
The LRU Cache is designed to store a limited number of items, evicting the least recently used item when it reaches capacity. It efficiently manages data using a combination of the Set and Hash Table ADTs. Key functions include:
- **LRU_insert()**: Insert a key-item pair and evict the least recently used item if full.
- **LRU_find()**: Retrieve an item and mark it as recently used.
- **LRU_delete()**: Remove an item from the cache.
- **LRU_print()**: Print the current contents of the cache.

## Compilation and Testing

To compile and test each part of the project, use the following commands:

### Set ADT:
```bash
gcc -Wall -Wextra set.c test_set.c -o test_set
./test_set
```

### Hash Table ADT:
```bash
gcc -Wall -Wextra set.c hashtable.c test_hashtable.c -o test_hashtable
./test_hashtable
```

### LRU Cache ADT:
```bash
gcc -Wall -Wextra set.c hashtable.c lru.c test_lru.c -o test_lru
./test_lru
```

Each test file (`test_set.c`, `test_hashtable.c`, `test_lru.c`) contains test cases to verify the correctness of your implementation. Run these after compiling to ensure everything works as expected.

## Usage
To use these ADTs in your own C projects, simply include the necessary header files (`set.h`, `hashtable.h`, or `lru.h`) and compile the source files along with your code. For example:
```c
#include "set.h"
#include "hashtable.h"
#include "lru.h"
```

You can then call the ADT functions as needed to manage your collections of key-item pairs.


## License
This project is licensed under the MIT License.
