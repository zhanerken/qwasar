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
    char * 	name;
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
int	ls_base(char *file_path, options_t *opt, int indent);
int cmpstruct(const void* v1,const void* v2);
int cmpstr(const void* v1,const void* v2);
void swap(void* v1, void* v2, int size);
void _qsort(void* v, int size, int left, int right,int (*comp)(void*, void*));
void print_data(fileinfo_t *file_list, int temp_count, int indent);
int cmpstruct_time(const void* v1,const void* v2);
bool isOption(char* str);
void set_Option(options_t* opt, char* str);
options_t* get_opt(int ac, char** av);
void set_files_list(options_t* opt, int argc, char** argv);
void free_opt(options_t* opt);

int main(int argc, char **argv) {

    options_t *opt;
    
    opt=get_opt(argc, argv);
    //printf("a=%d R=%d t=%d opt_count=%d argc=%d \n", opt->flag_a,opt->flag_R,opt->flag_t, opt->opt_ind, argc);
  
    set_files_list(opt, argc, argv);

    files_arg_handler(opt);

    free_opt(opt);

    return 0;

}

void free_opt(options_t* opt)
{
    for(int i=0;i<opt->files_count;i++)
    {
        free(opt->files_list[i]);
    }

    free(opt);
}

void set_files_list(options_t* opt, int argc, char** argv)
{   
    int index=0;
    
    opt->files_count=argc-opt->opt_ind;
   
    if (opt->opt_ind < argc) {

        opt->files_list = (char **) malloc (opt->files_count*sizeof(char *) );

        while (opt->opt_ind < argc) {
            opt->files_list[index]  = malloc(100*sizeof(char));
            //printf("argc is %d; optind is %d \n",argc,opt->opt_ind);
            strcpy(opt->files_list[index++], argv[opt->opt_ind++]);
        }
    }
    
}

options_t* get_opt(int ac, char** av)
{
    options_t* opt= (options_t*) malloc(sizeof(options_t));
    int index=1;
    opt->opt_ind=1;
    
    while(index<ac)
    {
        if (isOption(av[index]))
        {
            set_Option(opt, av[index]);
            opt->opt_ind++;
        }
        index++;
    }

    return opt;
}

void set_Option(options_t* opt, char* str)
{
    int index=1;
    char c;

    while (str[index]!='\0')
    {
        c=str[index];
        switch (c)
        {
            case 'a':
                opt->flag_a=1;
                break;
            case 'R':
                opt->flag_R=1;
                break;
            case 't':
                opt->flag_t=1;
                break;
            default:
                printf("wrong option\n");
                opt->flag_a=0;
                opt->flag_R=0;
                opt->flag_t=0;
        }

        index++;
    }
}

bool isOption(char* str)
{
      if (str[0] == '-') return true; 

    return false;
}


int	files_arg_handler(options_t *opt)
{
    _qsort(opt->files_list, sizeof(char*), 0, opt->files_count-1, (int (*)(void*, void*))(cmpstr));
    if (opt->files_count == 0) ls_base(".", opt, 0);

    for (int i=0; i<opt->files_count;i++)
    {
        printf("%s:\n",opt->files_list[i]);
        ls_base(opt->files_list[i],opt, 0);
    }

    return 0;
}

