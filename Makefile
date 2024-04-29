##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

SRC_FN	=	./run_prog.c \
			./exec_prompt.c \
			./handle_commands/handle_cd.c \
			./handle_commands/handle_env.c \
			./handle_commands/handle_exec.c \
			./handle_commands/handle_setenv.c \
			./handle_commands/handle_unsetenv.c \
			./list/push_to_list.c \
			./list/push_unique_to_list.c \
			./list/delete_in_list.c \
			./list/add_item.c \
			./list/append_to_list.c \
			./helpers/args_parsing.c \
			./helpers/parse_line_helpers.c \
			./helpers/clear_filename.c \
			./helpers/getenv_list.c \
			./helpers/free_env.c \
			./helpers/put_arg_err.c \
			./helpers/free_seps.c \
			./helpers/concat_strings.c\
			./redirections/handle_semicolon.c \
			./redirections/handle_pipe.c \
			./redirections/handle_redir_stdout.c \
			./redirections/handle_redir_stdout_append.c \
			./redirections/handle_redir_stdin.c \
			./redirections/handle_redir_stdin_word.c \
			./redirections/sep_pipes.c \
			./redirections/tree_pipe.c \
			./redirections/sep_semicolon.c \
			./parsing/get_cmd_opts.c \
			./parsing/my_getenv.c \
			./parsing/parse_args.c \
			./parsing/parse_line.c \
			./tree/create_tree.c \
			./run_tree.c

SRC     =	main.c	\
			$(SRC_FN)

TEST_SRC	= 	$(SRC_FN)	\
				tests/test_helpers.c \
				tests/test_exec_prompt.c \
				tests/test_handle_cd.c \
				tests/test_handle_env.c \
				tests/test_handle_setenv.c \
				tests/test_handle_unsetenv.c \
				tests/test_handle_pipe.c \
				tests/test_handle_redir_stdout.c \
				tests/test_handle_semicolon.c \
				tests/test_parse_line.c

TESTS	=	unit_tests

CRFLAGS	=	--coverage -lcriterion

OBJ	=	$(SRC:.c=.o)

MY_SEGFAULT_SRC	=	tests/my_segfault.c

MY_SEGFAULT	=	tests/my_segfault

OBJ_SEGFAULT	=	$(MY_SEGFAULT_SRC:.c=.o)

NAME	=	mysh

all:	lib $(NAME)

lib:
	cd lib/my && make && cd ../..

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) -L./lib/my -lmy -I./include/ -Wall -Wextra

$(MY_SEGFAULT):	$(OBJ_SEGFAULT)
	gcc -o $(MY_SEGFAULT) $(OBJ_SEGFAULT) -Wall -Wextra

tests_run: $(MY_SEGFAULT) lib
	gcc -o $(TESTS) $(TEST_SRC) $(CRFLAGS) -L./lib/my -lmy
	./$(TESTS)

clean:
	cd lib/my && make clean && cd ../..
	rm -f $(OBJ) $(OBJ_SEGFAULT) *~ ./lib/my/*.o *.gcda *.gcno

fclean:	clean
	cd lib/my && make fclean && cd ../..
	rm -f $(NAME) $(TESTS) $(MY_SEGFAULT) lsresult*

re:     fclean all

tester:		all
	cd tests/tester && cp ../../mysh . && ./tester.sh

coding-style:	fclean
	coding-style . . &&	cat coding-style-reports.log

.PHONY: lib $(NAME) $(MY_SEGFAULT)
