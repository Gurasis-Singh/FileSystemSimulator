#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

void init_file_system();
void create_file(char *name);
void write_file_cli(char *input);
void read_file(char *name);
void delete_file(char *name);
void chmod_file(char *input);
void list_files();
void save_state(const char *fname);
void load_state(const char *fname);
void make_directory(char *name);
void change_directory(char *name);

#endif