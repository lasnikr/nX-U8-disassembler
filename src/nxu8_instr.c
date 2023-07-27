#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "lib_nxu8.h"
#include "nxu8_instr.h"

struct nxu8_instr_mask instrs[] = {
	{0x8001, 0x0f00, 0x08, 0x00f0, 0x04, "add\tr%0d,\tr%1d",          NULL},
	{0x1000, 0x0f00, 0x08, 0x00ff, 0x00, "add\tr%0d,\t#%1hh",          NULL},
	{0xf006, 0x0e00, 0x08, 0x00e0, 0x04, "add\ter%0d,\ter%1d",        NULL},
	{0xe080, 0x0e00, 0x08, 0x007f, 0x00, "add\ter%0d,\t#%1hh",         NULL},
	{0x8006, 0x0f00, 0x08, 0x00f0, 0x04, "addc\tr%0d,\tr%1d",         NULL},
	{0x6000, 0x0f00, 0x08, 0x00ff, 0x00, "addc\tr%0d,\t%1sh",         NULL},
	{0x8002, 0x0f00, 0x08, 0x00f0, 0x04, "and\tr%0d,\tr%1d",          NULL},
	{0x2000, 0x0f00, 0x08, 0x00ff, 0x00, "and\tr%0d,\t#%1hh",          NULL},
	{0x8007, 0x0f00, 0x08, 0x00f0, 0x04, "cmp\tr%0d,\tr%1d",          NULL},
	{0x7000, 0x0f00, 0x08, 0x00ff, 0x00, "cmp\tr%0d,\t#%1hh",          NULL},
	{0x8005, 0x0f00, 0x08, 0x00f0, 0x04, "cmpc\tr%0d,\tr%1d",         NULL},
	{0x5000, 0x0f00, 0x08, 0x00ff, 0x00, "cmpc\tr%0d,\t#%1hh",         NULL},
	{0xf005, 0x0e00, 0x08, 0x00e0, 0x04, "mov\ter%0d,\ter%1d",        NULL},
	{0xe000, 0x0e00, 0x08, 0x00ff, 0x00, "mov\ter%0d,\t#%1hh",         NULL},
	{0x8000, 0x0f00, 0x08, 0x00f0, 0x04, "mov\tr%0d,\tr%1d",          NULL},
	{0x0000, 0x0f00, 0x08, 0x00ff, 0x00, "mov\tr%0d,\t#%1hh",          NULL},
	{0x8003, 0x0f00, 0x08, 0x00f0, 0x04, "or\tr%0d,\tr%1d",           NULL},
	{0x3000, 0x0f00, 0x08, 0x00ff, 0x00, "or\tr%0d,\t#%1hh",           NULL},
	{0x8004, 0x0f00, 0x08, 0x00f0, 0x04, "xor\tr%0d,\tr%1d",          NULL},
	{0x4000, 0x0f00, 0x08, 0x00ff, 0x00, "xor\tr%0d,\t#%1hh",          NULL},
	{0xf007, 0x0e00, 0x08, 0x00e0, 0x04, "cmp\ter%0d,\ter%1d",        NULL},
	{0x8008, 0x0f00, 0x08, 0x00f0, 0x04, "sub\tr%0d,\tr%1d",          NULL},
	{0x8009, 0x0f00, 0x08, 0x00f0, 0x04, "subc\tr%0d,\tr%1d",         NULL},

	{0x800a, 0x0f00, 0x08, 0x00f0, 0x04, "sll\tr%0d,\tr%1d",          NULL},
	{0x900a, 0x0f00, 0x08, 0x0070, 0x04, "sll\tr%0d,\t%1d",           NULL},
	{0x800b, 0x0f00, 0x08, 0x00f0, 0x04, "sllc\tr%0d,\tr%1d",         NULL},
	{0x900b, 0x0f00, 0x08, 0x0070, 0x04, "sllc\tr%0d,\t%1d",          NULL},
	{0x800e, 0x0f00, 0x08, 0x00f0, 0x04, "sra\tr%0d,\tr%1d",          NULL},
	{0x900e, 0x0f00, 0x08, 0x0070, 0x04, "sra\tr%0d,\t%1d",           NULL},
	{0x800c, 0x0f00, 0x08, 0x00f0, 0x04, "srl\tr%0d,\tr%1d",          NULL},
	{0x900c, 0x0f00, 0x08, 0x0070, 0x04, "srl\tr%0d,\t%1d",           NULL},
	{0x800d, 0x0f00, 0x08, 0x00f0, 0x04, "srlc\tr%0d,\tr%1d",         NULL},
	{0x900d, 0x0f00, 0x08, 0x0070, 0x04, "srlc\tr%0d,\t%1d",          NULL},

