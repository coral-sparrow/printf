#include "main.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>


/**
 * get_specifier - get the number of format specifier (%) in string
 * @format: string to check for % in.
 * Return: # of % in string or 0.
 */

int get_specifier(const char *format)
{
	int n = 0, i;

	if (format)
	{
		for (i = 0; format[i] != '\0'; i++)
		{
			if (format[i] == '%')
			{
				n++;
				if (format[i + 1] == '%')
					i++;
			}
		}
	}

	return (n);
}

/**
 * get_specidx - return array of specifiers indexs in string.
 * @format: string to check the %.
 * @n: number of format specifiers.
 * Return: array of int.
 */
int *get_specidx(const char *format, int n)
{
	int i, j = 0;
	int *idx;

	idx = malloc(sizeof(int) * n);

	if (!idx)
		return (NULL);

	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			idx[j] = i;
			if (format[i + 1] == '%')
				i++;
			j++;
		}
	}

	/* idx[j] = i; */
	return (idx);
}

/**
 * concat_buff - concat the new string with the str in the buffer.
 * @is_char: if it is only single char.
 * @b: buffer.
 * @new_s: the new str to concat
 * Return: 1 if success, 0 otherwise
 */
int concat_buff(buff *b, char *new_s, int is_char)
{
	int l1, l2, lt, i, j;
	char *n;

	l1 = _strlen(b->s);
	if (!is_char)
	{
		if (new_s == NULL)
			new_s = "(null)";
		l2 = _strlen(new_s);
	} else
		l2 = 1;

	lt = l1 + l2 + 1;
	n = malloc(sizeof(char) * lt);
	if (!n)
		return (0);

	j = 0;
	i = 0;
	while (i < l1)
	{
		n[i] = b->s[i];
		i++;
	}
	while (j < l2)
	{
		n[i] = new_s[j];
		i++;
		j++;
	}

	n[i] = '\0';
	free(b->s);
	b->s = n;
	return (1);
}

/**
 * concat_slice - concat the buffer with slice of given string.
 * @b: buffer.
 * @str: new str.
 * @start: begining of slice.
 * @end: end of slice.
 * Return: 1 if success, 0 otherwise
 */
int concat_slice(buff *b, const char *str, int start, int end)
{
	int l1, l2, lt, i, j;
	char *s;

	if (!b || !str)
		return (-1);
	if (start >= end)
		return (-1);

	l1 = _strlen(b->s);
	l2 = end - start;
	lt = l1 + l2 + 1;

	s = malloc(sizeof(char) * lt);

	if (!s)
		return (-1);
	i = 0;
	j = start;

	while (i < l1)
	{
		s[i] = b->s[i];
		i++;
	}
	while (j < end)
	{
		s[i] = str[j];
		i++;
		j++;
	}

	s[i] = '\0';
	free(b->s);
	b->s = s;
	return (1);
}

/**
 * _printf - custom printf function.
 * @format: the given string
 * Return: 1 if c is uppercase, 0 otherwise
 */
int _printf(const char *format, ...)
{
	int n = 0, len, i, final, *idx, flen = c_strlen(format);
	va_list ap;
	buff b;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	n = get_specifier(format);
	idx = get_specidx(format, n);
	if (!idx)
		return (-1);
	init_buff(format, &b, idx[0], n);
	for (i = 0; i < n; i++)
	{
		char tmp = format[idx[i] + 1], tmp_c, *tmp_s;
		int unk = 0;

		if ((tmp == 'c') || (tmp == '%'))
		{
			tmp_c = (tmp == 'c') ? (va_arg(ap, int)) : '%';
			concat_buff(&b, &tmp_c, 1);
		} else if (tmp == 's')
		{
			tmp_s = va_arg(ap, char *);
			concat_buff(&b, tmp_s, 0);
		} else
			unk = 1;

		if ((i + 1) != n)
		{
			if (unk)
				concat_slice(&b, format, idx[i], idx[i + 1]);
			else
				concat_slice(&b, format, idx[i] + 2, idx[i + 1]);
		} else
		{
			if (unk && (tmp != '\0'))
				final = concat_slice(&b, format, idx[i], flen);
			else if (unk)
				final = concat_slice(&b, format, idx[i] + 1, flen);
			else
				final = concat_slice(&b, format, idx[i] + 2, flen);
		}
	}
	va_end(ap);
	printf("final is %d\n", final);
	len = (final > 0) ? write(1, b.s, _strlen(b.s)) : final;
	return ((len == 0) ? 1 : len);
}
