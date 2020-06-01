CC=gcc
CC_OPT=-g3 -fsanitize=address -Wall -Wextra -Werror
OUTPUT=my_ls

${OUTPUT}: main.o get_opt.o files_arg_handler.o free_opt.o ls_base.o _qsort.o set_files_list.o utils.o
	${CC} ${CC_OPT} main.o get_opt.o files_arg_handler.o free_opt.o ls_base.o _qsort.o set_files_list.o utils.o -o ${OUTPUT}

get_opt.o: get_opt.c
	${CC} ${CC_OPT} -c get_opt.c

files_arg_handler.o: files_arg_handler.c
	${CC} ${CC_OPT} -c files_arg_handler.c

free_opt.o: free_opt.c
	${CC} ${CC_OPT} -c free_opt.c

main.o: main.c
	${CC} ${CC_OPT} -c main.c

ls_base.o: ls_base.c
	${CC} ${CC_OPT} -c ls_base.c

_qsort.o: _qsort.c
	${CC} ${CC_OPT} -c _qsort.c

set_files_list.o: set_files_list.c
	${CC} ${CC_OPT} -c set_files_list.c

utils.o: utils.c
	${CC} ${CC_OPT} -c utils.c

clean:
	rm *.o ${OUTPUT}