	{0x9032, 0x0e00, 0x08, 0x0000, 0x00, "l\ter%0d,\t%D:[ea]",        NULL},
	{0x9052, 0x0e00, 0x08, 0x0000, 0x00, "l\ter%0d,\t%D:[ea+]",       NULL},
	{0x9002, 0x0e00, 0x08, 0x00e0, 0x04, "l\ter%0d,\t%D:[er%1d]",     NULL},
	{0xa008, 0x0e00, 0x08, 0x00e0, 0x04, "l\ter%0d,\t%D:%2hh[er%1d]", NULL},
	{0xb000, 0x0e00, 0x08, 0x003f, 0x00, "l\ter%0d,\t%D:%1sh[bp]",    NULL},
	{0xb040, 0x0e00, 0x08, 0x003f, 0x00, "l\ter%0d,\t%D:%1sh[fp]",    NULL},
	{0x9012, 0x0e00, 0x08, 0x0000, 0x00, "l\ter%0d,\t%D:%2hh",        NULL},
	{0x9030, 0x0f00, 0x08, 0x0000, 0x00, "l\tr%0d,\t%D:[ea]",         NULL},
	{0x9050, 0x0f00, 0x08, 0x0000, 0x00, "l\tr%0d,\t%D:[ea+]",        NULL},
	{0x9000, 0x0f00, 0x08, 0x00e0, 0x04, "l\tr%0d,\t%D:[er%1d]",      NULL},
	{0x9008, 0x0f00, 0x08, 0x00e0, 0x04, "l\tr%0d,\t%D:%2hh[er%1d]",  NULL},
	{0xd000, 0x0f00, 0x08, 0x003f, 0x00, "l\tr%0d,\t%D:%1sh[bp]",     NULL},
	{0xd040, 0x0f00, 0x08, 0x003f, 0x00, "l\tr%0d,\t%D:%1sh[fp]",     NULL},
	{0x9010, 0x0f00, 0x08, 0x0000, 0x00, "l\tr%0d,\t%D:%2hh",         NULL},
	{0x9034, 0x0c00, 0x08, 0x0000, 0x00, "l\txr%0d,\t%D:[ea]",        NULL},
	{0x9054, 0x0c00, 0x08, 0x0000, 0x00, "l\txr%0d,\t%D:[ea+]",       NULL},
	{0x9036, 0x0800, 0x08, 0x0000, 0x00, "l\tqr%0d,\t%D:[ea]",        NULL},
	{0x9056, 0x0800, 0x08, 0x0000, 0x00, "l\tqr%0d,\t%D:[ea+]",       NULL},

