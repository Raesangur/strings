/******************************************************************************/
/* strings.c																  */
/* Pascal-Emmanuel Lachance													  */
/* https://www.github.com/Raesangur											  */
/* attempt at creating a C string class										  */
/******************************************************************************/
/******************************************************************************/
/* File includes */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include "strings.h"

/******************************************************************************/
/* Private functions declarations */
size_t string_length(string_t* s);
char* string_begin(string_t* s);
char* string_end(string_t* s);
char string_first(string_t* s);
char string_last(string_t* s);
char string_at(string_t* s, size_t position);
char* string_ptr_at(string_t* s, size_t position);
string_t* string_replace_char(string_t* s, char newChar, size_t position);

bool string_is_empty(string_t* s);
bool string_is_clear(string_t* s);
bool string_is_equal(string_t* s, string_t* compare);

size_t string_contains(string_t* s, const char* search);
size_t string_contains_s(string_t* s, string_t* search);
size_t string_contains_c(string_t* s, char search);

string_t* string_clear(string_t* s);
string_t* string_assign(string_t* s, const char* newString);
string_t* string_assign_n(string_t*s, const char* newString, size_t n, size_t pos);
string_t* string_assign_s(string_t* s, string_t* newString);
string_t* string_assign_s_n(string_t*s, string_t* newString, size_t n, size_t pos);
string_t* string_append(string_t* s, const char* newString);
string_t* string_append_n(string_t* s, const char* newString, size_t n, size_t pos);
string_t* string_append_s(string_t* s, string_t* newString);
string_t* string_append_s_n(string_t* s, string_t* newString, size_t n, size_t pos);
string_t* string_copy(string_t* s);
string_t* string_sub(string_t*, size_t pos, size_t n);


/******************************************************************************/
/* Public functions definitions */
string_t* stringConstructor(const char* baseString)
{
	string_t* s = malloc(sizeof(string_t));

	s->string = NULL;

	/* Set functions pointers */
	s->length = &string_length;
	s->begin = &string_begin;
	s->end = &string_end;
	s->first = &string_first;
	s->last = &string_last;
	s->at = &string_at;
	s->ptr_at = &string_ptr_at;
	s->replaceChar = &string_replace_char;

	s->is_empty = &string_is_empty;
	s->is_clear = &string_is_clear;
	s->is_equal = &string_is_equal;

	s->search = &string_contains;
	s->search_string = &string_contains_s;
	s->search_char = &string_contains_c;

	s->clear = &string_clear;
	s->assign = &string_assign;
	s->assign_n = &string_assign_n;
	s->assign_string = &string_assign_s;
	s->assign_string_n = &string_assign_s_n;
	s->append = &string_append;
	s->append_n = &string_append_n;
	s->append_string = &string_append_s;
	s->append_string_n = &string_append_s_n;
	s->create_copy = &string_copy;


	/* Set string value */
	if (baseString != NULL)
	{
		s->assign(s, baseString);
	}
	else
	{
		s->assign(s, "");
	}


	return s;
}

void stringDestructor(string_t** s)
{
	(*s)->clear(*s);

	free((*s)->string);
	free(*s);
}


/******************************************************************************/
/* Private functions definitions */
size_t string_length(string_t* s)
{
	return strlen(s->string);
}
char* string_begin(string_t* s)
{
	return s->string;
}
char* string_end(string_t* s)
{
	return s->string + (s->length(s) - 1);
}
char string_first(string_t* s)
{
	return s->string[0];
}
char string_last(string_t* s)
{
	return s->string[s->length(s) - 1];
}
char string_at(string_t* s, size_t position)
{
	if (position > s->length(s))		/* Check position validity */
	{
		return (char)0x00;				/* Return null character if invalid */
	}
	else
	{
		return s->string[position];
	}
}
char* string_ptr_at(string_t* s, size_t position)
{
	if (position > s->length(s))		/* Check position validity */
	{
		return NULL;					/* Return null if invalid */
	}
	else
	{
		return s->string + position;
	}
}
string_t* string_replace_char(string_t* s, char newChar, size_t position)
{
	if (position > s->length(s))
	{
		return NULL;
	}

	s->string[position] = newChar;

	return s;
}

