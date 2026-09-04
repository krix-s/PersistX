# PersistX

A hands-on educational storage engine built in modern C++17.

PersistX explores how database storage engines manage persistent data using fixed-size pages, buffer management, write-ahead logging, crash recovery, and indexing.

---

## Architecture

```text
                    QueryEngine
                 /      |       \
                /       |        \
               v        v         v
          Index    BufferPool   WALManager
                       |
                       v
                  DiskManager
                       |
                       v
                     Page
                       |
                       v
                    Record
```

Each component has a focused responsibility:

| Component | Responsibility |
|---|---|
| **Record** | Represents a key-value record |
| **Page** | Stores records inside a fixed 4 KB page |
| **DiskManager** | Reads and writes pages to disk |
| **BufferPoolManager** | Caches pages in memory and performs LRU-style eviction |
| **WALManager** | Logs operations and replays them during recovery |
| **QueryEngine** | Coordinates database operations and maintains the in-memory index |

---

## Features

- **Page-based storage** using fixed 4 KB pages
- **Persistent disk storage** using page files
- **Buffer pool** with LRU-style eviction using a min-heap
- **Dirty-page tracking** and flushing before eviction
- **Write-Ahead Logging (WAL)** for `INSERT` and `REMOVE` operations
- **Crash recovery** through WAL replay
- **In-memory sorted index** using `std::map`
- **Exact key lookup**
- **Prefix search**
- **Lexicographic range queries**
- **Interactive command-line interface**
- **Crash simulation** for testing recovery

---

## Project Structure

```text
PersistX/
├── include/
│   ├── bufferPoolManager.h
│   ├── diskManager.h
│   ├── page.h
│   ├── queryEngine.h
│   ├── record.h
│   └── walManager.h
│
├── src/
│   ├── bufferPoolManager.cpp
│   ├── diskManager.cpp
│   ├── main.cpp
│   ├── page.cpp
│   ├── queryEngine.cpp
│   ├── record.cpp
│   └── WalManager.cpp
│
├── CMakeLists.txt
└── .gitignore
```

---

## Storage Model

PersistX stores records inside fixed-size pages.

Each page has a maximum size of 4096 bytes:

```text
Page
├── Record
├── Record
├── Record
└── ...
```

Each record contains a key and value.

Pages are persisted as individual files:

```text
data/
├── page_0.txt
├── page_1.txt
├── page_2.txt
└── ...
```

---

## Buffer Pool

The `BufferPoolManager` keeps pages in memory to reduce repeated disk I/O.

It maintains:

- An unordered map for locating cached pages
- A min-heap containing page timestamps
- Dirty-page metadata

When the buffer pool is full, the least recently accessed valid page is selected for eviction.

If the page is dirty, it is written to disk before eviction.

```text
Page request
     |
     v
Buffer Pool
   /     \
 HIT     MISS
  |        |
  v        v
Update   DiskManager
timestamp    |
             v
          Load page
```

---

## Index

`QueryEngine` maintains an in-memory sorted index:

```text
std::map<string, int>
```

which maps:

```text
key → page ID
```

This allows exact key searches to identify the relevant page without scanning every page.

The index can also be rebuilt by scanning the stored pages.

---

## Write-Ahead Logging

Before modifying the database during normal operation, PersistX records the operation in the WAL.

Example:

```text
INSERT|alice|hello
REMOVE|alice
```

The WAL is stored in:

```text
data/wal.log
```

During recovery, logged operations are replayed with WAL logging disabled to avoid recursively logging recovery operations.

---

## Crash Recovery

PersistX provides a crash simulation command that terminates the process abruptly.

The basic recovery flow is:

```text
Normal execution
      |
      v
WAL operation logged
      |
      v
Page modified
      |
      v
Crash
      |
      v
Restart
      |
      v
Read WAL
      |
      v
Replay pending operations
      |
      v
Rebuild index
      |
      v
Continue execution
```

This allows crash recovery to be tested by intentionally terminating the process between logging and normal shutdown.

---

## Query Operations

PersistX supports:

```text
INSERT <key> <value>
GET <key>
DELETE <key>
PREFIX <prefix>
RANGE <start> <end>
DISPLAY
HELP
CRASH
EXIT
```

Example:

```text
PersistX> INSERT alice hello
OK

PersistX> GET alice
hello

PersistX> INSERT bob world
OK

PersistX> PREFIX b
bob = world

PersistX> DELETE alice
OK

PersistX> GET alice
NOT FOUND!
```

---

## Building

### Requirements

- C++17-compatible compiler
- CMake

### Configure

```bash
cmake -S . -B build
```

### Build

```bash
cmake --build build
```

Run the generated executable from the location produced by CMake.

---

## Design Principles

1. **Page-based storage**  
   Persistent data is organized into fixed-size pages.

2. **Buffer-first access**  
   Pages are accessed through the buffer pool before disk I/O.

3. **Dirty-page tracking**  
   Modified pages are marked dirty and written to disk before eviction.

4. **Write-ahead logging**  
   Database operations are logged before modifying the stored state.

5. **Separation of responsibilities**  
   Query processing, caching, disk I/O, logging, pages, and records are implemented as separate components.

---

## Current Limitations

PersistX is an educational storage engine rather than a production database.

Current limitations include:

- The index is memory-resident.
- Page metadata such as total page count is maintained in memory.
- WAL uses logical operation logging rather than page-level logging.
- No concurrent transaction processing.
- No locking or multi-threaded access.
- Storage is implemented using simple text files.
- Recovery and durability mechanisms are simplified for educational purposes.

---

## License

This project is for educational purposes.
