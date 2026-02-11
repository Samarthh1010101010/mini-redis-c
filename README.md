# Mini Redis (C)

A minimal Redis-inspired in-memory key-value store implemented in C.

## Features
- **SET / GET / DEL** commands for basic key-value operations
- Hash-table-based storage with collision handling
- Dynamic memory management
- File-based persistence across restarts

## Build

Compile the project using GCC:

```bash
gcc main.c store.c -o redis
```

## Usage

Run the executable:

```bash
./redis
```

### Available Commands

Once running, you can use the following commands:

- `SET key value` - Store a key-value pair
- `GET key` - Retrieve the value for a key
- `DEL key` - Delete a key-value pair
- `EXIT` - Exit the program

### Example Session

```
Mini Redis (Phase 1)
Commands: SET key value | GET key | DEL key | EXIT
> SET name Alice
OK
> GET name
Alice
> DEL name
Deleted
> GET name
(nil)
> EXIT
```

## Requirements

- GCC compiler
- Linux/Unix environment or Windows with MinGW/WSL

## Project Structure

- `main.c` - Main program loop and command parser
- `store.c` - Hash table implementation
- `store.h` - Hash table interface declarations

## License

Open source project - feel free to use and modify.