	{0x9033, 0x0e00, 0x08, 0x0000, 0x00, "st\ter%0d,\t%D:[ea]",        NULL},
	{0x9053, 0x0e00, 0x08, 0x0000, 0x00, "st\ter%0d,\t%D:[ea+]",       NULL},
	{0x9003, 0x0e00, 0x08, 0x00e0, 0x04, "st\ter%0d,\t%D:[er%d]",      NULL},
	{0xa009, 0x0e00, 0x08, 0x00e0, 0x04, "st\ter%0d,\t%D:%2hh[er%1d]", NULL},
	{0xb080, 0x0e00, 0x08, 0x003f, 0x00, "st\ter%0d,\t%D:%1sh[bp]",    NULL},
	{0xb0c0, 0x0e00, 0x08, 0x003f, 0x00, "st\ter%0d,\t%D:%1sh[fp]",    NULL},
	{0x9013, 0x0e00, 0x08, 0x0000, 0x00, "st\ter%0d,\t%D:%2hh",        NULL},
	{0x9031, 0x0f00, 0x08, 0x0000, 0x00, "st\tr%0d,\t%D:[ea]",         NULL},
	{0x9051, 0x0f00, 0x08, 0x0000, 0x00, "st\tr%0d,\t%D:[ea+]",        NULL},
	{0x9001, 0x0f00, 0x08, 0x00e0, 0x04, "st\tr%0d,\t%D:[er%1d]",      NULL},
	{0x9009, 0x0f00, 0x08, 0x00e0, 0x04, "st\tr%0d,\t%D:%2hh[er%1d]",  NULL},
	{0xd080, 0x0f00, 0x08, 0x003f, 0x00, "st\tr%0d,\t%D:%1sh[bp]",     NULL},
	{0xd0c0, 0x0f00, 0x08, 0x003f, 0x00, "st\tr%0d,\t%D:%1sh[fp]",     NULL},
	{0x9011, 0x0f00, 0x08, 0x0000, 0x00, "st\tr%0d,\t%D:%2hh",         NULL},
	{0x9035, 0x0c00, 0x08, 0x0000, 0x00, "st\txr%0d,\t%D:[ea]",        NULL},
	{0x9055, 0x0c00, 0x08, 0x0000, 0x00, "st\txr%0d,\t%D:[ea+]",       NULL},
	{0x9037, 0x0800, 0x08, 0x0000, 0x00, "st\tqr%0d,\t%D:[ea]",        NULL},
	{0x9057, 0x0800, 0x08, 0x0000, 0x00, "st\tqr%0d,\t%D:[ea+]",       NULL},

	{0xe100, 0x00ff, 0x00, 0x0000, 0x00, "add\tsp,\t%0sh",            NULL},
	{0xa00f, 0x00f0, 0x04, 0x0000, 0x00, "mov\tecsr,\tr%0d",          NULL},
	{0xa00d, 0x0e00, 0x08, 0x0000, 0x00, "mov\telr,\ter%0d",          NULL},
	{0xa00c, 0x00f0, 0x04, 0x0000, 0x00, "mov\tepsw,\tr%0d",          NULL},
	{0xa005, 0x0e00, 0x08, 0x0000, 0x00, "mov\ter%0d,\telr",          NULL},
	{0xa01a, 0x0e00, 0x08, 0x0000, 0x00, "mov\ter%0d,\tsp",           NULL},
	{0xa00b, 0x00f0, 0x04, 0x0000, 0x00, "mov\tpsw,\tr%0d",           NULL},
	{0xe900, 0x00ff, 0x00, 0x0000, 0x00, "mov\tpsw,\t#%0hh",          NULL},
	{0xa007, 0x0f00, 0x08, 0x0000, 0x00, "mov\tr%0d,\tecsr",          NULL},
	{0xa004, 0x0f00, 0x08, 0x0000, 0x00, "mov\tr%0d,\tepsw",          NULL},
	{0xa003, 0x0f00, 0x08, 0x0000, 0x00, "mov\tr%0d,\tpsw",           NULL},
	{0xa10a, 0x00f0, 0x04, 0x0000, 0x00, "mov\tsp,\ter%0d",           NULL},
	
	{0xf05e, 0x0e00, 0x08, 0x0000, 0x00, "push\ter%0d",              NULL},
	{0xf07e, 0x0800, 0x08, 0x0000, 0x00, "push\tqr%0d",              NULL},
	{0xf04e, 0x0f00, 0x08, 0x0000, 0x00, "push\tr%0d",               NULL},
	{0xf06e, 0x0c00, 0x08, 0x0000, 0x00, "push\txr%0d",              NULL},
	{0xf0ce, 0x0f00, 0x08, 0x0000, 0x00, "push\t%0r"},
	{0xf01e, 0x0e00, 0x08, 0x0000, 0x00, "pop\ter%0d",               NULL},
	{0xf03e, 0x0800, 0x08, 0x0000, 0x00, "pop\tqr%0d",               NULL},
	{0xf00e, 0x0f00, 0x08, 0x0000, 0x00, "pop\tr%0d",                NULL},
	{0xf02e, 0x0c00, 0x08, 0x0000, 0x00, "pop\txr%0d",               NULL},
	{0xf08e, 0x0f00, 0x08, 0x0000, 0x00, "pop\t%0R"},
	
