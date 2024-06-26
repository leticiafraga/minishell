##
## EPITECH PROJECT, 2024
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
			./list/clone_list_env.c \
			./helpers/args_parsing.c \
			./helpers/clear_filename.c \
			./helpers/clear_str.c \
			./helpers/concat_strings.c\
			./helpers/free_env.c \
			./helpers/free_seps.c \
			./helpers/getenv_list.c \
			./helpers/parse_line_helpers.c \
			./helpers/print_tree.c \
			./helpers/put_arg_err.c \
			./redirections/handle_semicolon.c \
			./redirections/handle_and.c \
			./redirections/handle_backticks.c \
			./redirections/handle_or.c \
			./redirections/handle_dollar.c \
			./redirections/handle_redir_stdout.c \
			./redirections/handle_redir_stdout_append.c \
			./redirections/handle_redir_stdin.c \
			./redirections/handle_redir_stdin_word.c \
			./redirections/handle_parentheses.c \
			./redirections/handle_pipe.c \
			./parsing/my_getenv.c \
			./parsing/parse_args.c \
			./parsing/parse_line.c \
			./parsing/line_error_handling.c \
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
				tests/test_handle_redir.c \
				tests/test_handle_semicolon.c \
				tests/test_handle_and_or.c \
				tests/test_handle_dollar.c \
				tests/test_handle_parentheses.c \
				tests/test_parse_line.c

TESTS	=	unit_tests

CFLAGS	=	-Wall -Wextra

CRFLAGS	=	--coverage -lcriterion

OBJ	=	$(SRC:.c=.o)

NAME	=	42sh

all:	lib $(NAME)

lib:
	cd lib/my && make && cd ../..

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) -L./lib/my -lmy -I./include/

tests_run: lib
	gcc -o $(TESTS) $(TEST_SRC) $(CRFLAGS) -L./lib/my -lmy
	./$(TESTS)

clean:
	cd lib/my && make clean && cd ../..
	rm -f $(OBJ) *~ ./lib/my/*.o *.gcda *.gcno

fclean:	clean
	cd lib/my && make fclean && cd ../..
	rm -f $(NAME) $(TESTS) lsresult*

re:     fclean all

tester:		all
	cd tests/tester && cp ../../$(NAME) ./mysh && ./tester.sh

coding-style:	fclean
	coding-style . . &&	cat coding-style-reports.log

.PHONY: lib $(NAME)
