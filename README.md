# Binary to Wozmon

(c) 2019 by Matthias Arndt <marndt@asmsoftware.de>

The MIT License applies to this project.

## Abstract

This is a little file tool to dump a binary file in the format used by the 
Wozmon monitor software used by the Apple 1.

The output can directly be fed into a serial link if necessary.

## System requirements

- C99 compliant compiler and runtime environment

## Usage

$ bin2woz <loading address> <input file>

The loading address is given in 4 hexadecimal digits without prefix.
The output is dumped to stdout including CR/LF for Wozmon.

## Example:

$ bin2woz 0280 my_program.bin

