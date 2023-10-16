#ifndef MAIN_H
#define MAIN_H


/**
 * struct buffer - buffer struct
 * @s: the string buffer
 *
 * Description: Longer description
 */
struct buffer
{
	char *s;
};

/**
 * buff - typedef for struct buffer
 */
typedef struct buffer buff;

int _printf(const char *format, ...);
int concat_buff(buff *b, char *new_s, int is_char);
int *get_specidx(const char *format, int n);
int get_specifier(const char *format);
int _strlen(char *s);
void init_buff(const char *s, buff *b, int len);



#endif

