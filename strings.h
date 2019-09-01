/******************************************************************************/
/* strings.h																  */
/* Pascal-Emmanuel Lachance													  */
/* https://www.github.com/Raesangur											  */
/* attempt at creating a C string class										  */
/******************************************************************************/

#pragma once
/******************************************************************************/
/* File includes */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/******************************************************************************/
/* Typedefs */
typedef struct string_t string_t;

struct string_t
{
	char* string;

	size_t(*length)(string_t* s);
	char* (*begin)(string_t* s);
	char* (*end)(string_t* s);
	char(*first)(string_t* s);
	char(*last)(string_t* s);
	char(*at)(string_t* s, size_t position);
	char* (*ptr_at)(string_t* s, size_t position);
	string_t* (*replaceChar)(string_t* s, char newChar, size_t position);

	bool(*is_empty)(string_t* s);
	bool(*is_clear)(string_t* s);
	bool(*is_equal)(string_t* s, string_t* compare);

	size_t(*search)(string_t* s, const char* search);
	size_t(*search_string)(string_t* s, string_t* search);
	size_t(*search_char)(string_t* s, char search);

	string_t* (*clear)(string_t* s);
	string_t* (*assign)(string_t* s, const char* newString);
	string_t* (*assign_n)(string_t* s, const char* newString, size_t n, size_t pos);
	string_t* (*assign_string)(string_t* s, string_t* newString);
	string_t* (*assign_string_n)(string_t* s, string_t* newString, size_t n, size_t pos);
	string_t* (*append)(string_t* s, const char* newString);
	string_t* (*append_n)(string_t* s, const char* newString, size_t n, size_t pos);
	string_t* (*append_string)(string_t* s, string_t* newString);
	string_t* (*append_string_n)(string_t* s, string_t* newString, size_t n, size_t pos);
	string_t* (*create_copy)(string_t* s);
	string_t* (*substring)(string_t* s, size_t pos, size_t n);
};


/******************************************************************************/
/* Public functions declarations */
string_t* stringConstructor(const char* baseString);
void stringDestructor(string_t** s);