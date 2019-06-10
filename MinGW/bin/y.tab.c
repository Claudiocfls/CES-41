#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 2 ".\lab_4.y"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define      LT         1
#define      LE         2
#define      GT         3
#define      GE         4
#define      EQ         5
#define      NE         6
#define      VEZES      1
#define      DIV        2
#define      MOD        3
#define      MAIS       1
#define      MENOS      2
int tab = 0;
int control_tab = 1;

/*   Definicao dos tipos de identificadores   */

#define 	  IDPROG		  1
#define 	  IDVAR		    2
#define     IDFUNC      3

/*  Definicao dos tipos de variaveis   */

#define 	  NAOVAR		  0
#define 	  INTEIRO		  1
#define 	  LOGICO		  2
#define 	  REAL		    3
#define 	  CARACTERE	  4

/*   Definicao de outras constantes   */

#define	    NCLASSHASH	23
#define	    VERDADE		  1
#define	    FALSO		    0

/*  Strings para nomes dos tipos de identificadores  */

char *nometipid[3] = {" ", "IDPROG", "IDVAR"};

/*  Strings para nomes dos tipos de variaveis  */

char *nometipvar[5] = {"NAOVAR","INTEIRO", "LOGICO", "REAL", "CARACTERE"};

/*    Declaracoes para a tabela de simbolos     */

typedef struct celsimb celsimb;
typedef celsimb *simbolo;
struct celsimb {
	char *cadeia;
	int tid, tvar;
	char inic, ref;
	simbolo prox;
};

/*  Variaveis globais para a tabela de simbolos e analise semantica */

simbolo tabsimb[NCLASSHASH];
simbolo simb;
int tipocorrente;

/*
	Prototipos das funcoes para a tabela de simbolos
    	e analise semantica
 */

void InicTabSimb (void);
void ImprimeTabSimb (void);
simbolo InsereSimb (char *, int, int);
int hash (char *);
simbolo ProcuraSimb (char *);
void DeclaracaoRepetida (char *);
void TipoInadequado (char *);
void NaoDeclarado (char *);
void VerificaInicRef (void);
void Incompatibilidade (char *);

