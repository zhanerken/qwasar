#include "my_ls.h"

int	ls_base(char *file_path, options_t *opt)
{
    DIR *dirp;
    struct dirent *entry;
    struct stat buffer;
    char path[1024] = "";
    fileinfo_t *entry_list = (fileinfo_t*) malloc(1000 * sizeof(fileinfo_t));

    int entry_count = 0;
    int dir_count = 0;

    dirp = opendir(file_path);

    if (dirp == NULL)
    {
        free(entry_list);
        closedir(dirp);
        return (1);
    }

    while ((entry = readdir(dirp)) != NULL)
    {
        if (opt->flag_a == 0 && entry->d_name[0] == '.') continue;
        
        my_memset(path, 0, sizeof(path));
        my_strcat(path, file_path);
        my_strcat(path, "/");
        my_strcat(path, entry->d_name);
        lstat(path, &buffer);

        entry_list[entry_count].name = (char*)malloc(1000 * sizeof(char));
        entry_list[entry_count].path = (char*)malloc(1000 * sizeof(char));

       if (S_ISDIR(buffer.st_mode))
       {
           entry_list[entry_count].time = buffer.st_mtim.tv_sec;
           entry_list[entry_count].time *= 1000000000;
           entry_list[entry_count].time += buffer.st_mtim.tv_nsec;
           my_strcpy(entry_list[entry_count].name, entry->d_name);
           my_strcpy(entry_list[entry_count].path, path);
           entry_list[entry_count].is_dir = true;
           dir_count++;
        } else
            {
               entry_list[entry_count].time = buffer.st_mtim.tv_sec;
               entry_list[entry_count].time *= 1000000000;
               entry_list[entry_count].time += buffer.st_mtim.tv_nsec;
               my_strcpy(entry_list[entry_count].name, entry->d_name);
               my_strcpy(entry_list[entry_count].path, path);
               entry_list[entry_count].is_dir = false;
            }
            entry_count++;
    }

    if (opt->flag_t == 1) _qsort(entry_list, sizeof(fileinfo_t), 0, entry_count - 1, (int (*)(void*, void*))(cmpstruct_time));
    else _qsort(entry_list, sizeof(fileinfo_t), 0, entry_count - 1, (int (*)(void*, void*))(cmpstruct));

    print_data(entry_list, entry_count, 1);

    if (dir_count > 0)
    for (int i = 0; i < entry_count; i++)
    {
        if (entry_list[i].is_dir == true && opt->flag_R == 1 && my_strcmp(entry_list[i].name, ".") != 0  && my_strcmp(entry_list[i].name, "..") != 0)
        {   
            printf("%s:\n", entry_list[i].path);
            ls_base(entry_list[i].path, opt);
        }
    }
    
    for (int i=0;i<entry_count;i++)
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
    for(int i = 0;i < entry_count; i++)
    printf("%*s- %s\n", indent, "", entry_list[i].name);
}