#include "my_ls.h"

void set_files_list(options_t* opt, int argc, char** argv)
{
    int index = 0;
    opt->files_count = argc - opt->opt_ind;
    if (opt->opt_ind < argc)
    {
        opt->files_list = (char**)malloc(opt->files_count * sizeof(char*));
        while (opt->opt_ind < argc)
        {
            opt->files_list[index] = malloc(100 * sizeof(char));
            strcpy(opt->files_list[index++], argv[opt->opt_ind++]);
        }
    }
}