bool string_is_empty(string_t* s)
{
	if (s->string == NULL)				/* If string doesn't have allocated memory */
	{
		return true;
	}
	else if (s->length(s) == 0)			/* If string is fully empty */
	{
		return true;
	}
	else if (s->length(s) == 1)			/* If the string contains a single character */
	{
		if (isblank(s->string[0]))		/* If this character is a space */
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool string_is_clear(string_t* s)
{
	size_t length = s->length(s);
	if (length == -1)					/* If length is invalid */
	{
		return false;
	}

	size_t i;
	for (i = 0; i < length; i++)
	{
		if (isblank(s->string[i]))
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	/* If it went through all the string and it was all clear */
	return true;
}
bool string_is_equal(string_t* s, string_t* compare)
{
	size_t length = s->length(s);
	if (length == -1)					/* If length is invalid */
	{
		return false;
	}

	/* Compare string lengths */
	if (length != compare->length(compare))
	{
		return false;					/* Both string lengths aren't the same */
	}


	size_t i;
	for (i = 0; i < length; i++)
	{
		if (s->string[i] == compare->string[i])
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	/* If it went through all the string and both were equal */
	return true;
}

size_t string_contains(string_t* s, const char* search)
{
	char* location = strstr(s->string, search);

	if (location == NULL)				/* If string was not found */
	{
		return -1;
	}
	else
	{
		return (location - s->string);
	}
}
size_t string_contains_s(string_t* s, string_t* search)
{
	return string_contains(s, search->string);
}
size_t string_contains_c(string_t* s, char search)
{
	char* location = strchr(s->string, search);

	if (location == NULL)				/* If character wasn't found */
	{
		return -1;
	}
	else
	{
		return (location - s->string);
	}
}

string_t* string_clear(string_t* s)
{
	size_t i;
	size_t length = s->length(s);

	if (length == -1)
	{
		return NULL;
	}

	for (i = 0; i < length; i++)
	{
		s->string[i] = ' ';				/* Replace character with space */
	}


	return s;
}
string_t* string_assign(string_t* s, const char* newString)
{
	size_t length = strlen(newString);
	if (length == -1)					/* Check if length is valid */
	{
		return NULL;
	}

	if (s->string != NULL)				/* Check if string pointer is empty */
	{
		s->clear(s);					/* Clear the string */

		/* Deallocate memory */
		free(s->string);
	}


	/* Allocate memory */
	s->string = (char*)malloc(sizeof(char) * (length + 1));

	if (s->string == NULL)				/* Check if memory allocation was successful */
	{
		return NULL;
	}


	/* Set characters */
	size_t i;
	for (i = 0; i <= length; i++)
	{
		s->string[i] = newString[i];
	}

	return s;
}
string_t* string_assign_n(string_t*s, const char* newString, size_t n, size_t pos)
{
	size_t length = strlen(newString);
	if (length == -1)					/* Check if length is valid */
	{
		return NULL;
	}

	if (n + pos > length)				/* Check if substring to create is of correct size */
	{
		return NULL;
	}


	if (s->string != NULL)				/* Check if string pointer is empty */
	{
		s->clear(s);					/* Clear the string */

		/* Deallocate memory */
		free(s->string);
	}

	/* Allocate memory */
	s->string = (char*)malloc(sizeof(char) * (n + 1));

	if (s->string == NULL)				/* Check if memory allocation was successful */
	{
		return NULL;
	}


	/* Set characters */
	size_t i;
	for (i = pos; i <= pos + n; i++)
	{
		s->string[i - pos] = newString[i];
	}

	return s;
}
string_t* string_assign_s(string_t* s, string_t* newString)
{
	if (newString->string == NULL)
	{
		return NULL;
	}
	else
	{
		return string_assign(s, newString->string);
	}
}
string_t* string_assign_s_n(string_t*s, string_t* newString, size_t n, size_t pos)
{
	if (newString->string == NULL)
	{
		return NULL;
	}
	else
	{
		return string_assign_n(s, newString->string, n, pos);
	}
}
string_t* string_append(string_t* s, const char* newString)
{
	if (s->string == NULL)				/* If the string is empty, assign a new value instead of appending it */
	{
		return string_assign(s, newString);
	}

	/* Allocate new memory space */
	s->string = (char*)realloc(s->string, sizeof(char) * (s->length(s) + strlen(newString) + 1));


	/* Append content of new string */
	strcat(s->string, newString);

	return s;
}
string_t* string_append_n(string_t* s, const char* newString, size_t n, size_t pos)
{
	if (s->string == NULL)				/* If the string is empty, assign a new value instead of appending it */
	{
		return string_assign_n(s, newString, n, pos);
	}

	if (pos + n > strlen(newString))	/* Check if substring is of correct size */
	{
		return NULL;
	}



	/* Allocate new memory space */
	s->string = (char*)realloc(s->string, sizeof(char) * (s->length(s) + n + 1));


	/* Append content of new string */
	strncat(s->string, &newString[pos], n);

	return s;
}
string_t* string_append_s(string_t* s, string_t* newString)
{
	if (newString->string == NULL)				/* If the string is empty, return original string */
	{
		return s;
	}

	return string_append(s, newString->string);
}
string_t* string_append_s_n(string_t* s, string_t* newString, size_t n, size_t pos)
{
	if (newString->string == NULL)				/* If the string is empty, return original string */
	{
		return s;
	}

	return string_append_n(s, newString->string, n, pos);
}

string_t* string_copy(string_t* s)
{
	return stringConstructor(s->string);
}

string_t* string_sub(string_t* s, size_t n, size_t pos)
{
	string_t* newString = stringConstructor(NULL);

	newString = newString->assign_string_n(newString, s, n, pos);

	return newString;
}