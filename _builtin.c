#include "hsh.h"

/**
 * _isbuiltin - check if the command is a builtin function.
 *
 * @comm: the command to check.
 *
 * Return: the number of the command or 0
 */

int	_isbuiltin(char *comm)
{
	unsigned int	i;
	char		*builtlist[] = {"exit", "env", "setenv",
					"unsetenv", "cd", "alias", "unalias",
					"help", "history", NULL};
	i = 0;
	while (builtlist[i])
	{
		if (_strcmp(comm, builtlist[i]) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}

/**
 * _get_b_fct - call the right builtin function.
 *
 * @comm: the command to excute.
 * @param: global parameter variable
 * @c: curop
 * @n: nextop
 * @p: parsed
 *
 * Return: the exit number of the command or 1
 */

int	_get_b_fct(char **comm, param_t *param, char *c, char *n, char **p)
{
	if (_strcmp(comm[0], "exit") == 0)
		return (_ft_exit(comm, param, c, n, p));
	if (_strcmp(comm[0], "env") == 0)
		return (_ft_env(param));
	if (_strcmp(comm[0], "setenv") == 0)
		return (_ft_setenv(comm, param));
	if (_strcmp(comm[0], "unsetenv") == 0)
		return (_ft_unsetenv(comm, param));
	if (_strcmp(comm[0], "alias") == 0)
		return (_ft_alias(comm, param));
	if (_strcmp(comm[0], "unalias") == 0)
		return (_ft_unalias(comm, param));
	if (_strcmp(comm[0], "cd") == 0)
		return (_ft_cd(comm, param));
	if (_strcmp(comm[0], "help") == 0)
		return (_ft_help(comm, param));
	if (_strcmp(comm[0], "history") == 0)
		return (_ft_history(comm, param));



	_puts("not done yet\n");
	return (1);
}
