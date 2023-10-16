#include "main.h"
#include <stdlib.h>

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
 * init_buff - initialize buffer with the first part of the string.
 * @s: the string to use.
 * @b: the buffer struct.
 * @len: the first len of the buffer string.
 * Return: Nothing.
 */
void init_buff(const char *s, buff *b, int len)
{
	int i = 0;

	if (b && s)
	{
		b->s = malloc(len);
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
