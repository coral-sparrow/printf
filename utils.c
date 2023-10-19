#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * _strlen - get the str lenght.
 * @s: the string.
 * Return: 1 if success, 0 otherwise
 */
int _strlen(char *s)
{
	int n = 0;

	if (s)
	{
		while (*s++)
			n++;
	}
	return (n);
}



/**
 * c_strlen - get the str lenght.
 * @s: the string.
 * Return: 1 if success, 0 otherwise
 */
int c_strlen(const char *s)
{
	int n = 0;

	if (s)
	{
		while (*s++)
			n++;
	}
	return (n);
}

/**
 * init_buff - initialize buffer with the first part of the string.
 * @s: the string to use.
 * @b: the buffer struct.
 * @len: the first len of the buffer string
 * @n: number of specifiers
 * Return: Nothing.
 */
void init_buff(const char *s, buff *b, int len, int n)
{
	int i = 0;

	if (!n)
		len = c_strlen(s);
	if (!len && b && s)
	{
		b->s = malloc(sizeof(char));
		if (b->s)
			b->s[0] = '\0';
	} else if (b && s)
	{
		b->s = malloc(sizeof(char) * len);
		if (b->s)
		{
			while (len--)
			{
				b->s[i] = s[i];
				i++;
			}
		}
	}


}
