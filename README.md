# File Compression and Decompression using zlib

This C program demonstrates how to compress and decompress files using the zlib library. The zlib library provides functions for data compression and decompression using the deflate algorithm.

## Overview
The program consists of the following key components:
- `compress_file`: Function to compress a source file using zlib compression.
- `decompress_file`: Function to decompress a compressed file using zlib decompression.
- `main`: The main function that compresses a file, then decompresses the compressed file.

## How it Works
1. The program first opens the source file in binary read mode and the destination file in binary write mode.
2. It initializes a zlib stream for compression or decompression, depending on the function being called.
3. The file is read in chunks, compressed or decompressed, and then written to the destination file.
4. Once the process is complete, the files are closed, and the functions return 0 on success or -1 on failure.

## Usage
1. Compile the program using a C compiler that supports zlib (e.g., gcc).
2. Run the compiled executable.
3. The program will compress the source file (`BinarySearchR.c`) into `compressed_file.z` and then decompress it back to `decompressed_file.c`.
4. Check the output messages to see if the operations were successful.

## Dependencies
- This program requires the zlib library for compression and decompression functionalities.
- Make sure to link against the zlib library when compiling the program.

## Error Handling
- If any errors occur during file operations or zlib functions, an error message will be displayed.

Feel free to modify and integrate this code into your projects for file compression and decompression using zlib.
