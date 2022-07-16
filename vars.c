#include "main.h"

extern uint8_t lastError;

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
	
	/* Set up the name */
	var->name = calloc(length + 1, sizeof(char));
	if (var->name == NULL) {
		free(var);
		lastError = MEMORY_ERROR;
		return NULL;
	}
	for (i=0; i<length; i++) var->name[i] = raw[i];
	
	/* Set up the value */
	var->value = calloc(BUFFER_MAX - length + 1, sizeof(char));
	if (var->value == NULL) {
		free(var);
		free(var->name);
		lastError = MEMORY_ERROR;
		return NULL;
	}
	strncpy(var->value, equals + 1, BUFFER_MAX - length + 1);
	return var;
}

void FreeVariable(Variable* var, bool freeAll) {
	if (var == NULL) return;
	if (freeAll) FreeVariable(var->next, true);
	if (var->name != NULL) free(var->name);
	if (var->value != NULL) free(var->value);
	free(var);
}

Variable* GetVariable(Variable* first, char* name) {
	#if DEBUG_MODE
	printf("Searching for: \"%s\"\n", name);
	#endif
	Variable* current = first;
	while(current != NULL) {
		#if DEBUG_MODE
		printf("\"%s\" = \"%s\"\n", current->name, current->value);
		#endif
		if (strcmp(current->name, name) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}

void SetVariable(Variable * first, char* raw) {
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
	
	/* Set up the name */
	name = calloc(length + 1, sizeof(char));
	if (name == NULL) {
		lastError = MEMORY_ERROR;
		return;
	}
	for (i=0; i<length; i++) name[i] = raw[i];
	
	/* Check if a variable named name already exists;
	if so, reset its value. */
	current = GetVariable(first, name);
		if (current != NULL) {
		if (current->value != NULL) {
			free(current->value);
			current->value = NULL;
		}
		current->value = calloc(BUFFER_MAX - length + 1, sizeof(char));
		if (current->value == NULL) {
			strncpy(raw, "?MEMORY ERROR", BUFFER_MAX);
			free(name);
			return;
		}
		strncpy(current->value, equals + 1, BUFFER_MAX - length + 1);
	}
	
	/* If it gets here, create a new variable */
	current = first;
	while(current != NULL && current->next != NULL) {
		current = current->next;
	}
	current->next = CreateVariable(raw);
	if (current->next == NULL)
		lastError = MEMORY_ERROR;
	free(name);
}

void ReplaceVariablesWithValues(Variable* first, char* line) {
	/* Declare variables */
	Variable* current;
	char* position;
	char value[BUFFER_MAX];
	size_t i;
	
	/* Loop through all the variables, looking for each */
	current = first;
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
			printf("Found %s.  Now replace it.\n", current->name);
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