	{0xa00e, 0x0f00, 0x08, 0x00f0, 0x04, "mov\tcr%0d,\tr%1d",         NULL},
	{0xf02d, 0x0e00, 0x08, 0x0000, 0x00, "mov\tcer%0d,\t%D:[ea]",     NULL},
	{0xf03d, 0x0e00, 0x08, 0x0000, 0x00, "mov\tcer%0d,\t%D:[ea+]",    NULL},
	{0xf00d, 0x0f00, 0x08, 0x0000, 0x00, "mov\tcr%0d,\t%D:[ea]",      NULL},
	{0xf01d, 0x0f00, 0x08, 0x0000, 0x00, "mov\tcr%0d,\t%D:[ea+]",     NULL},
	{0xf04d, 0x0c00, 0x08, 0x0000, 0x00, "mov\tcxr%0d,\t%D:[ea]",     NULL},
	{0xf05d, 0x0c00, 0x08, 0x0000, 0x00, "mov\tcxr%0d,\t%D:[ea+]",    NULL},
	{0xf06d, 0x0800, 0x08, 0x0000, 0x00, "mov\tcqr%0d,\t%D:[ea]",     NULL},
	{0xf07d, 0x0800, 0x08, 0x0000, 0x00, "mov\tcqr%0d,\t%D:[ea+]",    NULL},
	{0xa006, 0x0f00, 0x08, 0x00f0, 0x04, "mov\tr%0d,\tcr%0d",         NULL},
	{0xf0ad, 0x0e00, 0x08, 0x0000, 0x00, "mov\t%D:[ea],\tcer%0d",     NULL},
	{0xf0bd, 0x0e00, 0x08, 0x0000, 0x00, "mov\t%D:[ea+],\tcer%0d",    NULL},
	{0xf08d, 0x0f00, 0x08, 0x0000, 0x00, "mov\t%D:[ea],\tcr%0d",      NULL},
	{0xf09d, 0x0f00, 0x08, 0x0000, 0x00, "mov\t%D:[ea+],\tcr%0d",     NULL},
	{0xf0cd, 0x0c00, 0x08, 0x0000, 0x00, "mov\t%D:[ea],\tcxr%0d",     NULL},
	{0xf0dd, 0x0c00, 0x08, 0x0000, 0x00, "mov\t%D:[ea+],\tcxr%0d",    NULL},
	{0xf0ed, 0x0800, 0x08, 0x0000, 0x00, "mov\t%D:[ea],\tcqr%0d",     NULL},
	{0xf0fd, 0x0800, 0x08, 0x0000, 0x00, "mov\t%D:[ea+],\tcqr%0d",    NULL},

	{0xf00a, 0x00e0, 0x04, 0x0000, 0x00, "lea\t[er%0d]",             NULL},
	{0xf00b, 0x00e0, 0x04, 0x0000, 0x00, "lea\t%2hh[er%0d]",         NULL},
	{0xf00c, 0x0000, 0x00, 0x0000, 0x00, "lea\t%2hh",                NULL},

	{0x801f, 0x0f00, 0x08, 0x0000, 0x00, "daa\tr%0d",                NULL},
	{0x803f, 0x0f00, 0x08, 0x0000, 0x00, "daa\tr%0d",                NULL},
	{0x805f, 0x0f00, 0x08, 0x0000, 0x00, "daa\tr%0d",                NULL},

	{0xa000, 0x0f00, 0x08, 0x0070, 0x04, "sb\tr%0d.%1d",             NULL},
	{0xa080, 0x0070, 0x04, 0x0000, 0x00, "sb\t%2hh.%0d",             NULL},
	{0xa002, 0x0f00, 0x08, 0x0070, 0x04, "rb\tr%0d.%1d",             NULL},
	{0xa082, 0x0070, 0x04, 0x0000, 0x00, "rb\t%2hh.%0d",             NULL},
	{0xa001, 0x0f00, 0x08, 0x0070, 0x04, "tb\tr%0d.%1d",             NULL},
	{0xa081, 0x0070, 0x04, 0x0000, 0x00, "tb\t%2hh.%0d",             NULL},

