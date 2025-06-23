#include "file_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct File {
    char name[32];
    char data[512];
    int size;
    char permission[4];
    time_t created_at;
    struct File *next;
} File;

typedef struct Directory {
    char name[32];
    struct Directory *parent;
    struct Directory *subdirs;
    struct Directory *next;
    File *files;
} Directory;

Directory *root;
Directory *current;

void print_time(time_t t) {
    char buf[26];
    ctime_r(&t, buf);
    buf[strcspn(buf, "\n")] = 0;
    printf("%s", buf);
}

void init_file_system() {
    root = malloc(sizeof(Directory));
    strcpy(root->name, "/");
    root->parent = NULL;
    root->subdirs = NULL;
    root->files = NULL;
    root->next = NULL;
    current = root;
    printf("Advanced file system initialized.\n");
}

void create_file(char *name) {
    File *f = current->files;
    while (f) {
        if (strcmp(f->name, name) == 0) {
            printf("File already exists.\n");
            return;
        }
        f = f->next;
    }
    File *new_file = malloc(sizeof(File));
    strcpy(new_file->name, name);
    new_file->size = 0;
    strcpy(new_file->permission, "rw-");
    new_file->created_at = time(NULL);
    new_file->next = current->files;
    current->files = new_file;
    printf("File '%s' created.\n", name);
}

void write_file_cli(char *input) {
    char filename[32], data[512];
   sscanf(input, "%s %[^\n]", filename, data);

]", filename, data);
    File *f = current->files;
    while (f) {
        if (strcmp(f->name, filename) == 0) {
            strcpy(f->data, data);
            f->size = strlen(data);
            printf("Data written to '%s'.\n", filename);
            return;
        }
        f = f->next;
    }
    printf("File not found.\n");
}

void read_file(char *name) {
    File *f = current->files;
    while (f) {
        if (strcmp(f->name, name) == 0) {
            printf("Content: %s\n", f->data);
            return;
        }
        f = f->next;
    }
    printf("File not found.\n");
}

void delete_file(char *name) {
    File *prev = NULL, *f = current->files;
    while (f) {
        if (strcmp(f->name, name) == 0) {
            if (prev) prev->next = f->next;
            else current->files = f->next;
            free(f);
            printf("File '%s' deleted.\n", name);
            return;
        }
        prev = f;
        f = f->next;
    }
    printf("File not found.\n");
}

void chmod_file(char *input) {
    char filename[32], perm[4];
    sscanf(input, "%s %s", filename, perm);
    File *f = current->files;
    while (f) {
        if (strcmp(f->name, filename) == 0) {
            strcpy(f->permission, perm);
            printf("Permission updated for '%s'.\n", filename);
            return;
        }
        f = f->next;
    }
    printf("File not found.\n");
}

void list_files() {
    printf("Listing in directory: %s\n", current->name);
    File *f = current->files;
    while (f) {
        printf("[F] %s (%d bytes) [%s] Created: ", f->name, f->size, f->permission);
        print_time(f->created_at);
        printf("\n");
        f = f->next;
    }
    Directory *d = current->subdirs;
    while (d) {
        printf("[D] %s/\n", d->name);
        d = d->next;
    }
}

void make_directory(char *name) {
    Directory *d = current->subdirs;
    while (d) {
        if (strcmp(d->name, name) == 0) {
            printf("Directory already exists.\n");
            return;
        }
        d = d->next;
    }
    Directory *new_dir = malloc(sizeof(Directory));
    strcpy(new_dir->name, name);
    new_dir->parent = current;
    new_dir->files = NULL;
    new_dir->subdirs = NULL;
    new_dir->next = current->subdirs;
    current->subdirs = new_dir;
    printf("Directory '%s' created.\n", name);
}

void change_directory(char *name) {
    if (strcmp(name, "..") == 0) {
        if (current->parent) current = current->parent;
        return;
    }
    Directory *d = current->subdirs;
    while (d) {
        if (strcmp(d->name, name) == 0) {
            current = d;
            return;
        }
        d = d->next;
    }
    printf("Directory not found.\n");
}

void save_directory(FILE *fp, Directory *dir) {
    fwrite(dir, sizeof(Directory), 1, fp);

    File *f = dir->files;
    while (f) {
        fwrite(f, sizeof(File), 1, fp);
        f = f->next;
    }

    Directory *sub = dir->subdirs;
    while (sub) {
        save_directory(fp, sub);
        sub = sub->next;
    }
}

void save_state(const char *fname) {
    FILE *fp = fopen(fname, "wb");
    if (!fp) {
        printf("Save failed.\n");
        return;
    }
    save_directory(fp, root);
    fclose(fp);
    printf("State saved.\n");
}

void load_state(const char *fname) {
    printf("Load functionality not fully implemented for nested tree.\n");
}
