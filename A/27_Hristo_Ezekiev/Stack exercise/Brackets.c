#include <limits.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>

	#define STARTING_SIZE 5
	#define MAX_STRING_LENGTH 100

	struct stack_z {
	int top, size;
	char *data;
	};

	void stack_init(struct stack_z*);
	void stack_destroy(struct stack_z*);
	int stack_get_size(struct stack_z);
	int stack_increase_size(struct stack_z*);
	int stack_reduce_size(struct stack_z*);
	int stack_resize(struct stack_z*);
	void transfer_data(char*, char, char*);
	void stack_push(struct stack_z*, char value);
	char stack_pop(struct stack_z*);
	bool stack_empty(struct stack_z);
	void stack_copy(struct stack_z *from, struct stack_z *to);

	int verification(char brackets[MAX_STRING_LENGTH])
	{
	struct stack_z opened_brackets;
	stack_init(&opened_brackets);
    int i;
	for(i = 0; brackets[i] != '\0'; ++i)
	{
	char current_bracket = brackets[i];

	if(current_bracket == '(' || current_bracket == '{' || current_bracket == '[')
	stack_push(&opened_brackets, current_bracket);
	else
	{
	char last_opened_bracket = stack_pop(&opened_brackets);

	if((current_bracket == ')' && last_opened_bracket != '(')
	|| (current_bracket == '}' && last_opened_bracket != '{')
	|| (current_bracket == ']' && last_opened_bracket != '['))
	return -1;
	}
	}

	if(!stack_empty(opened_brackets))
	return -1;

	stack_destroy(&opened_brackets);

	return 0;
	}

	int main()
	{
	char input[MAX_STRING_LENGTH];
	printf("Please input a few brackets in a random sequence\n");
	scanf("%s", input);

	if(verification(input) < 0)
	printf("WRONG!\n");
	else
	printf("OK.\n");

	return 0;
	}



	void stack_init(struct stack_z* s) {
	s->size = STARTING_SIZE;
	s->top = 0;
	s->data = (char*) malloc(s->size * sizeof(char));
	}

	void stack_destroy(struct stack_z* s){
	free(s->data);
	s->size = 0;
	s->top = 0;
	}

	int stack_get_size(struct stack_z s) {
	return s.top;
	}

	void stack_push(struct stack_z* s, char value) {
	if (s->top == s->size)
	stack_increase_size(s);

	s->data[s->top++] = value;
	}

	char stack_pop(struct stack_z* s) {
	if(s->top == 0)
	return -1;

	if(s->top <= s->size / 2 && s->size > STARTING_SIZE)
	stack_reduce_size(s);

	return s->data[--s->top];
	}

	void transfer_data(char *old_data, char old_data_size, char *new_data)
	{
	int i;
	for(i = 0; i < old_data_size; ++i)
	new_data[i] = old_data[i];
	}


	int stack_increase_size(struct stack_z *s)
	{
	s->size *= 2;

	if(stack_resize(s) == -1)
	return -1;

	return 0;
	}


	int stack_reduce_size(struct stack_z *s)
	{
	s->size /= 2;

	if(stack_resize(s) == -1)
	return -1;

	return 0;
	}


	int stack_resize(struct stack_z *s)
	{
	char *new_data = (char*)malloc(sizeof(char) * s->size);

	transfer_data(s->data, s->size, new_data);

	free(s->data);
	s->data = new_data;

	if(s->data == NULL)
	return -1;

	return 0;
	}

	bool stack_empty(struct stack_z s)
	{
	return s.top == 0;
	}

	void stack_copy(struct stack_z *from, struct stack_z *to)
	{
	to->data = (char*)malloc(from->size * sizeof(char));
	transfer_data(from->data, from->size, to->data);
	to->size = from->size;
	to->top = from->top;
	}