	{0xed08, 0x0000, 0x00, 0x0000, 0x00, "ei",                      NULL},
	{0xebf7, 0x0000, 0x00, 0x0000, 0x00, "di",                      NULL},
	{0xed80, 0x0000, 0x00, 0x0000, 0x00, "sc",                      NULL},
	{0xeb7f, 0x0000, 0x00, 0x0000, 0x00, "rc",                      NULL},
	{0xfecf, 0x0000, 0x00, 0x0000, 0x00, "cplc",                    NULL},

	// TODO: Fix this
	{0xc000, 0x00ff, 0x00, 0x0000, 0x00, "bge\t%0Oh",                },
	{0xc100, 0x00ff, 0x00, 0x0000, 0x00, "blt\t%0Oh",                },
	{0xc200, 0x00ff, 0x00, 0x0000, 0x00, "bgt\t%0Oh",                },
	{0xc300, 0x00ff, 0x00, 0x0000, 0x00, "ble\t%0Oh",                },
	{0xc400, 0x00ff, 0x00, 0x0000, 0x00, "bges\t%0Oh",               },
	{0xc500, 0x00ff, 0x00, 0x0000, 0x00, "blts\t%0Oh",               },
	{0xc600, 0x00ff, 0x00, 0x0000, 0x00, "bgts\t%0Oh",               },
	{0xc700, 0x00ff, 0x00, 0x0000, 0x00, "bles\t%0Oh",               },
	{0xc800, 0x00ff, 0x00, 0x0000, 0x00, "bne\t%0Oh",                },
	{0xc900, 0x00ff, 0x00, 0x0000, 0x00, "beq\t%0Oh",                },
	{0xca00, 0x00ff, 0x00, 0x0000, 0x00, "bnv\t%0Oh",                },
	{0xcb00, 0x00ff, 0x00, 0x0000, 0x00, "bov\t%0Oh",                },
	{0xcc00, 0x00ff, 0x00, 0x0000, 0x00, "bps\t%0Oh",                },
	{0xcd00, 0x00ff, 0x00, 0x0000, 0x00, "bns\t%0Oh",                },
	{0xce00, 0x00ff, 0x00, 0x0000, 0x00, "bal\t%0Oh",                },

	{0x810f, 0x0e00, 0x08, 0x00e0, 0x04, "extbw\ter%0d",             NULL},

	{0xe500, 0x003f, 0x00, 0x0000, 0x00, "swi\t%1hh",                NULL},
	{0xffff, 0x0000, 0x00, 0x0000, 0x00, "brk",                     NULL},
	
	// TODO: Fix this
	{0xf000, 0x0f00, 0x08, 0x0000, 0x00, "b\t%0h:%2hh",              },
	{0xf002, 0x00f0, 0x04, 0x0000, 0x00, "b\ter%d",                  NULL},
	{0xf001, 0x0f00, 0x08, 0x0000, 0x00, "bl\t%0h:%2hh",             },
	{0xf003, 0x00f0, 0x04, 0x0000, 0x00, "bl\ter%d",                 NULL},

	{0xf004, 0x0e00, 0x08, 0x00f0, 0x04, "mul\ter%0d,\tr%1d",       NULL},
	{0xf009, 0x0e00, 0x08, 0x00f0, 0x04, "div\ter%0d,\tr%1d",       NULL},

	{0xfe2f, 0x0000, 0x00, 0x0000, 0x00, "inc\t[ea]",               NULL},
	{0xfe3f, 0x0000, 0x00, 0x0000, 0x00, "dec\t[ea]",               NULL},
	{0xfe1f, 0x0000, 0x00, 0x0000, 0x00, "rt",                      NULL},
	{0xfe0f, 0x0000, 0x00, 0x0000, 0x00, "rti",                     NULL},
	{0xfe8f, 0x0000, 0x00, 0x0000, 0x00, "nop",                     NULL},
};

struct nxu8_instr *nxu8_decode_instr(struct nxu8_decoder *decoder, uint32_t addr) {
	// Get the instruction word
	uint16_t instr_fw = nxu8_read16(decoder, addr);

