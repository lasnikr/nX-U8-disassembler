#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "lib/lib_nxu8.h"

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

void hexStringToBytes(char* bytes) {
    size_t stringLength = strlen(bytes);

    if (stringLength % 2 != 0) {
        fprintf(stderr, "Invalid input: The string length must be even.\n");
        return;
    }

    size_t numBytes = stringLength / 2;
    for (size_t i = 0; i < numBytes; ++i) {
        sscanf(&bytes[i * 2], "%2hhx", &bytes[i]);
    }
}

char* parseBinaryStringToBytes(const char* binaryString, size_t* numBytes) {
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

int main(int argc, char **argv) {
	if (argc == 1) {
		printf("[Interactive Mode]\nPlease enter a stream of bits (they must be a multiple of 16):\n");
		while (1) {
			char *line = NULL;
        	size_t len = 0;

        	if (getline(&line, &len, stdin) < 0) {
            	free(line);
            	fprintf(stderr, "Could not read the line\n");
            	return 1;
        	}

			line[strcspn(line, "\n")] = '\0';

        	if (strcmp(line, "exit") == 0) {
            	free(line);
            	break;
        	}

			len = strlen(line);

			line = parseBinaryStringToBytes(line, &len);

			if (!line) continue;
			
			struct nxu8_decoder *decoder = nxu8_init_decoder(len,(uint8_t *)line);
			readFromDecoder(decoder);
			free(line);
		}
	} else if (argc == 2) {
		struct nxu8_decoder *decoder = nxu8_init_decoder_file(argv[1]);
		readFromDecoder(decoder);
	} else {
		printf("Usage: %s [Input File]\n", argv[0]);
	}

	return 0;
}