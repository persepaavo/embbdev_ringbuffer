#include <stdio.h>
#include <string.h>
#define MAX_BUFFER 10

#define OK 1
#define ERROR -1

struct buffer_type{
  unsigned char *head;
  unsigned char *tail;
  unsigned char *buffer;
};

enum error_type{
  BUFF_OK,        /*! No error */
  BUFFER_EMPTY,   /*! Buffer is empty */
  BUFFER_FULL,    /*! Buffer is full */
  BUFFER_OVERRUN, /*! Try to read over buffer end */
  BUFFER_ERROR,
  UNKNOWN_ERROR
};

void init_buffer(struct buffer_type *b, unsigned char *buffer);
void empty_buffer(struct buffer_type *b);
signed int get_buffer_state(struct buffer_type b, enum error_type *err);
int add_char_to_buffer(struct buffer_type *b, unsigned char c, enum error_type *err);
signed char get_char_from_buffer(struct buffer_type *b, enum error_type *err);
int print_buffer(struct buffer_type b, int *err);
int add_string_to_buffer(struct buffer_type *b, unsigned char *s, enum error_type *err);
int  get_string_from_buffer(struct buffer_type *b, unsigned char *dest, int len, enum error_type *err);