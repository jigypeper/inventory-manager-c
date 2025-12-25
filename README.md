# Inventory Manager

A simple command-line inventory management system written in C. Manage parts using a binary search tree data structure for efficient operations.

## Features

- **Add Parts**: Insert new inventory items with part number, name, and quantity
- **Update Parts**: Modify existing part information
- **Delete Parts**: Remove parts from inventory
- **Search**: Find and display individual parts by part number
- **List All**: Display all parts in sorted order
- **Binary Search Tree**: Efficient storage and retrieval of inventory items

## Data Structure

Parts are stored in a binary search tree (`item` struct) with the following fields:
- `part_number`: Unique identifier (int)
- `part_name`: Part name (up to 25 characters)
- `qty`: Quantity in stock (int)
- `left_part`: Pointer to left child node
- `right_part`: Pointer to right child node

## Building

The project uses a Makefile for compilation with `clang`:

```bash
make           # Build the project
make run       # Build and run
make clean     # Remove all build artifacts
make debug     # Build with debug symbols
make release   # Build optimized release
```

## Usage

Run the program:
```bash
./bin/inventory-manager
```

Available commands:
- `i` - Insert a new part
- `u` - Update an existing part
- `d` - Delete a part
- `p` - Print/view a specific part
- `l` - List all parts
- `q` - Quit

## Project Structure

```
.
├── Makefile              # Build configuration
├── README.md             # This file
└── src/
    ├── main.c            # Main program and CLI interface
    └── item-fns/
        ├── item_fns.c    # Item operations (insert, update, delete, search)
        ├── item_fns.h    # Item function declarations
        ├── read_line.c   # Input reading utilities
        └── read_line.h   # Input reading declarations
```

## Compilation Details

- **Compiler**: clang
- **Standard**: C11
- **Flags**: `-Wall -Wextra` for strict error checking
- **Debug info**: Enabled by default (`-g`)

## TODO
[] Read into tree from input file  
[] Write to output file  
[] Write to SQLite database   
