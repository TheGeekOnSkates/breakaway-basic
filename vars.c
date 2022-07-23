#include "main.h"

extern uint8_t lastError;

Variable* firstVar = NULL, * firstAlias = NULL;

Variable* CreateVariable(char* raw) {
	/* Declare variables */
	Variable* var;
	size_t i, length;
	char* equals;
	
	/* Set up the variable we'll return later */
	var = malloc(sizeof(Variable));
	if (var == NULL) {
		lastError = MEMORY_ERROR;
		return NULL;
	}
	var->next = NULL;
	
	/* Get the position of the equals sign */
	equals = strchr(raw, '=');
	if (equals == NULL) {
		free(var);
		lastError = SYNTAX_ERROR;
		return NULL;
	}
	i = 0;
	length = equals - raw;
	
	/* Set up the memory for the name */
	var->name = calloc(length + 1, sizeof(char));
	if (var->name == NULL) {
		free(var);
		lastError = MEMORY_ERROR;
		return NULL;
	}
	
	/* Copy the variable name into that memory */
	for (i=0; i<length; i++) {
		if (raw[i] == ' ') {
			/* It found one space, so move pass all spaces */
			while(raw[i] == ' ') i++;
			
			/* If it's not at an equals sign, the user goofed */
			if (raw[i] != '=') {
				free(var);
				lastError = SYNTAX_ERROR;
				return NULL;
			}
			
			/* Then break regardless, cuz we're at the end of
			the variable's name */
			break;
		}
		
		/* Otherwise, it's a character that works in variable names,
		so add it to the name */
		var->name[i] = raw[i];
		var->name[i + 1] = '\0';
	}
	
	/* Set up the memory to store the value */
	var->value = calloc(BUFFER_MAX - length + 1, sizeof(char));
	if (var->value == NULL) {
		free(var);
		free(var->name);
		lastError = MEMORY_ERROR;
		return NULL;
	}
	
	/* Make sure we're past any leading spaces */
	equals++;	/* past the actual = sign */
	while(equals[0] == ' ') equals++;
	
	#if DEBUG_MODE
	printf("equals = \"%s\"\n", equals);
	#endif
	
	/* Copy the value into the variable */
	strncpy(var->value, equals, BUFFER_MAX - length + 1);
	return var;
}

void FreeVariables(Variable* v) {
	if (v == NULL) return;
	FreeVariables(v->next);
	if (v->name != NULL) free(v->name);
	if (v->value != NULL) free(v->value);
	free(v);
}

Variable* GetVariable(char* name, bool isAlias) {
	#if DEBUG_MODE
	/* Check your inputs */
	printf("Name = \"%s\" (%s)\n", name, isAlias ? "alias" : "variable");
	#endif
	
	Variable* current = isAlias ? firstAlias : firstVar;
	if (current == NULL) return NULL;
	
	while(current != NULL) {
		if (current->name == NULL) {
			#if DEBUG_MODE
			printf("current->name is NULL\n");
			#endif
			return NULL;
		}
		
		#if DEBUG_MODE
		printf("\"%s\" = \"%s\"\n", current->name, current->value);
		#endif
		if (strcmp(current->name, name) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}

void SetVariable(char* raw, bool isAlias) {
	Variable* current = NULL;
	char* equals, * name;
	size_t i, length;
	
	/* Get the position of the equals sign */
	equals = strchr(raw, '=');
	if (equals == NULL) {
		lastError = SYNTAX_ERROR;
		return;
	}
	i = 0;
	length = equals - raw;
	
	/* Set up the memory for the name */
	name = calloc(length + 1, sizeof(char));
	if (name == NULL) {
		lastError = MEMORY_ERROR;
		return;
	}
	
	/* Copy the variable name into that memory */
	for (i=0; i<length; i++) {
		if (raw[i] == ' ') {
			/* It found one space, so move pass all spaces */
			while(raw[i] == ' ') i++;
			
			/* If it's not at an equals sign, the user goofed */
			if (raw[i] != '=') {
				lastError = SYNTAX_ERROR;
				return;
			}
			
			/* Then break regardless, cuz we're at the end of
			the variable's name */
			break;
		}
		
		/* Otherwise, it's a character that works in variable names,
		so add it to the name */
		name[i] = raw[i];
		name[i + 1] = '\0';
	}
	
	#if DEBUG_MODE
	printf("Name = \"%s\"\n", name);
	#endif
	
	/* Check if a variable named name already exists;
	if so, reset its value. */
	current = GetVariable(name, isAlias);
	if (current != NULL) {
		if (current->value != NULL) {
			free(current->value);
			current->value = NULL;
		}
		current->value = calloc(BUFFER_MAX - length + 1, sizeof(char));
		if (current->value == NULL) {
			lastError = MEMORY_ERROR;
			free(name);
			return;
		}
		#if DEBUG_MODE
		printf("equals + 1 = %s.\n", equals + 1);
		#endif
		
		equals++;	/* past the actual = sign */
		while(equals[0] == ' ') equals++;
		strncpy(current->value, equals, BUFFER_MAX - length + 1);
		#if DEBUG_MODE
		printf("current->value = %s\n", current->value);
		#endif
		return;
	}
	
	/* If it gets here, create a new variable */
	current = isAlias ? firstAlias : firstVar;
	while(current != NULL && current->next != NULL) {
		#if DEBUG_MODE
		printf("SetVariable: current->name = \"%s\"\n", current->name);
		#endif
		current = current->next;
	}
	current->next = CreateVariable(raw);
	if (current->next == NULL)
		lastError = MEMORY_ERROR;
	if (name != NULL) free(name);
}

void ReplaceVariablesWithValues(char* line) {
	/* Declare variables */
	Variable* current;
	char* position;
	char value[BUFFER_MAX];
	size_t i;
	
	/* Loop through all the variables, looking for each */
	current = firstVar;
	while(current != NULL) {
		#if DEBUG_MODE
		printf("Looking for \"%s\"\n", current->name);
		#endif
		
		/* Loop through all occurrences of the variable,
		replacing its name with its value */
		while(true) {
			if (current->name == NULL) break;
			position = strstr(line, current->name);
			if (position == NULL) break;
			
			#if DEBUG_MODE
			printf("Found \"%s\".\n", current->name);
			#endif
			
			/* Now that we found it, we need to strip out the
			trailing new-line character from the value */
			for (i=0; i<BUFFER_MAX; i++) {
				if (current->value[i] == '0' || current->value[i] == '\n') break;
				value[i] = current->value[i];
			}
			
			ReplaceWithString(line, position - line, position - line + strlen(current->name), value);
			#if DEBUG_MODE
			printf("Now line = %s\n", line);
			#endif
		}
		current = current->next;
	}
}

void ReplaceAliases(char* buffer) {
	Variable* current = firstAlias;
	while(current != NULL) {
		if (STRING_STARTS_WITH(buffer, current->name)) {
			ReplaceWithString(buffer, 0, strlen(current->name), current->value);
			return;
		}
		current = current->next;
	}
}
