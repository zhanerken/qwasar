#include "my_ls.h"

void free_opt(options_t* opt)
{
    for(int i=0;i<opt->files_count;i++)
    {
        free(opt->files_list[i]);
    }
    if (opt->files_count!=0) free(opt->files_list);
    free(opt);
}