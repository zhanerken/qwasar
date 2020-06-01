#include "my_ls.h"

int main(int argc, char **argv) {

    options_t *opt;
    
    opt = get_opt(argc, argv); // parse options -Rat
  
    set_files_list(opt, argc, argv); // parse file names

    files_arg_handler(opt); // parse file/directory names and implement my_ls command

    free_opt(opt); // free memory

    return 0;

}






