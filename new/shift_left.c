#include "main.h"

void shift_left(char* string, size_t start, size_t length) {
        size_t i;
        for (i = start + 1; i < length; i++) {
                string[i - 1] = string[i];
                string[i] = ' ';
        }
}
