#include "my_ls.h"

options_t* get_opt(int ac, char** av)
{
    options_t* opt = (options_t*)malloc(sizeof(options_t));
    int index = 1;
    opt->opt_ind = 1;
    opt->flag_a = 0;
    opt->flag_R = 0;
    opt->flag_t = 0;
    
    while(index < ac)
    {
        if (isOption(av[index]))
        {
            set_option(opt, av[index]);
            opt->opt_ind++;
        }
        index++;
    }

    return opt;
}

void set_option(options_t* opt, char* str)
{
    int index = 1;
    char c;

    while (str[index] != '\0')
    {
        c = str[index];
        switch (c)
        {
            case 'a':
                opt->flag_a = 1;
                break;
            case 'R':
                opt->flag_R = 1;
                break;
            case 't':
                opt->flag_t = 1;
                break;
            default:
                printf("wrong option\n");
                opt->flag_a = 0;
                opt->flag_R = 0;
                opt->flag_t = 0;
        }

        index++;
    }
}

bool isOption(char* str)
{
      if (str[0] == '-') return true; 

    return false;
}