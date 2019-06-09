%{
void comentario(void);
%}

delim       [ \t\n\r]
ws          {delim}+
digito      [0-9]
letra       [A-Za-z]
ctint       {digito}+
ctreal      {digito}+\.{digito}*([Ee][+-]?{digito}+)?
carac1      \\.|[^\\']
ctcarac     '{carac1}'
carac2      \\.|[^\\\"]
string      \"{carac2}*\"
id          {letra}({letra}|{digito})*


%%
{ws}        { ;}
"/*"        {comentario();}
call        {return CALL;}
functions   {return FUNCTIONS;}
global      {return GLOBAL;}
local       {return LOCAL;}
main        {return MAIN;}
program     {return PROGRAM;}
write       {return WRITE;}
read        {return READ;}
return      {return RETURN;}
statements  {return STATEMENTS;}
char        {return CHAR;}
int         {return INT;}
float       {return FLOAT;}
void        {return VOID;}
logic       {return LOGIC;}
true        {return TRUE;}
false       {return FALSE;}
if          {return IF;}
else        {return ELSE;}
do          {return DO;}
for         {return FOR;}
while       {return WHILE;}
{id}        {strcpy (yylval.cadeia, yytext); return ID;}
{ctint}     {yylval.valint = atoi(yytext); return INTCT;}
{ctreal}    {yylval.valreal = atof(yytext); return FLOATCT;}
{ctcarac}   {strcpy (yylval.cadeia, yytext); return CHARCT;}
{string}    {strcpy (yylval.cadeia, yytext); return STRING;}
"<"         {yylval.atr = LT; return RELOP;}
"<="        {yylval.atr = LE; return RELOP;}
">"         {yylval.atr = GT; return RELOP;}
">="        {yylval.atr = GE; return RELOP;}
"="         {yylval.atr = EQ; return RELOP;}
"!="        {yylval.atr = NE; return RELOP;}
"||"        {return OR;}
"&&"        {return AND;}
"!"         {return NOT;}
"~"         {return NEG;}
"+"         {yylval.atr = MAIS; return ADOP;}
"-"         {yylval.atr = MENOS; return ADOP;}
"*"         {yylval.atr = VEZES; return MULTOP;}
"/"         {yylval.atr = DIV; return MULTOP;}
"%"         {yylval.atr = MOD; return MULTOP;}
"<-"        {return ASSIGN;}
"("         {return OPPAR;}
")"         {return CLPAR;}
"["         {return OPBRAK;}
"]"         {return CLBRAK;}
"{"         {return OPBRACE;}
"}"         {return CLBRACE;}
";"         {return SCOLON;}
","         {return COMMA;}
":"         {return COLON;}
.           {yylval.carac = yytext[0]; return INVAL;}
%%

void comentario () {
	char c;
	int estado;
	estado = 1;
	while (estado != 3) {
		switch (estado) {
			case 1:
				c = input ();
				if (c == EOF) estado = 3;
				else if (c == '*') estado = 2;
				break;
			case 2:
				c = input ();
				if (c == EOF || c == '/') estado = 3;
				else if (c == '*') estado = 2;
				else estado = 1;
				break;
		}
	}
}