	uint8_t dsr_len = 0;

	// DSR Instructions
	char dsr[5] = "0";
	if ((instr_fw & 0xff00) == 0xe300) {
		sprintf(dsr, "%d", instr_fw & 0x00ff);
		instr_fw = nxu8_read16(decoder, addr + 2);
		dsr_len += 2;
	} else if ((instr_fw & 0xff0f) == 0x900f) {
		sprintf(dsr, "r%d", (instr_fw >> 4) & 0xf);
		instr_fw = nxu8_read16(decoder, addr + 2);
		dsr_len += 2;
	} else if (instr_fw == 0xfe9f) {
		sprintf(dsr, "DSR");
		instr_fw = nxu8_read16(decoder, addr + 2);
		dsr_len += 2;
	}

	// Find the matching instruction
	for (int x = 0; x < sizeof(instrs) / sizeof(struct nxu8_instr_mask); x++) {
		uint16_t mask = (instrs[x].arg0_mask | instrs[x].arg1_mask) ^ 0xFFFF;

		if ((instr_fw & mask) == instrs[x].instr_mask) {
			// Initialise the instruction
			struct nxu8_instr *instr = malloc(sizeof(struct nxu8_instr));

			instr->addr = addr;
			instr->len = dsr_len + 2;
			instr->nxrefs_from = 0;
			instr->xrefs_from = NULL;
			instr->nxrefs_to = 0;
			instr->xrefs_to = NULL;

			char mnemonic[50];
			char *head = mnemonic;
			char *fmt = instrs[x].format_string;

			while (*fmt != '\0') {
				switch (*fmt) {
					case '%': {
						uint16_t src;
						uint8_t src_bits;
						fmt++;
						switch (*fmt) {
							case '0': {
								src_bits = __builtin_clz(instrs[x].arg0_mask) - instrs[x].arg0_shift - 17;
								src = (instr_fw & instrs[x].arg0_mask) >> instrs[x].arg0_shift;
								break;
							}
							case '1': {
								src_bits = __builtin_clz(instrs[x].arg1_mask) - instrs[x].arg1_shift;
								src = (instr_fw & instrs[x].arg1_mask) >> instrs[x].arg1_shift;
								break;
							}
							case '2': {
								src_bits = 16;
								src = nxu8_read16(decoder, addr + instr->len);
								instr->len += 2;
								break;
							}
							default: fmt--;
						}
						fmt++;
						switch (*fmt) {
							case 'd': {
								head += sprintf(head, "%d", src);
								break;
							}
							case 'R':
							case 'r': {
								int count = 0;
								if (src & 8) { head += sprintf(head, "lr"); count++; }
								if (src & 4) { head += sprintf(head, "%sepsw", count != 0 ? ", " : ""); count++; }
								if (src & 2) { head += sprintf(head, "%s%s", count != 0 ? ", " : "", *fmt == 'r' ? "elr" : "pc"); count++; }
								if (src & 1) { head += sprintf(head, "%sea", count != 0 ? ", " : ""); count++; }
								break;
							}
							case 'h': {
								head += sprintf(head, "%02x", src);
								break;
							}
							case 's': {
								// Sign extend src
								src |= (src >> src_bits) ? (0xFFFF << src_bits) : 0;
								head += sprintf(head, "%s%02x", src & 0x8000 ? "-" : "+", src & 0x8000 ? (src ^ 0xFFFF) + 1 : src);
								break;
							}
							case 'O': {
								src |= (src >> src_bits) ? (0xFFFF << src_bits) : 0;
								src <<= 1;
								head += sprintf(head, "%s%0x", src & 0x8000 ? "-" : "+", src & 0x8000 ? (src ^ 0xFFFF) + 1 : src);
								break;
							}
							case 'D': {
								head += sprintf(head, "%s", dsr);
								break;
							}
						}
						break;
					}

					default: {
						*(head++) = *fmt;
						break;
					}
				}
				fmt++;
			}
			*head = '\0';

			// Copy the mnemonic
			size_t length = strlen(mnemonic) + 1;
			instr->assembly = malloc(length);
			strcpy(instr->assembly, mnemonic);

			return instr;
		}
	}

	return NULL;
}