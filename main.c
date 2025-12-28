#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define PROMPT "($) "

/**
 * main - Entry point for the simple shell
 * @argc: Number of arguments
 * @argv: Array of arguments
 * @envp: Environment variables
 * Return: 0 on success, non-zero on failure
 */
int main(int argc, char *argv[], char *envp[])
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;
	char *token;
	char *args[64]; /* Array for command and arguments  */
	int i;
	int cmd_count = 1;
	char **env;
	char *cmd;
	char *path;
	char *path_copy;
	char *dir;
	char full_path[1024];

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(0);
		}

		/* Remove newline */
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		/* Tokenize command and arguments */
		token = strtok(line, " \t");
		if (token == NULL)
			continue;

		i = 0;
		while (token != NULL && i < 63)
		{
			args[i] = token;
			i++;
			token = strtok(NULL, " \t");
		}
		args[i] = NULL;

		/* Handle built-ins */
		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			exit(0);
		}
		else if (strcmp(args[0], "env") == 0)
		{
			for (env = envp; *env != NULL; env++)
				printf("%s\n", *env);
			cmd_count++;
			continue;
		}

		/* Handle PATH */
		cmd = args[0];
		if (strchr(cmd, '/') == NULL)
		{
			/* Get PATH from environment */
			path = NULL;
			for (env = envp; *env != NULL; env++)
			{
				if (strncmp(*env, "PATH=", 5) == 0)
				{
					path = *env + 5;
					break;
				}
			}
			if (path != NULL)
			{
				path_copy = strdup(path);
				dir = strtok(path_copy, ":");
				while (dir != NULL)
				{
					snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
					if (access(full_path, X_OK) == 0)
					{
						args[0] = full_path;
						break;
					}
					dir = strtok(NULL, ":");
				}
				free(path_copy);
			}
		}

		pid = fork();
		if (pid == -1)
		{
			perror(argv[0]);
			continue;
		}
		if (pid == 0)
		{
			/* Child process */
			if (execve(args[0], args, envp) == -1)
			{
				fprintf(stderr, "%s: %d: %s: not found\n", argv[0], cmd_count, cmd);
				exit(127);
			}
		}
		else
		{
			/* Parent process */
			wait(&status);
			cmd_count++;
		}
	}

	free(line);
	return (0);
}