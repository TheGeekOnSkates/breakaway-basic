#include "main.h"

void UnTokenize(unsigned char* tokens, FILE* where) {
	size_t i;
	for (i = 0; i < INPUT_BUFFER_SIZE; i++) {
		switch(tokens[i]) {
			case ABS: fprintf(where, " ABS("); break;
			case ALL: fprintf(where, " ALL"); break;
			case AND: fprintf(where, " AND"); break;
			case AS: fprintf(where, " AS"); break;
			case ASC: fprintf(where, " ASC("); break;
			case ATN: fprintf(where, " ATN("); break;
			case AUTO: fprintf(where, " AUTO"); break;
			case BACKSLASH: printf("\\"); break;
			case BEEP: fprintf(where, " BEEP"); break;
			case BIN: fprintf(where, " BIN$("); break;
			case BOLD: fprintf(where, " BOLD"); break;
			case CDBL: fprintf(where, " CDBL("); break;
			case CD: fprintf(where, " CHDIR"); break;
			case CHAIN: fprintf(where, " CHAIN"); break;
			case CHR: fprintf(where, " CHR$("); break;
			case CINT: fprintf(where, " CINT("); break;
			case CLEAR: fprintf(where, " CLEAR"); break;
			case CLOSE: fprintf(where, " CLOSE"); break;
			case CLS: fprintf(where, " CLS"); break;
			case COLON: fprintf(where, ":"); break;
			case COLOR: fprintf(where, " COLOR"); break;
			case COMMA: fprintf(where, ","); break;
			case COMMON: fprintf(where, " COMMON"); break;
			case CONT: fprintf(where, " CONT"); break;
			case COS: fprintf(where, " COS("); break;
			case CSNG: fprintf(where, " CSNG("); break;
			case CVD: fprintf(where, " CVD("); break;
			case CVI: fprintf(where, " CVI("); break;
			case CVL: fprintf(where, " CVL("); break;
			case CVS: fprintf(where, " CVS("); break;
			case CSRLIN: fprintf(where, " CSRLIN"); break;
			case CURSES: fprintf(where, " CURSES"); break;
			case DASH: fprintf(where, "-"); break;
			case DATA: fprintf(where, " DATA"); break;
			case DATE: fprintf(where, " DATE$"); break;
			case DBL: fprintf(where, " DBL"); break;
			case DEF: fprintf(where, " DEF"); break;
			case DIM: fprintf(where, " DIM"); break;
			case DOUBLE_STAR: fprintf(where, "**"); break;
			case FIELD: fprintf(where, " FIELD"); break;
			case FILES: fprintf(where, " FILES"); break;
			case FN: fprintf(where, " FN"); break;
			case FOR: fprintf(where, " FOR"); break;
			case GET: fprintf(where, " GET"); break;
			/*
			LEFT OFF HERE
			
			All of the above are working, both on the Tokenize side and here.
			Keep testing the others, checking to make sure all tokens in the
			Tokens enum are accounted for and work correctly.
			*/
			case GOSUB: fprintf(where, " GOSUB"); break;
			case GOTO: fprintf(where, " GOTO"); break;
			case GREATER_THAN_OR_EQUAL: fprintf(where, ">="); break;
			case GREATER_THAN: fprintf(where, ">"); break;
			case HASH: fprintf(where, "#"); break;
			case HAT: fprintf(where, "^"); break;
			case HEX: fprintf(where, " HEX$"); break;
			case IF: fprintf(where, " IF"); break;
			case INPUT: fprintf(where, " INPUT"); break;
			case KILL: fprintf(where, " KILL"); break;
			case LEFT: fprintf(where, " LEFT$("); break;
			case LET: fprintf(where, " LET"); break;
			case LIST: fprintf(where, " LIST"); break;
			case LOAD: fprintf(where, " LOAD"); break;
			case LOCATE: fprintf(where, " LOCATE"); break;
			case LOG: fprintf(where, " LOG$"); break;
			case MKDIR: fprintf(where, " MKDIR"); break;
			case LEFT_BRACKET: fprintf(where, "["); break;
			case LEFT_PAREN: fprintf(where, "("); break;
			case LESS_THAN_OR_EQUAL: fprintf(where, "<="); break;
			case LESS_THAN: fprintf(where, "<="); break;
			case NUMBER: fprintf(where, "{number}"); break;
			case PLUS: fprintf(where, "+"); break;
			case PRINT: fprintf(where, " PRINT"); break;
			case REM: fprintf(where, " REM%s", &tokens[1]); return;
			case RIGHT_BRACKET: fprintf(where, "]"); break;
			case RIGHT_PAREN: fprintf(where, ")"); break;
			case SLASH: printf("/"); break;
			case STAR: fprintf(where, "*"); break;
			case NONE:
				/* 0, like a NULL terminator, end of line */
				return;
			default:
				fprintf(where, "\r\nTO-DO: un-tokenize %d\r\n", tokens[i]);
				break;
		}
	}
}
