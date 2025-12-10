#include "minishell.h"
#include "libft.h"

void	execute_external_commands(t_shell *minishell)
{
	t_token	*all_commands;
	all_commands = minishell->tokens.head;
	size_t	i = 0;
	int		fd = 0;									// Valeur par defaut si aucun switch requis ? Surement bad idea - A revoir

	bool	cmd_binary_found = false;

	char	**execve_args;						// Tableau de strings (arguments du programme executé par execve)
	execve_args = ft_calloc(sizeof(char *), 4);	// Room for 4 args

	int		execve_args_count = 0;
	// Option for later : construire argv dans une boucle (mais requiert une realloc a chaque ajout TBC)

	while (i < minishell->tokens.count)
	{
		if (all_commands->type == TOK_WORD)
		{
			if((all_commands->raw_str[0] != '-') && (cmd_binary_found == false))
			{
				execve_args[execve_args_count] = ft_strjoin("/bin/", all_commands->raw_str);			// Create binary path for the ext command
				cmd_binary_found = true;
				execve_args_count++;
			}
			else if (all_commands->raw_str[0] == '-')
			{
				execve_args[execve_args_count] = ft_strdup(all_commands->raw_str);						// (If applicable) Flag
				execve_args_count++;
			}
			else
			{
				execve_args[execve_args_count] = ft_strdup(all_commands->raw_str);						// (If applicable) File
				fd = fetch_fd(all_commands->raw_str);
				execve_args_count++;
			}
		}
		else
// Something wrong here - In/Out files are added in the execve_args array = NO GOOD.
// Find a way to add them if BEFORE the redirection, and not add them if AFTER
// examples to work with :	wc -l < doc.txt
		{
			i++;											// Car on a ira obligatoirement sur le next node pour trouver le in/outfile
			fd = fetch_fd(all_commands->next->raw_str);		// Arg/location will change, grab in/outfile wherever Leo will put it
			if(all_commands->type == TOK_REDIR_IN)			// 🟣 <				wc -l < test.txt
			{
				fork_and_exec(fd, 1, execve_args);
				return;
			}
			else if(all_commands->type == TOK_REDIR_OUT)	// 🟣 >
			{
				fork_and_exec(0, fd, execve_args);
				return;
			}
			else if(all_commands->type == TOK_HEREDOC) {}	// 🟣 <<
			else if(all_commands->type == TOK_APPEND) {}	// 🟣 >>
			else if(all_commands->type == TOK_PIPE) {}		// 🟣 |
		}
		i++;
		all_commands = all_commands->next;
	}
	fork_and_exec(0, 1, execve_args);
}
// ls > test.txt
void	fork_and_exec(int fd_stdin, int fd_stdout, char	**execve_args)
{
// /* GNL TEST */			char	*test_gnl1 = get_next_line(1);
// /* GNL TEST */			printf("%sDEBUG * GNL1 : %s\n%s", S_MAGENTA, test_gnl1, NC);
// /* GNL TEST */			char	*test_gnl2 = get_next_line(fd_stdout);
// /* GNL TEST */			printf("%sDEBUG * GNL2 : %s\n%s", S_MAGENTA, test_gnl2, NC);
	char	*envp[] = {NULL};								// (Facultatif) - Tableau de strings (variables d’environnement)
	pid_t fork_pid_return = fork();							// Seulement utile en cas de < << > >> |
	if(fork_pid_return == -1)
			perror("------------------ Error");
	pid_t child_pid;
	int status;												// Status code = the one to put in the env var for error return ?
	int	backup_stdin;
	int	backup_stdout;

	if(fork_pid_return != 0)								// Le parent attend le résultat avec waitpid
	{
		child_pid = fork_pid_return;
		if(waitpid(child_pid, &status, 0) == -1)
			perror("------------------ Error");
		if(status != 0)
			printf("status is not 0 (%d) - Check macro in 'man waitpid' to find out what that means\n", status);
		printf("%sDEBUG * From Parent - PID : %d\n%s", BLUE, getpid(), NC);
	}
	else		// Le child exécute la commande avec execve -> aller chercher la commande en binaire
	{
		printf("%sDEBUG * From Child - PID : %d - Parent PID : %d\n%s", CYAN, getpid(), getppid(), NC);
		printf("%sDEBUG * Param FD_in : %d - Param FD_out : %d - Command : %s\n%s", RED, fd_stdin, fd_stdout, execve_args[0], NC);
		if(fd_stdin != STDIN_FILENO)
		{
			backup_stdin = dup(0);
			printf("%sBack up Stdin is %d\n%s", YELLOW, backup_stdin, NC);
			dup2(fd_stdin, STDIN_FILENO);
			printf("%sStdin 1 is now associated to FD %d\n%s", YELLOW, fd_stdin, NC);
			close(fd_stdin);
		}
		if(fd_stdout != STDOUT_FILENO)
		{
			backup_stdout = dup(1);
			printf("%sBack up Stdout is %d\n%s", YELLOW, backup_stdout, NC);
			dup2(fd_stdout, STDOUT_FILENO);
			printf("%sStdout 0 is now associated to FD %d\n%s", YELLOW, fd_stdout, NC);
			close(fd_stdout);
		}
		printf("%s", GREEN);
		if (execve(execve_args[0], execve_args, envp) == -1)
		{
			perror("------------------ Error");
		}
		printf("%s", NC);
		if(fd_stdin != STDIN_FILENO)			// Revert back to normal
			dup2(STDIN_FILENO, backup_stdin);
		if(fd_stdout != STDOUT_FILENO)
			dup2(STDOUT_FILENO, backup_stdout);
		printf("Everything is theorically back to normal - FD-Wise\n");
		// exit;
		// return;				// Nope bc process must stop now ? But what about memory leaks ? Use free function
	}
}

// ls > test.txt
int		fetch_fd(char *file_name)
{
	int		fd;
	char	*file_path = NULL;
	file_path = build_path(file_name);
	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);					// HYPER IMPORTANT - Tout se joue ici
	free(file_path);
	if (fd == -1)
	{
		perror("------------------ Error");
	}
	return(fd);
}

char	*build_path(char *file_name)
{
	char	*current_working_directory = fetch_current_working_directory();
	char	*cwd_with_slash = ft_strjoin(current_working_directory, "/");
	char	*file_path = ft_strjoin(cwd_with_slash, file_name);
	free(current_working_directory);
	free(cwd_with_slash);
	return (file_path);
}
