#ifndef extract_h
#define extract_h

#define	BUFF_SIZE	1024
#define	READ_SIZE	BUFF_SIZE - 1
#define READ_B  512
#define BUFFER  4096

#define CHAR_IS_NEWLINE(c)  c == '\n'

char    *read_line(int fd);
char    *get_one_line(int fd, int *index, char *buff);

#endif
