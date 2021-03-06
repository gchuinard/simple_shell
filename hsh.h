#ifndef HSH_H
#define HSH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <err.h>
#include <stdbool.h>
#include <limits.h>
#define SEP " \n\a\t\v\r"


/**
 * struct error_mess - use to display proper error message
 *
 * @nbr_error: error number from execve
 * @n_err_sh: error number to return
 * @m_error: text message
 *
 * Description: store the error message
 */
typedef struct  error_mess
{
	int     nbr_error;
	int     n_err_sh;
	char    *m_error;
}       error_mess_t;



/**
 * struct aliasl - linked list on the alias variables
 *
 * @var: variable
 * @value: variable value
 * @next: next node
 *
 * Description: store the alias
 */
typedef struct aliasl
{
	char *var;
	char *value;
	struct aliasl *next;
} aliasl_t;



/**
 * struct envl - linked list on the ENV variables
 *
 * @var: variable
 * @value: variable value
 * @next: next node
 *
 * Description: store the environment
 */
typedef struct envl
{
	char *var;
	char *value;
	struct envl *next;
} envl_t;



/**
 * struct histl - linked list on the history
 *
 * @line: history line
 * @next: next node
 *
 * Description: store the history
 */
typedef struct histl
{
	char *line;
	struct histl *next;
} histl_t;



/**
 * struct paraml - central structure containing all information
 * and parameters needed to execute Shell
 *
 * @bashname: name of the bash for error message display
 * @count: number of lines of command
 * @pid: pid of the current shell process
 * @lastexit: last return value from executed commands
 * @envlist: head of linked list on the environment variables
 * @alias: head of linked list on the alias variable
 * @hist: head of linked list on the history
 * @filename : name of the file to read from if mode = 2
 * @fdnb : file descriptor to read from
 * @mode : 0 for Interactive, 1 for Noninter, 2 for FileMode
 *
 * Description: store the environment
 */


typedef struct paraml
{
	char *bashname;
	int count;
	char *pid;
	int lastexit;
	envl_t *envlist;
	aliasl_t *alias;
	histl_t *hist;
	char *filename;
	int fdnb;
	int mode;
} param_t;





extern char	**environ;

/* _builtin.c */
int	_isbuiltin(char *comm);
int	_get_b_fct(char **comm, param_t *param, char *c, char *n, char **p);

/* _putfct.c */
int	_putchar(char c);
int	_puts(char *s);
void _prompt(param_t *param);
void _prompt2(param_t *param);

/* _strfct1.c */
int	_strlen(char *s);
char	*_strcat(char *dest, char *src);
int	_strcmp(char *s1, char *s2);
char	*_strcpy(char *dest, char *src);
char	*_strdup(char *str);

/* _strfct2.c */
int	_strlennull(char *s);
char	*_str_concat(char *s1, char *s2);
char	*_getenv(char *name, char **env);
char	*_strrev(char *str);
char	*_convert_base(unsigned long int nbr, int base, int cap);

/* _strfct3.c */
char	*_str_concat_f(char *s1, char *s2);
void _replace_null(char *buf, int bufflen);

/* main.c */
int _launchShell(param_t *param);
int _shell_loop(param_t *param);
int _core_exec(char **parsed, int nbw, param_t *param);
void _siginthandler(int signum);

/* _parse_string.c */
char	**_parse_string(char *string, int *nbw);
void	_free_grid(char **grid, int height);
char	**_parse_string2(char *string, int *nbw, param_t *param);
char	**_parse_alias(char **com, int *nbw, param_t *par, aliasl_t **v, int k);
void	_free_vis(aliasl_t *vis);

/* _exec_fct.c */
int _exec_fct(char **parsed, param_t *param, char *c, char *n, char **p);
char	*_getfullpath(char *name, char *mypath);
int _eft(int nb, char *cm, char **pd, param_t *pm, char *c, char *n, char **p);
int	_error_open(int errnb, char *command, param_t *param);
int _contains_char(char *str, char c);

/* _getline.c */
int	_strfindn(char *s, char c);
char	*_strncpy(char *dest, char *src, int n);
ssize_t	_getlinefile(char **lineptr, size_t *n, int fd);
char *_strncut(char *src, int n, int from);

