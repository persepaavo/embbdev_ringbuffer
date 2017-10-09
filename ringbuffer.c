#include "ringbuffer.h"


void init_buffer(struct buffer_type *b, unsigned char *buffer){	
	b->head=buffer;
	b->tail=buffer;
	b->buffer=buffer;
}

void empty_buffer(struct buffer_type *b){
	b->tail=b->head;	
}
signed int get_buffer_state(struct buffer_type b, enum error_type *err){
	int amount = 0;
	amount = b.head-b.tail;
	if(amount<0){
		amount=amount+MAX_BUFFER;
	}
	if (amount >=0 && amount <= MAX_BUFFER){
		*err = BUFF_OK;
		return amount;
	}
	else{
		*err = BUFFER_OVERRUN;
		return -1;
	}
	
}
int add_char_to_buffer(struct buffer_type *b, unsigned char c, enum error_type *err){
	if(b->head < (b->buffer+MAX_BUFFER-1)){
		*(b->head) = c;
		b->head++;
	}
	else if((b->head == (b->buffer+MAX_BUFFER-1)) && (b->head !=b->tail)){
		*(b->head) = c;
		b->head = b->buffer;		
	}
	else{
		*err = BUFFER_FULL;
		return -1;
	}
	return get_buffer_state(*b,err);
}
signed char get_char_from_buffer(struct buffer_type *b, enum error_type *err){
	signed char temp;
	if((b->tail < (b->buffer+MAX_BUFFER-1)) && (b->head !=b->tail)){
		temp = *(b->tail);
		b->tail++;
	}
	else if((b->tail == (b->buffer+MAX_BUFFER-1))){
		temp = *(b->tail);
		b->tail = b->buffer;		
	}
	else{
		*err = BUFFER_ERROR;
		return -1;
	}
	return temp;
}
int print_buffer(struct buffer_type b, enum error_type *err){
	unsigned char *h = b.head;
	unsigned char *t = b.tail;
	char temp,i = 0;
	printf("\n\n");
	while(t != h){
		if((t < (b.buffer+MAX_BUFFER-1)) && (h != t)){
			temp = *t;
			t++;
		}
		else if((t == (b.buffer+MAX_BUFFER-1))){
			temp = *t;
			t = b.buffer;		
		}
		else{
			*err = BUFFER_ERROR;
			return -1;
		}
		printf("%c",temp);
		i++;
	}
	printf("\n\n");
	
	return i;
	
}
int add_string_to_buffer(struct buffer_type *b, unsigned char *s, enum error_type *err){
	int i = 0;
	int l = 0;
	int k;
	while(*(s+l) != '\0'){
		l++;
	}
	k = get_buffer_state(*b,err);
	
	if(l > (MAX_BUFFER-k)){
		return -1;
	}
	
	while(*(s+i) != '\0'){
		if(b->head < (b->buffer+MAX_BUFFER-1)){
			*(b->head) = *(s+i);
			b->head++;
		}
		else if((b->head == (b->buffer+MAX_BUFFER-1)) && (b->head !=b->tail)){
			*(b->head) = *(s+i);
			b->head = b->buffer;		
		}
		else{
			*err = BUFFER_FULL;
			return -1;
		}
		i++;
		*err= BUFF_OK;
	}
	return i;
	
}
int  get_string_from_buffer(struct buffer_type *b, unsigned char *dest, int len, enum error_type *err){
	int i=0;
	
	for(i=0; i<len;i++){
		*(dest+i)=get_char_from_buffer(b,err);
	}
	return i;
	
}