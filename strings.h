#ifndef _STRINGS_H
#define _STRINGS_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Checks if string A = string B, case-insensitive
 * @param[in] a The first string
 * @param[in] b The second string
 * @returns True if strings A and B contain the same text, not taking
 * upper/lower-case into consideration (so i.e. "cOOl" and "Cool" match).
 * @remarks If you want a case-sensitive match, just use strcmp :)
 */
bool StringEquals(char* a, const char* b) {
	size_t i = 0, lengthA = 0, lengthB = 0;

	/* Obviously, if one is NULL and the other is not, then no */
	if ((a == NULL && b != NULL) || (a != NULL && b == NULL)) return false;

	/* If the strings are not the same length, then obviously, no */
	lengthA = strlen(a); lengthB = strlen(b);
	if (lengthA != lengthB) return false;

	/* Obvious stuff dealt with; time for a char-by-char check */
	for (; i<lengthA; i++) if (toupper(a[i]) != toupper(b[i])) return false;

	/* If it gets here, then yes :) */
	return true;
}

bool StringStartsWith(char* a, const char* b) {
	size_t i = 0, lengthA = 0, lengthB = 0;

	/* If either one is NULL, then obviously no */
	if (a == NULL || b == NULL) return false;
	
	/* If string A is shorter than string B, then obviously, no */
	lengthA = strlen(a); lengthB = strlen(b);
	if (lengthA < lengthB) return false;
	
	/* Obvious stuff dealt with; time for a char-by-char check */
	for (; i<lengthB; i++) if (toupper(a[i]) != toupper(b[i])) return false;
	
	/* If it gets here, then yes :) */
	return true;
}

#endif
