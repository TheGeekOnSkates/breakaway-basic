#include "main.h"

/*
LEFT OFF HERE

To depuzzle this, my strategy is (once again) to use a stack.  The code below
parses the expression into an array of floats.  I expect to be using floats in
the future, as most BASICs do (and u never know when I might).  But this was an
experiment, a small step in what I think is the right direction.  What I need
to do next is probably something like this:
	1. Put all this logic inside an "is_expr" or something.  Don't forget,
		this function will have to handle expressions in PRINT, which
		expects an expr_list (not to mention we'll need to get the code
		between IF and THEN).
	2. Scheme up some clever hack to make the logic work.  Obviously I'm
		not very good at depuzzling (even in Zelda I always hated
		the puzles, lol) but if God is in it, a solution will come.
		Shoot, just the fact that I thought "stack" is a good start! :)
	3. Geek-rig a string-replace function better than what I had before
	4. Put it all together somehow.
*/
void eval_expr(Line line) {
	/* Declare vars */
	float numbers[LINE_SIZE];
	size_t counter = 0, size = 0;
	char* pos = line, * temp = line;
	
	/* Parse the string into a stack */
	while(true) {
		while(pos[0] == ' ') pos++;
		temp = pos;
		if (pos[0] == 0) break;
		if (is_number(pos, &pos)) {
			numbers[counter] = atof(temp);
			counter++;
		}
		while(pos[0] == ' ') pos++;
		if (!is_math_action(pos[0])) break;
		numbers[counter] = pos[0];
		counter++;
		pos++;
	}
	size = counter;
	
	/* Dummy code to prevent compiler warnings
	I'll be using both "numbers" and "size" next time... */
	if (size == 1)
		printf("(size = %g)", numbers[size - 1]);
}
