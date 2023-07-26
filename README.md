# nX-U8-disassembler
### This repository is heavily based on [nxu8_disas](https://github.com/Fraserbc/nxu8_disas) by [Fraser Price](https://github.com/fraserbc)

There are some small enhancements (in speed, reliability and building), but the biggest new feature is the interactive mode.
To access the interactive mode, run the disassembler without an input file as an argument (just `./disas`).  
Inside the interactive mode, you can input a stream of bits, which has to be a multiple of 16, for example:
```
1111_1111_0000_1111
```
Note that underscores can be used for better orientation, but the input is valid with or without them.
The 16 bits are then parsed into two bytes and read by the disassembler.

The interactive mode can be extremely useful for understanding the underlying structure of nX-U8/100 Assembly and can also be used for debugging.
It also supports a command history (saved inside `history.txt`).
