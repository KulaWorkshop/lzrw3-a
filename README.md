# LZRW3-A

In the [first demo](https://youtu.be/bOIwnoH2pKI) of the game, the `.TGI` and `.GGI` files are both fully compressed with [LZRW3-A](http://www.ross.net/compression/lzrw3a.html), an old compression method. In order for these files to be viewed or edited, they must first be decompressed and then recompressed to be put back into the game, and this simple tool can do both!

## Usage

`lzrw3a <in-file> <out-file> [-c]`

To **decompress**, specify the input path to the compressed file and the output path. To **compress**, specify the input path to the decompressed file, the output path, and add the `-c` flag to indicate compression instead.

Examples:

-   `lzapack KULA.TGI KULA_UNCOMPRESSED.TGI`
-   `lzapack KULA_UNCOMPRESSED.GGI KULA.GGI -c`

## Building

This project uses `make` and `gcc` to build the final executable. Once both are installed, just run the `make` command in the directory. `lzrw.h`, `lzrw3.c`, and `lzrw3-a.c` are all sourced from http://www.ross.net/compression/lzrw3a.html.
