In the first demo of the game, the GGI and TGI files are both fully compressed using the same compression method as the KUB. In order to edit these two files,
they must be first uncompressed, edited, then recompressed to be put back into the game. This simple tool can do both!

To decompress one of these formats, run the tool with the following arguments:
lzapack inputFilePath outputFilePath

To compress a file, run the tool with the -c or --compress flag instead:
lzapack inputFilePath outputFilePath -c

Examples:
lzapack KULA.TGI KULA_UNCOMPRESSED.TGI
lzapack KULA_UNCOMPRESSED.GGI KULA.GGI -c

The LZRW3-A header and source files come from: http://www.ross.net/compression/lzrw3a.html