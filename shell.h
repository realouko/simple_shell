#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

/* Definitions for read and write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Definitions for command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* Definitions for convert_number() function*/
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/** Definitions for getline()
 * 1 if you're using system getline()
 */
#define USE_GETLINE 0
#define USE_STRTOK 0

/*Definitions for HIST*/
#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;


/**
 * struct liststr is a singly linked list
 *
 * @num: number field
 * @str: the string
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;



/**
 * struct passinfo - contains a random arg that can be used
 * as the input to a function to provide a
 * common prototype for function pointer structs
 *
 * @arg: a string produced by getline that contains arguments
 * @argv: a collection of strings created from arg
 * @path: the path in a string for the current command
 * @argc: the arg count
 * @line_count: this is the error count
 * @err_num: error code for exit()s
 * @linecount_flag: counts this line of input
 * @fname: this is the program filename
 * @env: localized linked list copy of enviroment
 * @environ: LL env environment updated specifically for this function
 * @history: this is the history node
 * @alias: alias node
 * @env_changed: if environ was changed
 * @status: return status for the last command executed
 * @cmd_buf: pointer to cmd_buf's address, if chaining
 * @cmd_buf_type: cmd_type ||, &&, ;
 * @readfd: the fd to read line input from
 * @histcount: counts the amount of historical lines
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf; /* pointer to cmd ; chain buff, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 *
 * @type: the builtin command flag
 * @func: this is the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;



/*BELOW IS A LIST OF PROTORYPES FOR ALL SOURCE FILES CREATED FOR THE SIMPLE SHELL*/

/* atoi.c prototypes*/
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* builtin.c prototypes*/
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* builtin1.c prototypes*/
int _myhistory(info_t *);
int _myalias(info_t *);

/* environ.c prototypes*/
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* errors.c prototypes*/
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* errors1.c prototypes*/
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* exits.c prototypes*/
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* getline.c prototypes*/
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c prototypes*/
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* getenv.c prototypes*/
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* history.c prototypes*/
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* lists.c prototypes*/
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* lists1.c prototypes*/
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* loophsh.c prototypes*/
int loophsh(char **);

/* memory.c prototypes*/
int bfree(void **);

/* parser.c prototypes*/
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* realloc.c prototypes*/
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* shell_loop.c prototypes*/
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* string.c prototypes*/
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string1.c prototypes*/
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* tokenizer.c prototypes*/
char **strtow(char *, char *);
char **strtow2(char *, char);

/* vars.c prototypes*/
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif

