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

void FreeVariables(Variable* v) {
	if (v == NULL) return;
	FreeVariables(v->next);
	if (v->name != NULL) free(v->name);
	if (v->value != NULL) free(v->value);
	free(v);
}

Variable* GetVariable(char* name, bool isAlias) {
	#if DEBUG_MODE
	printf("Searching for: \"%s\"\n", name);
	#endif
	Variable* current = isAlias ? firstAlias : firstVar;
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
	
	/* Set up the name */
	name = calloc(length + 1, sizeof(char));
	if (name == NULL) {
		lastError = MEMORY_ERROR;
		return;
	}
	for (i=0; i<length; i++) {
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
		strncpy(current->value, equals + 1, BUFFER_MAX - length + 1);
		#if DEBUG_MODE
		printf("current->value = %s\n", current->value);
		#endif
		return;
	}
	
	/* If it gets here, create a new variable */
	current = isAlias ? firstAlias : firstVar;
	while(current != NULL && current->next != NULL) {
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

void ReplaceAliases(char* buffer) {
	Variable* current = firstAlias;
	while(current != NULL) {
		if (STRING_STARTS_WITH(buffer, current->name)) {
			printf("Found it!\n");
			ReplaceWithString(buffer, 0, strlen(current->name), current->value);
			printf("buffer = \"%s\"\n", buffer);
			return;
		}
		current = current->next;
	}
}