#line 82 ".\lab_4.y"
typedef union {
	char cadeia[50];
	int atr, valint;
	float valreal;
	char carac;
	simbolo simb;
	int tipoexpr;
} YYSTYPE;
#line 100 "y.tab.c"
#define ELSE 257
#define IF 258
#define WHILE 259
#define ID 260
#define INTCT 261
#define RELOP 262
#define INVAL 263
#define FLOATCT 264
#define CHARCT 265
#define STRING 266
#define CHAR 267
#define DO 268
#define FALSE 269
#define FLOAT 270
#define FOR 271
#define FUNCTIONS 272
#define GLOBAL 273
#define INT 274
#define LOCAL 275
#define LOGIC 276
#define MAIN 277
#define PROGRAM 278
#define READ 279
#define RETURN 280
#define STATEMENTS 281
#define TRUE 282
#define VOID 283
#define WRITE 284
#define OR 285
#define AND 286
#define NOT 287
#define NEG 288
#define ADOP 289
#define MULTOP 290
#define ASSIGN 291
#define OPPAR 292
#define CLPAR 293
#define OPBRAK 294
#define CLBRAK 295
#define OPBRACE 296
#define CLBRACE 297
#define SCOLON 298
#define COMMA 299
#define COLON 300
#define CALL 301
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    9,   10,   11,   13,    0,   12,   15,   17,   12,   16,
   16,   18,   19,   19,   19,   19,   19,   20,   22,   20,
   24,   21,   23,   26,   23,   25,   27,   25,   28,   30,
   14,   29,   29,   34,   31,   32,   36,   38,   32,   37,
   37,   39,   41,   39,   40,   33,   42,   43,   33,   44,
   46,   35,   45,   45,   47,   47,   47,   47,   47,   47,
   47,   47,   47,   47,   47,   58,   48,   59,   60,   61,
   49,   62,   63,   62,   64,   65,   66,   50,   67,   68,
   69,   70,   51,   71,   72,   73,   74,   75,   76,   77,
   52,   78,   80,   81,   53,   79,   82,   79,   83,   85,
   86,   54,   84,   88,   84,   87,   87,   90,   56,   91,
   93,   89,   92,   92,   95,   57,   96,   57,   97,   98,
   99,   55,   94,  100,   94,    2,  101,    2,    3,  102,
    3,    4,  103,    4,    5,  104,    5,    6,  105,    6,
    7,  106,    7,    8,    8,    8,    8,    8,    8,  107,
    8,  108,  109,    8,    8,  111,    1,  110,  113,  110,
  112,  114,  112,
};
short yylen[] = {                                         2,
    0,    0,    0,    0,   10,    0,    0,    0,    5,    1,
    2,    3,    1,    1,    1,    1,    1,    1,    0,    4,
    0,    3,    0,    0,    4,    1,    0,    4,    0,    0,
    5,    1,    2,    0,    6,    1,    0,    0,    7,    0,
    1,    1,    0,    4,    2,    0,    0,    0,    5,    0,
    0,    5,    0,    2,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    0,    4,    0,    0,    0,
    9,    0,    0,    3,    0,    0,    0,    8,    0,    0,
    0,    0,   11,    0,    0,    0,    0,    0,    0,    0,
   20,    0,    0,    0,    8,    1,    0,    4,    0,    0,
    0,    8,    1,    0,    4,    1,    1,    0,    4,    0,
    0,    6,    0,    1,    0,    3,    0,    4,    0,    0,
    0,    7,    1,    0,    4,    1,    0,    4,    1,    0,
    4,    1,    0,    3,    1,    0,    4,    1,    0,    4,
    1,    0,    4,    1,    1,    1,    1,    1,    1,    0,
    3,    0,    0,    5,    1,    0,    3,    0,    0,    4,
    1,    0,    4,
};
short yydefred[] = {                                      1,
    0,    0,    2,    0,    3,    0,    4,    0,    7,    0,
    0,   29,    0,    8,    0,    5,    0,   30,   15,   14,
   13,   16,   17,    0,   10,    0,    0,   11,   21,    0,
   18,   36,    0,    0,   32,    0,    0,   12,   19,   37,
   33,   34,   24,   22,    0,    0,    0,    0,   20,   38,
   47,    0,   26,    0,    0,    0,   50,    0,   25,   27,
    0,    0,    0,   42,   48,    0,   35,    0,   45,   39,
   43,    0,   51,   28,    0,    0,   53,   44,    0,   68,
   75,   79,   84,   92,    0,   99,   66,   65,  108,   54,
   55,   56,   57,   58,   59,   60,   61,   62,   63,   64,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   53,
    0,  156,  120,   69,   76,    0,   85,   93,  116,    0,
  145,  146,  147,  149,  148,  133,  150,  152,  144,    0,
    0,  129,  132,    0,    0,  141,  155,  100,    0,  110,
    0,    0,    0,    0,    0,   80,    0,    0,    0,    0,
    0,    0,  127,  118,  130,  136,  139,  142,    0,   67,
  109,  159,  157,  121,    0,    0,    0,    0,   96,    0,
  111,  134,  151,    0,    0,    0,    0,    0,    0,  106,
    0,    0,  103,    0,    0,   70,   77,   81,   86,   94,
   97,    0,    0,    0,  131,    0,    0,  143,  101,  104,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  154,    0,    0,  160,  162,  122,    0,   78,
    0,    0,   95,   98,  112,  124,  102,  105,    0,   73,
   71,   82,   87,    0,    0,    0,    0,    0,    0,   74,
   83,    0,   88,    0,    0,   89,    0,    0,   90,    0,
   91,
};
short yydgoto[] = {                                       1,
  129,  181,  131,  132,  133,  134,  135,  136,    2,    4,
    6,   10,    8,   13,   11,   24,   17,   25,   26,   30,
   31,   45,   44,   37,   54,   48,   68,   15,   34,   27,
   35,   36,   52,   47,   58,   46,   62,   55,   63,   64,
   75,   56,   72,   66,   79,   77,   90,   91,   92,   93,
   94,   95,   96,   97,   98,   99,  100,  110,  102,  144,
  204,  231,  236,  103,  145,  205,  104,  167,  206,  237,
  105,  147,  207,  238,  244,  247,  250,  106,  170,  148,
  208,  209,  109,  182,  159,  214,  183,  215,  137,  111,
  149,  211,  192,  212,  107,  108,  101,  143,  185,  234,
  175,  176,  150,  177,  178,  179,  151,  152,  193,  163,
  142,  202,  184,  229,
};
short yysindex[] = {                                      0,
    0, -242,    0, -238,    0, -230,    0, -169,    0, -178,
 -164,    0, -159,    0, -157,    0, -207,    0,    0,    0,
    0,    0,    0, -207,    0, -129, -253,    0,    0, -181,
    0,    0, -119, -253,    0, -140, -128,    0,    0,    0,
    0,    0,    0,    0, -129, -133,  -96,  -86,    0,    0,
    0, -101,    0, -215, -207, -116,    0, -111,    0,    0,
  -72,  -97, -110,    0,    0, -107,    0,  -69,    0,    0,
    0, -207,    0,    0, -207, -207,    0,    0, -156,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -61,  -95,  -92, -156,  -89,  -77,  -80,  -48,  -67,    0,
  -59,    0,    0,    0,    0,  -33,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -273,
  -57,    0,    0, -254,  -52,    0,    0,    0, -209,    0,
  -56,  -51,  -60,  -48,  -48,    0,  -61,  -61,  -47,  -41,
  -41,  -48,    0,    0,    0,    0,    0,    0,  -55,    0,
    0,    0,    0,    0, -278, -212,  -46,  -43,    0, -266,
    0,    0,    0,  -36,  -48,  -48,  -41,  -41,  -41,    0,
  -36, -256,    0,  -41,  -48,    0,    0,    0,    0,    0,
    0,  -48,  -40,  -57,    0,  -39,  -52,    0,    0,    0,
  -39, -144, -272, -156, -156,  -48,  -48,  -44,  -61,  -36,
  -38,  -42,    0,  -37,  -55,    0,    0,    0,   -5,    0,
 -194, -269,    0,    0,    0,    0,    0,    0,  -41,    0,
    0,    0,    0,  -48,  -39, -156,  -35,  -48,  -36,    0,
    0, -247,    0,  -61,  -32,    0,  -48, -172,    0, -156,
    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,  -16,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -14,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -31,    0,    0, -149,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -21,    0,    0,    0,
    0,    0,    0,    0,  -29,    0,    0,    0,    0,    0,
    0,    0,  -28,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -19,    0,    0, -255,    0,
    0,    0,    0,    0, -135,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    7,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -125,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -179,    0,    0, -203, -221,    0,    0,    0,    7,    0,
    0, -108,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -25,    0,    0,    0,    0,    0,    0,
 -214,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -24,    0,  -63,    0, -188,  -91,    0,    0,    0,
 -137,    0,    0,    7,    7,    0,    0,    0,    0, -177,
    0,  -20,    0,    0,    0,    0,    0,    0, -240,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -123,    7,    0,    0, -166,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    7,
    0,
};
short yygindex[] = {                                      0,
 -100,  -99,   95,   96,  121, -174,   97, -145,    0,    0,
    0,    0,    0,    0,    0,  202,    0,  -22,  -23,    0,
  231,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  243,    0,    0,    0,    0,    0,    0,    0,    0,  203,
    0,    0,    0,    0,  169,    0, -104,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   65,    0,  170,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,
};
#define YYTABLESIZE 281
short yytable[] = {                                     116,
  113,   28,  196,   33,  119,  173,  153,  156,  130,  201,
   33,  153,  153,   19,  186,  153,   20,   72,   72,   72,
   21,    5,   22,   32,  154,  218,  190,   72,  233,   23,
   72,   61,  191,  198,  157,    3,  199,  153,   72,   72,
  138,   52,  200,   72,  165,  166,  168,  169,   80,   81,
  243,   61,  174,   28,  235,   72,   72,   72,   82,   19,
   72,   83,   20,  138,  138,    7,   21,  138,   22,   84,
   85,  138,  153,  138,   86,   23,  138,  138,  107,   59,
  187,  135,  135,   60,  107,  203,   87,  160,   88,  135,
  153,   89,  210,   12,  135,  135,  137,  137,  232,  219,
  220,   80,   81,    9,  137,  126,  221,  222,  224,  137,
  137,   82,  153,  126,   83,  123,   38,   39,  126,  126,
  249,  123,   84,   85,  117,  117,  125,   86,  117,  117,
   29,  240,  125,  117,  239,   14,  156,   16,  242,   87,
   40,   88,   18,  245,   89,  251,  117,  248,   23,   23,
  216,  117,  117,  158,  217,   42,  117,  161,   50,  156,
  156,  161,  115,  156,  156,   43,  110,  156,  156,  156,
  140,  163,  156,  156,   53,  163,  158,  158,   51,   57,
  158,  158,  158,   65,  158,   67,  158,   69,   71,  158,
  158,   74,   73,  140,  140,   70,  114,  140,  112,  115,
  140,  140,  117,  140,  120,  121,  140,  140,  122,  123,
  180,  120,  121,  124,  118,  122,  123,  119,  120,  121,
  124,  128,  122,  123,  138,  146,  125,  124,  155,  128,
  164,  126,  127,  125,  128,  128,  128,  158,  126,  127,
  125,  161,  162,  128,  171,  188,  127,  189,  153,  157,
  128,  230,  213,  223,  225,    6,  226,    9,  246,   46,
  227,   49,  241,   40,   41,   31,  119,  153,  113,  194,
  172,  195,  114,   76,  197,   49,   41,   78,  139,  228,
  141,
};
short yycheck[] = {                                     104,
  101,   24,  177,   27,  260,  151,  285,  262,  108,  184,
   34,  285,  285,  267,  293,  285,  270,  258,  259,  260,
  274,  260,  276,  277,  298,  298,  293,  268,  298,  283,
  271,   55,  299,  179,  289,  278,  293,  285,  279,  280,
  262,  297,  299,  284,  144,  145,  147,  148,  258,  259,
  298,   75,  152,   76,  229,  296,  297,  298,  268,  267,
  301,  271,  270,  285,  286,  296,  274,  289,  276,  279,
  280,  293,  285,  295,  284,  283,  298,  299,  293,  295,
  293,  285,  286,  299,  299,  185,  296,  297,  298,  293,
  285,  301,  192,  272,  298,  299,  285,  286,  293,  204,
  205,  258,  259,  273,  293,  285,  206,  207,  209,  298,
  299,  268,  285,  293,  271,  293,  298,  299,  298,  299,
  293,  299,  279,  280,  260,  261,  293,  284,  264,  265,
  260,  236,  299,  269,  234,  300,  262,  297,  238,  296,
  260,  298,  300,  244,  301,  250,  282,  247,  298,  299,
  295,  287,  288,  262,  299,  296,  292,  295,  292,  285,
  286,  299,  298,  289,  290,  294,  292,  293,  294,  295,
  262,  295,  298,  299,  261,  299,  285,  286,  275,  281,
  289,  290,  291,  300,  293,  297,  295,  260,  299,  298,
  299,  261,  300,  285,  286,  293,  292,  289,  260,  292,
  260,  293,  292,  295,  260,  261,  298,  299,  264,  265,
  266,  260,  261,  269,  292,  264,  265,  298,  260,  261,
  269,  285,  264,  265,  292,  259,  282,  269,  286,  293,
  291,  287,  288,  282,  298,  299,  292,  290,  287,  288,
  282,  298,  294,  292,  292,  292,  288,  291,  285,  289,
  292,  257,  293,  298,  293,  272,  299,  272,  291,  281,
  298,  281,  298,  293,  293,  297,  260,  293,  293,  175,
  150,  176,  293,   72,  178,   45,   34,   75,  110,  215,
  111,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 301
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ELSE","IF","WHILE","ID","INTCT",
"RELOP","INVAL","FLOATCT","CHARCT","STRING","CHAR","DO","FALSE","FLOAT","FOR",
"FUNCTIONS","GLOBAL","INT","LOCAL","LOGIC","MAIN","PROGRAM","READ","RETURN",
"STATEMENTS","TRUE","VOID","WRITE","OR","AND","NOT","NEG","ADOP","MULTOP",
"ASSIGN","OPPAR","CLPAR","OPBRAK","CLBRAK","OPBRACE","CLBRACE","SCOLON","COMMA",
"COLON","CALL",
};
char *yyrule[] = {
"$accept : Prog",
"$$1 :",
"$$2 :",
"$$3 :",
"$$4 :",
"Prog : $$1 PROGRAM $$2 ID $$3 OPBRACE $$4 GlobDecls Functions CLBRACE",
"GlobDecls :",
"$$5 :",
"$$6 :",
"GlobDecls : GLOBAL $$5 COLON $$6 DeclList",
"DeclList : Declaration",
"DeclList : DeclList Declaration",
"Declaration : Type ElemList SCOLON",
"Type : INT",
"Type : FLOAT",
"Type : CHAR",
"Type : LOGIC",
"Type : VOID",
"ElemList : Elem",
"$$7 :",
"ElemList : ElemList COMMA $$7 Elem",
"$$8 :",
"Elem : ID $$8 Dims",
"Dims :",
"$$9 :",
"Dims : OPBRAK $$9 DimList CLBRAK",
"DimList : INTCT",
"$$10 :",
"DimList : DimList COMMA $$10 INTCT",
"$$11 :",
"$$12 :",
"Functions : FUNCTIONS $$11 COLON $$12 FuncList",
"FuncList : Function",
"FuncList : FuncList Function",
"$$13 :",
"Function : Header OPBRACE $$13 LocDecls Stats CLBRACE",
"Header : MAIN",
"$$14 :",
"$$15 :",
"Header : Type ID $$14 OPPAR $$15 Params CLPAR",
"Params :",
"Params : ParamList",
"ParamList : Parameter",
"$$16 :",
"ParamList : ParamList COMMA $$16 Parameter",
"Parameter : Type ID",
"LocDecls :",
"$$17 :",
"$$18 :",
"LocDecls : LOCAL $$17 COLON $$18 DeclList",
"$$19 :",
"$$20 :",
"Stats : STATEMENTS $$19 COLON $$20 StatList",
"StatList :",
"StatList : StatList Statement",
"Statement : CompStat",
"Statement : IfStat",
"Statement : WhileStat",
"Statement : DoStat",
"Statement : ForStat",
"Statement : ReadStat",
"Statement : WriteStat",
"Statement : AssignStat",
"Statement : CallStat",
"Statement : ReturnStat",
"Statement : SCOLON",
"$$21 :",
"CompStat : OPBRACE $$21 StatList CLBRACE",
"$$22 :",
"$$23 :",
"$$24 :",
"IfStat : IF $$22 OPPAR $$23 Expression CLPAR $$24 Statement ElseStat",
"ElseStat :",
"$$25 :",
"ElseStat : ELSE $$25 Statement",
"$$26 :",
"$$27 :",
"$$28 :",
"WhileStat : WHILE $$26 OPPAR $$27 Expression CLPAR $$28 Statement",
"$$29 :",
"$$30 :",
"$$31 :",
"$$32 :",
"DoStat : DO $$29 Statement WHILE $$30 OPPAR $$31 Expression CLPAR $$32 SCOLON",
"$$33 :",
"$$34 :",
"$$35 :",
"$$36 :",
"$$37 :",
"$$38 :",
"$$39 :",
"ForStat : FOR $$33 OPPAR $$34 Variable ASSIGN $$35 Expression SCOLON $$36 Expression SCOLON $$37 Variable ASSIGN $$38 Expression CLPAR $$39 Statement",
"$$40 :",
"$$41 :",
"$$42 :",
"ReadStat : READ $$40 OPPAR $$41 ReadList CLPAR $$42 SCOLON",
"ReadList : Variable",
"$$43 :",
"ReadList : ReadList COMMA $$43 Variable",
"$$44 :",
"$$45 :",
"$$46 :",
"WriteStat : WRITE $$44 OPPAR $$45 WriteList CLPAR $$46 SCOLON",
"WriteList : WriteElem",
"$$47 :",
"WriteList : WriteList COMMA $$47 WriteElem",
"WriteElem : STRING",
"WriteElem : Expression",
"$$48 :",
"CallStat : CALL $$48 FuncCall SCOLON",
"$$49 :",
"$$50 :",
"FuncCall : ID $$49 OPPAR $$50 Arguments CLPAR",
"Arguments :",
"Arguments : ExprList",
"$$51 :",
"ReturnStat : RETURN $$51 SCOLON",
"$$52 :",
"ReturnStat : RETURN $$52 Expression SCOLON",
"$$53 :",
"$$54 :",
"$$55 :",
"AssignStat : $$53 Variable $$54 ASSIGN $$55 Expression SCOLON",
"ExprList : Expression",
"$$56 :",
"ExprList : ExprList COMMA $$56 Expression",
"Expression : AuxExpr1",
"$$57 :",
"Expression : Expression OR $$57 AuxExpr1",
"AuxExpr1 : AuxExpr2",
"$$58 :",
"AuxExpr1 : AuxExpr1 AND $$58 AuxExpr2",
"AuxExpr2 : AuxExpr3",
"$$59 :",
"AuxExpr2 : NOT $$59 AuxExpr3",
"AuxExpr3 : AuxExpr4",
"$$60 :",
"AuxExpr3 : AuxExpr4 RELOP $$60 AuxExpr4",
"AuxExpr4 : Term",
"$$61 :",
"AuxExpr4 : AuxExpr4 ADOP $$61 Term",
"Term : Factor",
"$$62 :",
"Term : Term MULTOP $$62 Factor",
"Factor : Variable",
"Factor : INTCT",
"Factor : FLOATCT",
"Factor : CHARCT",
"Factor : TRUE",
"Factor : FALSE",
"$$63 :",
"Factor : NEG $$63 Factor",
"$$64 :",
"$$65 :",
"Factor : OPPAR $$64 Expression $$65 CLPAR",
"Factor : FuncCall",
"$$66 :",
"Variable : ID $$66 Subscripts",
"Subscripts :",
"$$67 :",
"Subscripts : OPBRAK $$67 SubscrList CLBRAK",
"SubscrList : AuxExpr4",
"$$68 :",
"SubscrList : SubscrList COMMA $$68 AuxExpr4",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 434 ".\lab_4.y"
#include "lex.yy.c"
tabular() {
  if(control_tab){
    int i;
    for(i = 1; i<=tab;i++)
      printf("\t");
  }
  control_tab = 1;
}

allow_tab() {
  control_tab = 1;
}

no_tab() {
  control_tab = 0;
}

void InicTabSimb () {
	int i;
	for (i = 0; i < NCLASSHASH; i++)
		tabsimb[i] = NULL;
}

/*
	ProcuraSimb (cadeia): Procura cadeia na tabela de simbolos;
	Caso ela ali esteja, retorna um ponteiro para sua celula;
	Caso contrario, retorna NULL.
 */

simbolo ProcuraSimb (char *cadeia) {
	simbolo s; int i;
	i = hash (cadeia);
	for (s = tabsimb[i]; (s!=NULL) && strcmp(cadeia, s->cadeia);
		s = s->prox);
	return s;
}

/*
	InsereSimb (cadeia, tid, tvar): Insere cadeia na tabela de
	simbolos, com tid como tipo de identificador e com tvar como
	tipo de variavel; Retorna um ponteiro para a celula inserida
 */

simbolo InsereSimb (char *cadeia, int tid, int tvar) {
	int i; simbolo aux, s;
	i = hash (cadeia); aux = tabsimb[i];
	s = tabsimb[i] = (simbolo) malloc (sizeof (celsimb));
	s->cadeia = (char*) malloc ((strlen(cadeia)+1) * sizeof(char));
	strcpy (s->cadeia, cadeia);
	s->tid = tid;		s->tvar = tvar;
	s->inic = FALSO;	s->ref = FALSO;
	s->prox = aux;	return s;
}

/*
	hash (cadeia): funcao que determina e retorna a classe
	de cadeia na tabela de simbolos implementada por hashing
 */

int hash (char *cadeia) {
	int i, h;
	for (h = i = 0; cadeia[i]; i++) {h += cadeia[i];}
	h = h % NCLASSHASH;
	return h;
}

/* ImprimeTabSimb: Imprime todo o conteudo da tabela de simbolos  */

void ImprimeTabSimb () {
	int i; simbolo s;
	printf ("\n\n   TABELA  DE  SIMBOLOS:\n\n");
	for (i = 0; i < NCLASSHASH; i++)
		if (tabsimb[i]) {
			printf ("Classe %d:\n", i);
			for (s = tabsimb[i]; s!=NULL; s = s->prox){
				printf ("  (%s, %s", s->cadeia,  nometipid[s->tid]);
				if (s->tid == IDVAR)
					printf (", %s, %d, %d",
						nometipvar[s->tvar], s->inic, s->ref);
				printf(")\n");
			}
		}
}

void VerificaInicRef () {
	int i; simbolo s;

	printf ("\n");
	for (i = 0; i < NCLASSHASH; i++)
		if (tabsimb[i])
			for (s = tabsimb[i]; s!=NULL; s = s->prox)
				if (s->tid == IDVAR) {
					if (s->inic == FALSO)
						printf ("%s: Nao Inicializada\n", s->cadeia);
					if (s->ref == FALSO)
						printf ("%s: Nao Referenciada\n", s->cadeia);
				}
}


/*  Mensagens de erros semanticos  */

void DeclaracaoRepetida (char *s) {
	printf ("\n\n***** Declaracao Repetida: %s *****\n\n", s);
}

void NaoDeclarado (char *s) {
    printf ("\n\n***** Identificador Nao Declarado: %s *****\n\n", s);
}

void TipoInadequado (char *s) {
    printf ("\n\n***** Identificador de Tipo Inadequado: %s *****\n\n", s);
}

void Incompatibilidade (char *s) {
    printf ("\n\n***** Incompatibilidade: %s *****\n\n", s);
}
#line 688 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 141 ".\lab_4.y"
{InicTabSimb ();}
break;
case 2:
#line 142 ".\lab_4.y"
{printf("program ");}
break;
case 3:
#line 143 ".\lab_4.y"
{printf("%s ",yyvsp[0].cadeia); InsereSimb (yyvsp[0].cadeia, IDPROG, NAOVAR);}
break;
case 4:
#line 144 ".\lab_4.y"
{printf("\{\n"); tab++;}
break;
case 5:
#line 147 ".\lab_4.y"
{
                         tab--; tabular();
                         printf ("}\n");
                         VerificaInicRef ();
                         ImprimeTabSimb ();
                     }
break;
case 7:
#line 157 ".\lab_4.y"
{ tab--; tabular(); tab++; printf("global ");}
break;
case 8:
#line 157 ".\lab_4.y"
{printf(":\n");}
break;
case 12:
#line 162 ".\lab_4.y"
{printf(";\n");}
break;
case 13:
#line 164 ".\lab_4.y"
{tabular(); printf("int "); tipocorrente = INTEIRO;}
break;
case 14:
#line 165 ".\lab_4.y"
{tabular(); printf("float "); tipocorrente = REAL;}
break;
case 15:
#line 166 ".\lab_4.y"
{tabular(); printf("char "); tipocorrente = CARACTERE;}
break;
case 16:
#line 167 ".\lab_4.y"
{tabular(); printf("logic "); tipocorrente = LOGICO;}
break;
case 17:
#line 168 ".\lab_4.y"
{tabular(); printf("void ");}
break;
case 19:
#line 171 ".\lab_4.y"
{printf(", ");}
break;
case 21:
#line 174 ".\lab_4.y"
{
                         printf("%s",yyvsp[0].cadeia);
                         if (ProcuraSimb (yyvsp[0].cadeia)  !=  NULL)
                             DeclaracaoRepetida (yyvsp[0].cadeia);
                         else
                             InsereSimb (yyvsp[0].cadeia,  IDVAR,  tipocorrente);
                     }
break;
case 24:
#line 185 ".\lab_4.y"
{printf("\[");}
break;
case 25:
#line 186 ".\lab_4.y"
{printf("]");}
break;
case 26:
#line 188 ".\lab_4.y"
{printf("%d",yyvsp[0].valint);}
break;
case 27:
#line 189 ".\lab_4.y"
{printf(", ");}
break;
case 28:
#line 189 ".\lab_4.y"
{printf("%d",yyvsp[0].valint);}
break;
case 29:
#line 191 ".\lab_4.y"
{tab--; tabular(); tab++; printf("functions");}
break;
case 30:
#line 191 ".\lab_4.y"
{printf(":\n");}
break;
case 34:
#line 196 ".\lab_4.y"
{printf("\{\n"); tab++;}
break;
case 35:
#line 197 ".\lab_4.y"
{tab--; tabular(); printf("}\n");}
break;
case 36:
#line 199 ".\lab_4.y"
{tabular(); printf("main ");}
break;
case 37:
#line 200 ".\lab_4.y"
{printf("%s ",yyvsp[0].cadeia);}
break;
case 38:
#line 200 ".\lab_4.y"
{printf("\(");}
break;
case 39:
#line 200 ".\lab_4.y"
{printf(") ");}
break;
case 43:
#line 206 ".\lab_4.y"
{printf(", ");}
break;
case 45:
#line 208 ".\lab_4.y"
{printf("%s ",yyvsp[0].cadeia);}
break;
case 47:
#line 211 ".\lab_4.y"
{tab--; tabular(); tab++; printf("local");}
break;
case 48:
#line 211 ".\lab_4.y"
{printf(":\n");}
break;
case 50:
#line 213 ".\lab_4.y"
{tab--; tabular(); tab++; printf("statements");}
break;
case 51:
#line 213 ".\lab_4.y"
{printf(":\n");}
break;
case 65:
#line 228 ".\lab_4.y"
{printf(";\n"); allow_tab(); }
break;
case 66:
#line 231 ".\lab_4.y"
{tabular(); printf("\{\n"); tab++;}
break;
case 67:
#line 233 ".\lab_4.y"
{tab--; tabular(); printf("}\n");}
break;
case 68:
#line 235 ".\lab_4.y"
{tabular(); printf("if");}
break;
case 69:
#line 236 ".\lab_4.y"
{printf("\(");}
break;
case 70:
#line 237 ".\lab_4.y"
{printf(") "); no_tab();}
break;
case 73:
#line 240 ".\lab_4.y"
{tabular(); printf("else "); no_tab();}
break;
case 75:
#line 242 ".\lab_4.y"
{tabular(); printf("while");}
break;
case 76:
#line 242 ".\lab_4.y"
{printf("\(");}
break;
case 77:
#line 243 ".\lab_4.y"
{printf(") "); no_tab();}
break;
case 79:
#line 245 ".\lab_4.y"
{tabular(); printf("do "); no_tab();}
break;
case 80:
#line 246 ".\lab_4.y"
{tabular(); printf("while");}
break;
case 81:
#line 246 ".\lab_4.y"
{printf("\(");}
break;
case 82:
#line 247 ".\lab_4.y"
{printf(")");}
break;
case 83:
#line 248 ".\lab_4.y"
{printf(";\n");}
break;
case 84:
#line 250 ".\lab_4.y"
{tabular(); printf("for");}
break;
case 85:
#line 251 ".\lab_4.y"
{printf("\(");}
break;
case 86:
#line 252 ".\lab_4.y"
{printf(" <- ");}
break;
case 87:
#line 253 ".\lab_4.y"
{printf("; ");}
break;
case 88:
#line 254 ".\lab_4.y"
{printf("; ");}
break;
case 89:
#line 255 ".\lab_4.y"
{printf(" <- ");}
break;
case 90:
#line 257 ".\lab_4.y"
{printf(") ");no_tab();}
break;
case 92:
#line 260 ".\lab_4.y"
{tabular(); printf("read");}
break;
case 93:
#line 260 ".\lab_4.y"
{printf("\(");}
break;
case 94:
#line 260 ".\lab_4.y"
{printf(") ");}
break;
case 95:
#line 260 ".\lab_4.y"
{printf(";\n"); }
break;
case 97:
#line 263 ".\lab_4.y"
{printf(", ");}
break;
case 99:
#line 265 ".\lab_4.y"
{tabular(); printf("write");}
break;
case 100:
#line 265 ".\lab_4.y"
{printf("\(");}
break;
case 101:
#line 265 ".\lab_4.y"
{printf(")");}
break;
case 102:
#line 265 ".\lab_4.y"
{printf(";\n"); }
break;
case 104:
#line 268 ".\lab_4.y"
{printf(", ");}
break;
case 106:
#line 270 ".\lab_4.y"
{printf("%s",yyvsp[0].cadeia);}
break;
case 108:
#line 273 ".\lab_4.y"
{tabular(); printf("call ");}
break;
case 109:
#line 273 ".\lab_4.y"
{printf(";\n");}
break;
case 110:
#line 275 ".\lab_4.y"
{printf("%s",yyvsp[0].cadeia);}
break;
case 111:
#line 275 ".\lab_4.y"
{printf("\(");}
break;
case 112:
#line 275 ".\lab_4.y"
{printf(") ");}
break;
case 115:
#line 280 ".\lab_4.y"
{tabular(); printf("return ");}
break;
case 116:
#line 280 ".\lab_4.y"
{printf(";\n");}
break;
case 117:
#line 281 ".\lab_4.y"
{tabular(); printf("return ");}
break;
case 118:
#line 281 ".\lab_4.y"
{printf(";\n");}
break;
case 119:
#line 283 ".\lab_4.y"
{tabular();}
break;
case 120:
#line 285 ".\lab_4.y"
{if  (yyvsp[0].simb != NULL) yyvsp[0].simb->inic = yyvsp[0].simb->ref = VERDADE;}
break;
case 121:
#line 286 ".\lab_4.y"
{printf(" <- ");}
break;
case 122:
#line 288 ".\lab_4.y"
{
                         printf (";\n");
                         if (yyvsp[-5].simb != NULL)
                             if (((yyvsp[-5].simb->tvar == INTEIRO || yyvsp[-5].simb->tvar == CARACTERE) &&
                                 (yyvsp[-1].tipoexpr == REAL || yyvsp[-1].tipoexpr == LOGICO)) ||
                                 (yyvsp[-5].simb->tvar == REAL && yyvsp[-1].tipoexpr == LOGICO) ||
                                 (yyvsp[-5].simb->tvar == LOGICO && yyvsp[-1].tipoexpr != LOGICO))
                                 Incompatibilidade ("Lado direito de comando de atribuicao improprio");
                     }
break;
case 124:
#line 299 ".\lab_4.y"
{printf(", ");}
break;
case 127:
#line 302 ".\lab_4.y"
{printf(" || ");}
break;
case 128:
#line 303 ".\lab_4.y"
{
                       if (yyvsp[-3].tipoexpr != LOGICO || yyvsp[0].tipoexpr != LOGICO)
                          Incompatibilidade ("Operando improprio para operador or");
                       yyval.tipoexpr = LOGICO;
                     }
break;
case 130:
#line 310 ".\lab_4.y"
{printf(" && ");}
break;
case 131:
#line 311 ".\lab_4.y"
{
                       if (yyvsp[-3].tipoexpr != LOGICO || yyvsp[0].tipoexpr != LOGICO)
                           Incompatibilidade ("Operando improprio para operador and");
                       yyval.tipoexpr = LOGICO;
                     }
break;
case 133:
#line 318 ".\lab_4.y"
{printf("!");}
break;
case 134:
#line 319 ".\lab_4.y"
{
                       if (yyvsp[0].tipoexpr != LOGICO)
                           Incompatibilidade ("Operando improprio para operador not");
                       yyval.tipoexpr = LOGICO;
                     }
break;
case 136:
#line 327 ".\lab_4.y"
{
                       switch(yyvsp[0].atr){
                         case LT: printf(" < "); break;
                         case LE: printf(" <= "); break;
                         case GT: printf(" > "); break;
                         case GE: printf(" >= "); break;
                         case EQ: printf(" = "); break;
                         case NE: printf(" != "); break;
                       }
                     }
break;
case 137:
#line 337 ".\lab_4.y"
{
                         switch (yyvsp[-2].atr) {
                             case LT: case LE: case GT: case GE:
                                 if (yyvsp[-3].tipoexpr != INTEIRO && yyvsp[-3].tipoexpr != REAL && yyvsp[-3].tipoexpr != CARACTERE || yyvsp[0].tipoexpr != INTEIRO && yyvsp[0].tipoexpr != REAL && yyvsp[0].tipoexpr != CARACTERE)
                                     Incompatibilidade	("Operando improprio para operador relacional");
                                 break;
                             case EQ: case NE:
                                 if ((yyvsp[-3].tipoexpr == LOGICO || yyvsp[0].tipoexpr == LOGICO) && yyvsp[-3].tipoexpr != yyvsp[0].tipoexpr)
                                     Incompatibilidade ("Operando improprio para operador relacional");
                                 break;
                         }
                         yyval.tipoexpr = LOGICO;
                     }
break;
case 139:
#line 353 ".\lab_4.y"
{
                       if(yyvsp[0].atr == MAIS)
                         printf(" + ");
                       else
                         printf(" - ");
                     }
break;
case 140:
#line 358 ".\lab_4.y"
{
                         if (yyvsp[-3].tipoexpr != INTEIRO && yyvsp[-3].tipoexpr != REAL && yyvsp[-3].tipoexpr != CARACTERE || yyvsp[0].tipoexpr != INTEIRO && yyvsp[0].tipoexpr!=REAL && yyvsp[0].tipoexpr!=CARACTERE)
                             Incompatibilidade ("Operando improprio para operador aritmetico 1");
                         if (yyvsp[-3].tipoexpr == REAL || yyvsp[0].tipoexpr == REAL) yyval.tipoexpr = REAL;
                         else yyval.tipoexpr = INTEIRO;
                     }
break;
case 142:
#line 367 ".\lab_4.y"
{
                       if(yyvsp[0].atr == VEZES)
                         printf(" * ");
                       else if(yyvsp[0].atr == DIV)
                         printf(" / ");
                       else
                         printf(" % ");
                     }
break;
case 143:
#line 374 ".\lab_4.y"
{
                         switch (yyvsp[-2].atr) {
                             case VEZES: case DIV:
                                 if (yyvsp[-3].tipoexpr != INTEIRO && yyvsp[-3].tipoexpr != REAL && yyvsp[-3].tipoexpr != CARACTERE
                                     || yyvsp[0].tipoexpr != INTEIRO && yyvsp[0].tipoexpr!=REAL && yyvsp[0].tipoexpr != CARACTERE) {
                                     Incompatibilidade ("Operando improprio para operador aritmetico 2");
                                   }
                                 if (yyvsp[-3].tipoexpr == REAL || yyvsp[0].tipoexpr == REAL) yyval.tipoexpr = REAL;
                                 else yyval.tipoexpr = INTEIRO;
                                 break;
                             case MOD:
                                 if (yyvsp[-3].tipoexpr != INTEIRO && yyvsp[-3].tipoexpr != CARACTERE
                                     ||  yyvsp[0].tipoexpr != INTEIRO && yyvsp[0].tipoexpr != CARACTERE)
                                     Incompatibilidade ("Operando improprio para operador resto");
                                 yyval.tipoexpr = INTEIRO;
                                 break;
                         }
                     }
break;
case 144:
#line 393 ".\lab_4.y"
{
                        if  (yyvsp[0].simb != NULL)  {
                            yyvsp[0].simb->ref  =  VERDADE;
                            yyval.tipoexpr = yyvsp[0].simb->tvar;
                        }
                     }
break;
case 145:
#line 399 ".\lab_4.y"
{printf("%d",yyvsp[0].valint); yyval.tipoexpr = INTEIRO;}
break;
case 146:
#line 400 ".\lab_4.y"
{printf("%g",yyvsp[0].valreal); yyval.tipoexpr = REAL;}
break;
case 147:
#line 401 ".\lab_4.y"
{printf("%s",yyvsp[0].cadeia); yyval.tipoexpr = CARACTERE;}
break;
case 148:
#line 402 ".\lab_4.y"
{printf("true");  yyval.tipoexpr = LOGICO;}
break;
case 149:
#line 403 ".\lab_4.y"
{printf("false"); yyval.tipoexpr = LOGICO;}
break;
case 150:
#line 404 ".\lab_4.y"
{printf("~");}
break;
case 151:
#line 404 ".\lab_4.y"
{
                       if (yyvsp[0].tipoexpr != INTEIRO && yyvsp[0].tipoexpr != REAL && yyvsp[0].tipoexpr != CARACTERE)
                           Incompatibilidade  ("Operando improprio para menos unario");
                       if (yyvsp[0].tipoexpr == REAL) yyval.tipoexpr = REAL;
                       else yyval.tipoexpr = INTEIRO;
                     }
break;
case 152:
#line 410 ".\lab_4.y"
{printf("\(");}
break;
case 153:
#line 412 ".\lab_4.y"
{printf(") ");}
break;
case 154:
#line 413 ".\lab_4.y"
{yyval.tipoexpr = yyvsp[-2].tipoexpr;}
break;
case 156:
#line 418 ".\lab_4.y"
{
                       printf ("%s ", yyvsp[0].cadeia);
                       simb = ProcuraSimb (yyvsp[0].cadeia);
                       if (simb == NULL)   NaoDeclarado (yyvsp[0].cadeia);
                       else if (simb->tid != IDVAR) TipoInadequado (yyvsp[0].cadeia);
                       yyval.simb = simb;
                     }
break;
case 157:
#line 424 ".\lab_4.y"
{yyval.simb = yyvsp[-1].simb;}
break;
case 159:
#line 427 ".\lab_4.y"
{printf("\[");}
break;
case 160:
#line 428 ".\lab_4.y"
{printf("]");}
break;
case 162:
#line 431 ".\lab_4.y"
{printf(",");}
break;
#line 1367 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
