#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct fileinfo_t {
    long long 	time;
    char * name;
    char * path;
    bool is_dir;
} fileinfo_t;

typedef struct options_t {
    int flag_R;
    int flag_a;
    int flag_t;
    int files_count;
    int opt_ind;
    char** files_list;
} options_t;

int	files_arg_handler(options_t *opt);
int	ls_base(char *file_path, options_t *opt);
int cmpstruct(const void* v1,const void* v2);
int cmpstr(const void* v1,const void* v2);
void swap(void* v1, void* v2, int size);
void _qsort(void* v, int size, int left, int right,int (*comp)(void*, void*));
void print_data(fileinfo_t *file_list, int temp_count, int indent);
int cmpstruct_time(const void* v1,const void* v2);
bool isOption(char* str);
void set_option(options_t* opt, char* str);
options_t* get_opt(int ac, char** av);
void set_files_list(options_t* opt, int argc, char** argv);
void free_opt(options_t* opt);
void* my_memset(void *b, int c, int len);
char* my_strcat(char *dest, const char *src);
char* my_strcpy(char *destination, char *source);
void my_memcpy(void *dest, void *src, int n);
int my_strcmp(const char* s1, const char* s2); 
int is_dir(const char *path);
int is_file(const char *path);