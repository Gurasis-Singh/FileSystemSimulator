Advanced MiniOS File System Simulator - User Guide

1. Requirements:
- GCC compiler (Linux or WSL or Unix)
- Make

2. How to Compile:
$ make

3. How to Run:
$ ./fs

4. Features:
- Nested directory support
- File creation, deletion, read, write
- Metadata: name, size, permissions, timestamps
- CLI with commands: create, write, read, delete, ls, mkdir, cd, chmod, save, load, help, exit

5. Example Commands:
create file1
write file1 HelloWorld
read file1
mkdir folder1
cd folder1
create nested.txt
ls
save
exit

6. Notes:
- 'save' persists state to 'fs.img'
- 'load' restores state from 'fs.img'

Happy experimenting!