int	ls_base(char *file_path, options_t *opt, int indent)
{
    DIR		*dirp;
    struct dirent *entry;
    struct stat buffer;
    char path[1024]="";
    fileinfo_t  *entry_list = (fileinfo_t*) malloc(1000*sizeof(fileinfo_t));

    int entry_count=0;
    int dir_count=0;

    dirp = opendir(file_path);

    if (dirp == NULL)
    {
        return (1);
    }

    while ((entry = readdir(dirp)) != NULL) {

        if(opt->flag_a == 0 && entry->d_name[0] == '.') continue;

        //snprintf(path, sizeof(path), "%s/%s", file_path, entry->d_name);
        memset(path, 0, sizeof(path));
        strcat(path, file_path);
        strcat(path, "/");
        strcat(path, entry->d_name);
        lstat(path,&buffer);

        entry_list[entry_count].name=(char*)malloc(1000*sizeof(char));
        entry_list[entry_count].path=(char*)malloc(1000*sizeof(char));

       if(S_ISDIR(buffer.st_mode))
       {

               entry_list[entry_count].time=buffer.st_mtim.tv_sec;
               entry_list[entry_count].time*=1000000000;
               entry_list[entry_count].time+=buffer.st_mtim.tv_nsec;

               strcpy(entry_list[entry_count].name,entry->d_name);
               strcpy(entry_list[entry_count].path,path);
               entry_list[entry_count].is_dir = true;
               dir_count++;

        } else {
           
           entry_list[entry_count].time=buffer.st_mtim.tv_sec;
           entry_list[entry_count].time*=1000000000;
           entry_list[entry_count].time+=buffer.st_mtim.tv_nsec;

           strcpy(entry_list[entry_count].name,entry->d_name);
           strcpy(entry_list[entry_count].path,path);
           entry_list[entry_count].is_dir = false;
          
               }
         entry_count++;
    }

    if (opt->flag_t == 1)
        _qsort(entry_list, sizeof(fileinfo_t), 0, entry_count-1, (int (*)(void*, void*))(cmpstruct_time));
    else _qsort(entry_list, sizeof(fileinfo_t), 0, entry_count-1, (int (*)(void*, void*))(cmpstruct));

    print_data(entry_list, entry_count, 1);

    if (dir_count>0)
    for(int i=0;i<entry_count;i++)
    {
        if (entry_list[i].is_dir == true && opt->flag_R==1 && strcmp(entry_list[i].name, ".") != 0  && strcmp(entry_list[i].name, "..") != 0)
        {   printf("%s:\n", entry_list[i].path);
            ls_base(entry_list[i].path, opt, 2);
        }
    }

        for(int i=0;i<entry_count;i++)
        {
        free(entry_list[i].name);
        free(entry_list[i].path);

        }

    free(entry_list);

    closedir(dirp);

    return 0;
}

void print_data(fileinfo_t *entry_list, int entry_count, int indent)
{

    for(int i=0;i<entry_count;i++)
    printf("%*s- %s\n", indent, "", entry_list[i].name);
}


// v is an array of elements to sort.
// size is the number of elements in array
// left and right is start and end of array
//(*comp)(void*, void*) is a pointer to a function
// which accepts two void* as its parameter
void _qsort(void* v, int size, int left, int right,
            int (*comp)(void*, void*))
{
    void *vt, *v3;
    int i, last, mid = (left + right) / 2;
    if (left >= right)
        return;

    // casting void* to char* so that operations
    // can be done.
    void* vl = (char*)(v + (left * size));
    void* vr = (char*)(v + (mid * size));
    swap(vl, vr, size);
    last = left;
    for (i = left + 1; i <= right; i++) {

        // vl and vt will have the starting address
        // of the elements which will be passed to
        // comp function.
        vt = (char*)(v + (i * size));
        if ((*comp)(vl, vt) > 0) {
            ++last;
            v3 = (char*)(v + (last * size));
            swap(vt, v3, size);
        }
    }
    v3 = (char*)(v + (last * size));
    swap(vl, v3, size);
    _qsort(v, size, left, last - 1, comp);
    _qsort(v, size, last + 1, right, comp);
}

int cmpstr(const void* v1,const void* v2)
{
    char *a1 = (char*) v1;
    char *a2 = (char*) v2;
    return strcmp(a1, a2);
}

int cmpstruct(const void* v1,const void* v2)
{
    fileinfo_t *a1 = (fileinfo_t*) v1;
    fileinfo_t *a2 = (fileinfo_t*) v2;
    return strcmp(a1->name, a2->name);
}

int cmpstruct_time(const void* v1,const void* v2)
{
    fileinfo_t *a1 = (fileinfo_t*) v1;
    fileinfo_t *a2 = (fileinfo_t*) v2;
    int d = (a1->time == a2->time);
    if(d == 0) return (a1->time<a2->time);
    else return strcmp(a1->name, a2->name);
}


/* you can also write compare function for floats,
    chars, double similarly as integer. */
// function for swap two elements
void swap(void* v1, void* v2, int size)
{
    // buffer is array of characters which will
    // store element byte by byte
    char buffer[size];

    // memcpy will copy the contents from starting
    // address of v1 to length of size in buffer
    // byte by byte.
    memcpy(buffer, v1, size);
    memcpy(v1, v2, size);
    memcpy(v2, buffer, size);
}


