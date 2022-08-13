#include "main.h"

bool is_var(Line line, char** position) {
	char* pos = *position;
	bool result = line[0] >= 'A' && line[0] <= 'Z';
	pos++;
	*position = pos;
	return result;
}