/* _ft_exit.c */
int	_ft_exit(char **s, param_t *param, char *c, char *n, char **p);
int	_atoi_exit(char *s);
int	_error_exit(char *command, param_t *param);

/* _env_fct.c */
int _initParam(param_t *param, char **av, char **env);
envl_t	*_getEnvList(char **env);
char	**_getEnvChar(envl_t *head);
char *_get_env_val(char *var, envl_t *head);
char *_getpid(void);

/* _free_fct.c */
int _freeParam(param_t *param);
int _free_envlist(param_t *param);
int _free_alias(param_t *param);
int _free_hist(param_t *param);
void	_free_tab(char **tab);


/* _strtow.c */
int _isdelim(char c, const char *del);
int _nbword(const char *s, const char *del);
char *_mydup(const char *str, int size);
char **_strtow(const char *str, const char *del);

/* _strtow2.c */
int _nbword2(const char *s, const char *del);
char **_strtow2(const char *str, const char *del);

/* _ft_env.c */
int	_ft_env(param_t *param);
int	_ft_setenv(char **comm, param_t *param);
int	_ft_unsetenv(char **comm, param_t *param);

/* _ft_alias.c */
int     _ft_alias(char **comm, param_t *param);
int     _print_all_alias(param_t *param);
int     _print_single_alias(char *name, param_t *param);
int     _str_findeq(char *str);
int     _assign_alias(char *comm, param_t *param);

/* _ft_unalias.c */
int     _ft_unalias(char **comm, param_t *param);
int     _delete_alias(char *comm, param_t *param);

/* _ft_cd.c */
int	_ft_cd(char **path, param_t *param);
void	_free_cd(char *home, char *pwd, char *oldpwd, char *dest);
char	*_getdest(char *path, char *home, char *oldpwd, char *pwd);
int	_error_cd(char **command, param_t *param);
void _puts_dir(char *path);

/* _listfct1.c */
int _add_nodealias(aliasl_t **head, char *var);
int _is_nodeal(aliasl_t *head, char *var);
int _strcmp2(char *s1, char *s2);

/* _operators.c */
char *_ope_str(char *s);
char *_opeNEXT(char *s);
char *_opeAND(char *s);
char *_opeOR(char *s);
char *_opeSTOP(char *s);

/* _get_parsestruc */
int _exec_string(char **parsed, int nbw, param_t *param);
char **_getcomm(char **parsed, int from, int to);
int _exec_need(char *curop, int lastexit);
int _check_grammar(char **parsed, int nbw, param_t *param);
char *_get_nextop(char **parsed, int *cur);

/* _get_parsestruc2 */
int _error_syntax(char *command, param_t *param);
int _gramm_ret(char *curop, char *nextop, int ret);
char **_removelast(char **parsed, int *nbw);
char **_concat_parsed(char **parsed, int *nbw, char **parsed2, int *nbw2);
int _error_EOF(param_t *param);

/* _dollar_parse.c */
char *_parse_env(char *comm, param_t *param);

/* _ft_help.c */
int     _ft_help(char **comm, param_t *param);
void    _help_help(void);
void    _help_env(void);
void    _help_setenv(void);
void    _help_unsetenv(void);

/* _ft_help2.c */
void    _help_exit(void);
void    _help_cd(void);
void    _help_alias(void);
void    _help_unalias(void);
void    _help_history(void);

/* _ft_help3.c */
void    _help_all(void);
void    _help_error(char *comm, param_t *param);

/* _ft_history.c */
int     _ft_history(char **comm, param_t *param);
int     _add_hist_line(char *string, param_t *param);
int     _print_hist(param_t *param);
char *_str_concat_hist(char *s1, char *s2);

/* _ft_history2.c */
int     _pull_hist(param_t *param);
int     _push_hist(param_t *param);
int     _populate_hist(char *line, param_t *param);

/* _error_base.c */
char *_error_base(param_t *param);
int _add_alias_end(char *var, char *value, param_t *param);
char *_opeSTOP_zero(char *s);
int _add_env_end(char *var, char *value, param_t *param);

#endif
