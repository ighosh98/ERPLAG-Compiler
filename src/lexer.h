#ifndef LEXER_FILE
#define LEXER_FILE
#include<stdio.h>
typedef struct token{
    char* str;
    type tag;
    struct token * next;    
}token;
typedef enum terms{
program,
moduleDeclarations,
otherModules,
driverModule,
moduleDeclaration,
moduleDef,
module,
input_plist,
N1,
ret,
output_plist,
N2,
dataType,
type,
range,
statements,
statement,
ioStmt,
simpleStmt,
declareStmt,
condionalStmt,
iterativeStmt,
var,
whichId,
assignmentStmt,
moduleReuseStmt,
whichStmt,
lvalueIDStmt,
lvalueARRStmt,
expression,
index,
optional,
idList,
idListprime,
arithmeticExpr,
op1,
term,
arithmeticExprprime,
op2,
factor,
N4,
arithmeticOrBooleanExpr,
AnyTerm,
logicalOp,
relationalOp,
caseStmts,
default,
N7,
N8,
N9,
value,
$,
INTEGER,
REAL,
BOOLEAN,
OF,
ARRAY,
START,
END,
DECLARE,
MODULE,
DRIVER,
PROGRAM,
GET_VALUE,
PRINT,
USE,
WITH,
PARAMETERS,
TRUE,
FALSE,
TAKES,
INPUT,
RETURNS,
AND,
OR,
FOR,
IN,
SWITCH,
CASE,
BREAK,
DEFAULT,
WHILE,
PLUS,
MINUS,MUL,
DIV,
LT,
LE,
GE,
GT,
EQ,
NE,
DEF,
ENDDEF,
DRIVERDEF,
DRIVERENDDEF,
COLON,
RANGEOP,
SEMICOL,
COMMA,
ASSIGNOP,
SQBO,
SQBC,
BO,
BC,
COMMENTMARK,
ID,
NUM,
RNUM,
eps}terms;                    
                        
extern token *getNextToken();

extern FILE* getStream(FILE *fp);

extern void removeComments(char* testfile, char* cleanfile);

extern int getLineNumber();
#endif
