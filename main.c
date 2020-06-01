#include "my_ls.h"

int main(int argc, char **argv)
{
    options_t *opt;
    opt = get_opt(argc, argv);
    set_files_list(opt, argc, argv);
    files_arg_handler(opt);
    free_opt(opt);
    return 0;
    }






