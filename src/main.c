#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lzrw.h"

typedef struct
{
    const char* inputPath;
    const char* outputPath;
    int action;
} PACK_OPTS;

PACK_OPTS packOpts = { 0, 0, COMPRESS_ACTION_DECOMPRESS };

int parseArguments(int argc, char** argv) {
    for (unsigned int i = 1; i < argc; i++) {
        const char* argument = argv[i];
        if (argument[0] != '-') {
            if (packOpts.inputPath == 0)
                packOpts.inputPath = argument;
            else
                packOpts.outputPath = argument;

            continue;
        }

        if (strcmp(argument, "-c") == 0 || strcmp(argument, "--compress") == 0) {
            packOpts.action = COMPRESS_ACTION_COMPRESS;
            continue;
        } else {
            fprintf(stderr, "Unknown argument: '%s'\n", argument);
            return 1;   
        }
    }
}

int main(int argc, char** argv) {

    // Print banner
    printf("LZRW3-A version 1.0-beta.1 - By SaturnKai\n");
    printf("http://www.ross.net/compression/lzrw3a.html - Ross N. Williams\n\n");

    // Check arguments
    if (argc != 3 && argc != 4) {
        printf("lzrw3a <in-file> <out-file> [-c]\n");
        printf("  <in-file>  - Path to input file\n");
        printf("  <out-file> - Path to output file\n");
        printf("\nOptions:\n");
        printf("  -c, --compress - Compress file (default: decompress)\n");
        printf("\nFor more information, please read README.TXT.\n");
        return 0;
    }

    // Parse arguments
    if (parseArguments(argc, argv) == 1)
        return 1;

    // Display info message
    printf("Output file: %s\nAction type: %s\n\n", packOpts.outputPath, packOpts.action == COMPRESS_ACTION_DECOMPRESS ? "DECOMPRESS" : "COMPRESS");

    // Open files
    FILE* inputFile = fopen(packOpts.inputPath, "rb");
    if (!inputFile) {
        fprintf(stderr, "Failed to open input file: '%s'\n", packOpts.inputPath);
        return 1;
    }

    FILE* outputFile = fopen(packOpts.outputPath, "wb");
    if (!outputFile) {
        fprintf(stderr, "Failed to open output file: '%s'\n", packOpts.outputPath);
        return 1;
    }

    // Create input buffer
    fseek(inputFile, 0L, SEEK_END);
    long size = ftell(inputFile);
    rewind(inputFile);

    unsigned char* buffer = malloc(sizeof *buffer * size);
    if (!buffer) {
        fprintf(stderr, "Failed to allocate input buffer!\n");
        return 1;
    }

    fread(buffer, size, 1, inputFile);

    // Create output buffer
    unsigned char* bufferOut = malloc(sizeof *buffer * size * 10);
    if (!bufferOut) {
        fprintf(stderr, "Failed to allocate output buffer!\n");
        return 1;
    }

    // Create working memory buffer
    uint32_t workingMemoryLen = lzrw3_req_mem();
    unsigned char* workingMemory = malloc(sizeof *workingMemory * workingMemoryLen);
    if (!workingMemory) {
        fprintf(stderr, "Failed to allocate working memory buffer!\n");
        return 1;
    }

    // Compress / decompress
    uint32_t sizeOut;
    lzrw3a_compress(packOpts.action, workingMemory, buffer, size, bufferOut, &sizeOut);
    fwrite(bufferOut, sizeOut, 1, outputFile);

    // Cleanup
    fclose(inputFile);
    fclose(outputFile);
    free(buffer);
    free(bufferOut);
    free(workingMemory);

    return 0;
}