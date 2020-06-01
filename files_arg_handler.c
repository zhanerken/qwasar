#include "my_ls.h"

int	files_arg_handler(options_t *opt)
{
    _qsort(opt->files_list, sizeof(char*), 0, opt->files_count-1, (int (*)(void*, void*))(cmpstr));
    if (opt->files_count == 0) ls_base(".", opt);

    for (int i=0; i<opt->files_count;i++)
    {
        printf("%s:\n",opt->files_list[i]);
        ls_base(opt->files_list[i],opt);
    }

    return 0;
}