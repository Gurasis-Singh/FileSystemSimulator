#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_system.h"

void print_help() {
    printf("Available commands:\n");
    printf("create <filename>\n");
    printf("write <filename> <data>\n");
    printf("read <filename>\n");
    printf("delete <filename>\n");
    printf("ls\n");
    printf("chmod <filename> <permission>\n");
    printf("mkdir <dirname>\n");
    printf("cd <dirname>\n");
    printf("save\n");
    printf("load\n");
    printf("help\n");
    printf("exit\n");
}

int main() {
    init_file_system();
    char command[256];

    printf("MiniOS File System Simulator. Type 'help' for commands.\n");
    while (1) {
        printf(">> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        if (strncmp(command, "create ", 7) == 0)
            create_file(command + 7);
        else if (strncmp(command, "write ", 6) == 0)
            write_file_cli(command + 6);
        else if (strncmp(command, "read ", 5) == 0)
            read_file(command + 5);
        else if (strncmp(command, "delete ", 7) == 0)
            delete_file(command + 7);
        else if (strcmp(command, "ls") == 0)
            list_files();
        else if (strncmp(command, "chmod ", 6) == 0)
            chmod_file(command + 6);
        else if (strncmp(command, "mkdir ", 6) == 0)
            make_directory(command + 6);
        else if (strncmp(command, "cd ", 3) == 0)
            change_directory(command + 3);
        else if (strcmp(command, "save") == 0)
            save_state("fs.img");
        else if (strcmp(command, "load") == 0)
            load_state("fs.img");
        else if (strcmp(command, "help") == 0)
            print_help();
        else if (strcmp(command, "exit") == 0)
            break;
        else
            printf("Invalid command! Type 'help' for list.\n");
    }

    return 0;
}