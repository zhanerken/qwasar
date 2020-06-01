#include "my_ls.h"

int	files_arg_handler(options_t *opt)
{
    if (opt->files_count == 0)ls_base(".", opt);
    else
    {
        _qsort(opt->files_list, sizeof(char*), 0, opt->files_count - 1, (int (*)(void*, void*))(cmpstr));
        for (int i = 0; i < opt->files_count; i++)
        {
            if (is_dir(opt->files_list[i]) != 0)
            {
                printf("%s:\n", opt->files_list[i]);
                ls_base(opt->files_list[i], opt);
            }
            else
            {
                if (is_file(opt->files_list[i])) printf("%s\n", opt->files_list[i]);
                else printf("No such file...\n");
            }
        }
    }
    return 0;
}

int is_dir(const char *path)
{
    struct stat path_stat;
    lstat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int is_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}