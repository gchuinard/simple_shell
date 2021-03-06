#include "hsh.h"

/**
 * *_strfindn - locates a character in a string and return position
 *
 * @s : string where to search
 * @c : character to find
 *
 * Return: position of next character c, sizeof s if not found
 *
 */

int _strfindn(char *s, char c)
{
	int i = 0;

	while (*(s + i))
	{
		if (*(s + i) == c)
			return (i + 1);
		i++;
	}

	return (i);
}


/**
 * *_strncpy - copies a string
 *
 * @dest : destination
 * @src : string source to be copied
 * @n : number of bytes from source
 *
 * Return: string concatenated
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, lensrc;

	lensrc = _strlen(src);

	for (i = 0; i <= lensrc && i < n; i++)
	{
		*(dest + i) = *(src + i);
	}

	for (; i < n; i++)
	{
		*(dest + i) = '\0';
	}
	return (dest);
}




/**
 * *_strncut - copies a portion string
 *
 * @src : string source to be copied
 * @n : number of character to cut
 * @from : number to cut from
 *
 * Return: string concatenated
 */

char *_strncut(char *src, int n, int from)
{
	char *ret;
	int i;

	ret = malloc(sizeof(char) * (n + 1));
	if (ret == NULL)
		return (NULL);

	for (i = 0; i < n; i++)
		ret[i] = src[i + from];
	ret[i] = '\0';

	return (ret);
}







/**
 * _getlinefile - get the next line of the input.
 *
 * @lineptr: the adress where stock the next line.
 * @n: number of character return.
 * @fd: file descriptor of source.
 *
 * Return: the position of the next EOL or -1 if fail
 */

ssize_t _getlinefile(char **lineptr, size_t *n, int fd)
{
	static char *buf;
	static int bufflen;
	char *nextline, *tmp;
	int nextchar;

	if (bufflen == 0)
	{
		buf = (char *)malloc(sizeof(char) * 4097);
		bufflen = read(fd, buf, 4096);
		_replace_null(buf, bufflen);
		buf[bufflen] = '\0';
	}
	if (bufflen == 0)
	{
		free(buf);
		*lineptr = NULL;
		return (EOF);
	}
	nextchar = _strfindn(buf, '\n');
	nextline = malloc((nextchar + 1) * sizeof(char));
	*n = nextchar;
	_strncpy(nextline, buf, nextchar);
	nextline[nextchar] = '\0';
	*lineptr = _strdup(nextline);
	free(nextline);
	if (bufflen == nextchar)
	{
		free(buf);
		bufflen = 0;
	}
	else
	{
		tmp = _strdup((buf + nextchar));
		free(buf);
		buf = _strdup(tmp);
		free(tmp);
		bufflen = _strlen(buf);
	}
	return (nextchar);
}
