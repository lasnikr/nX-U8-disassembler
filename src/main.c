#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "lib_nxu8.h"
#include "lib/linenoise.h"

void readFromDecoder (struct nxu8_decoder *decoder) {
	uint32_t addr = 0;
	while (addr < decoder->buf_sz) {
		struct nxu8_instr *instr = nxu8_decode_instr(decoder, addr);

		if (instr != NULL) {
			printf("%05Xh\t", instr->addr);
			for (int x = 0; x < instr->len; x += 2) printf("%04X", nxu8_read16(decoder, addr + x));
			if (instr->len < 4) printf("\t");
			printf("\t%s\n", instr->assembly);
			addr += instr->len;
		} else {
			uint16_t val = nxu8_read16(decoder, addr);
			printf("%05Xh\t%04X\t\tdw %04x\n", addr, val, val);
			addr += 2;
		}
	}
}

char* parseBinaryStringToBytes(const char* binaryString, size_t* numBytes) {
	char *underscorePtr;
	while ((underscorePtr = strchr(binaryString, '_')) != NULL) {
        memmove(underscorePtr, underscorePtr + 1, strlen(underscorePtr));
    }

    size_t strLength = strlen(binaryString);
    *numBytes = strLength / 8;

    if (strLength % 16 != 0) {
        fprintf(stderr, "Error: Binary string length must be a multiple of 16.\n");
        return NULL;
    }

    char* bytes = (char*)malloc(*numBytes);
    if (!bytes) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }

    for (size_t i = 0; i < *numBytes; i++) {
        bytes[i] = 0;
        for (size_t j = 0; j < 8; j++) {
            if (binaryString[i * 8 + j] == '1') {
                bytes[i] |= (1 << (7 - j));
            } else if (binaryString[i * 8 + j] != '0') {
                fprintf(stderr, "Error: Invalid character in the binary string.\n");
                free(bytes);
                return NULL;
            }
        }
    }

    return bytes;
}

int swap = 0;

int main(int argc, char **argv) {
	if (argc == 1) {
		printf("[Interactive Mode]\nPlease enter a stream of bits (they must be a multiple of 16):\n");
		linenoiseHistoryLoad("history.txt");
		linenoiseHistorySetMaxLen(100);
		
		char *line;
        size_t len;

		while ((line = linenoise("> "))!= NULL) {
			linenoiseHistoryAdd(line);
			linenoiseHistorySave("history.txt");

        	if (strcmp(line, "exit") == 0) {
            	free(line);
            	break;
        	}

			len = strlen(line);

			line = parseBinaryStringToBytes(line, &len);

			if (!line) continue;

			struct nxu8_decoder *decoder = nxu8_init_minimal_decoder(len,(uint8_t *)line);
			readFromDecoder(decoder);
			free(line);
		}
	} else if (argc == 2) {
		swap = 1;
		struct nxu8_decoder *decoder = nxu8_init_decoder_file(argv[1]);
		readFromDecoder(decoder);
	} else {
		printf("Usage: %s [Input File]\n", argv[0]);
	}

	return 0;
}