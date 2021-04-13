# A simple memory allocator made by Qiwei He and Liwei Lu

## Usage

The program supports following commands:

1. `malloc <int size>` , which allocates certain amount of memory if available.

2. `free <int index>` , which frees the block which starts at certian pos.

3. `blocklist` , which display the information of each block.

4. `writemem <int index>, <char * str>` , which writes a string to a certain block.

5. `printmem <int index>, <int number_of_characters_to_print>` , which prints out certain amount of data from a block.

6. `quit` , which quits the program.

Structure of the Memory:

The heap size is 127 bytes long. For each block of allocated memory, the most-significant 7 bits of the headerand footershould indicate the size of the block, including the headerand footeritself. The least significant bit of the headerand footershould indicate the allocation of the block: 0 for free, 1 for allocated. 