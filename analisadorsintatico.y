%{
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

%}

%union {
	char cadeia[50];
	int atr, valint;
	float valreal;
	char carac;
	simbolo simb;
	int tipoexpr;
}
%type	     <simb>	            Variable
%type 	   <tipoexpr> 	      Expression  AuxExpr1  AuxExpr2
                              AuxExpr3   AuxExpr4   Term   Factor
%token                        ELSE
%token                        IF
%token                        WHILE
%token     <cadeia>           ID
%token     <valint>           INTCT
%token     <atr>              RELOP
%token     <carac>            INVAL
%token     <valreal>          FLOATCT
%token     <cadeia>           CHARCT
%token     <cadeia>           STRING
%token                        CHAR
%token                        DO
%token                        FALSE
%token                        FLOAT
%token                        FOR
%token                        FUNCTIONS
%token                        GLOBAL
%token                        INT
%token                        LOCAL
%token                        LOGIC
%token                        MAIN
%token                        PROGRAM
%token                        READ
%token                        RETURN
%token                        STATEMENTS
%token                        TRUE
%token                        VOID
%token                        WRITE
%token                        OR
%token                        AND
%token                        NOT
%token                        NEG
%token     <atr>              ADOP
%token     <atr>              MULTOP
%token                        ASSIGN
%token                        OPPAR
%token                        CLPAR
%token                        OPBRAK
%token                        CLBRAK
%token                        OPBRACE
%token                        CLBRACE
%token                        SCOLON
%token                        COMMA
%token                        COLON
%token                        CALL


%%
Prog         :       {InicTabSimb ();}
                     PROGRAM {printf("program ");}
                     ID {printf("%s ",$4); InsereSimb ($4, IDPROG, NAOVAR);}
                     OPBRACE {printf("\{\n"); tab++;}
                     GlobDecls Functions
                     CLBRACE
                     {
                         tab--; tabular();
                         printf ("}\n");
                         VerificaInicRef ();
                         ImprimeTabSimb ();
                     }
             ;


GlobDecls    :
             |       GLOBAL { tab--; tabular(); tab++; printf("global ");} COLON {printf(":\n");} DeclList
             ;
DeclList     :       Declaration
             |       DeclList Declaration
             ;
Declaration  :       Type ElemList SCOLON {printf(";\n");}
             ;
Type         :       INT {tabular(); printf("int "); tipocorrente = INTEIRO;}
             |       FLOAT {tabular(); printf("float "); tipocorrente = REAL;}
             |       CHAR {tabular(); printf("char "); tipocorrente = CARACTERE;}
             |       LOGIC {tabular(); printf("logic "); tipocorrente = LOGICO;}
             |       VOID {tabular(); printf("void ");}
             ;
ElemList     :       Elem
             |       ElemList COMMA {printf(", ");} Elem
             ;
Elem         :       ID
                     {
                         printf("%s",$1);
                         if (ProcuraSimb ($1)  !=  NULL)
                             DeclaracaoRepetida ($1);
                         else
                             InsereSimb ($1,  IDVAR,  tipocorrente);
                     }
                     Dims
             ;
Dims         :
             |       OPBRAK
                     {printf("\[");}
                     DimList CLBRAK {printf("]");}
             ;
DimList      :       INTCT {printf("%d",$1);}
             |       DimList COMMA {printf(", ");} INTCT {printf("%d",$4);}
             ;
Functions    :       FUNCTIONS {tab--; tabular(); tab++; printf("functions");} COLON {printf(":\n");} FuncList
             ;
FuncList     :       Function
             |       FuncList Function
             ;
Function     :       Header OPBRACE {printf("\{\n"); tab++;}
                     LocDecls Stats CLBRACE {tab--; tabular(); printf("}\n");}
             ;
Header       :       MAIN {tabular(); printf("main ");}
             |       Type ID {printf("%s ",$2);} OPPAR {printf("\(");} Params CLPAR {printf(") ");}
             ;
Params       :
             |       ParamList
             ;
ParamList    :       Parameter
             |       ParamList COMMA {printf(", ");} Parameter
             ;
Parameter    :       Type ID {printf("%s ",$2);}
             ;
LocDecls     :
             |       LOCAL {tab--; tabular(); tab++; printf("local");} COLON {printf(":\n");} DeclList
             ;
Stats        :       STATEMENTS {tab--; tabular(); tab++; printf("statements");} COLON {printf(":\n");} StatList
             ;
StatList     :
             |       StatList Statement
             ;
Statement    :       CompStat
             |       IfStat
             |       WhileStat
             |       DoStat
             |       ForStat
             |       ReadStat
             |       WriteStat
             |       AssignStat
             |       CallStat
             |       ReturnStat
             |       SCOLON {printf(";\n"); allow_tab(); }
             ;
CompStat     :       OPBRACE
                     {tabular(); printf("\{\n"); tab++;}
                     StatList CLBRACE
                     {tab--; tabular(); printf("}\n");}
             ;
IfStat       :       IF {tabular(); printf("if");}
                     OPPAR {printf("\(");} Expression
                     CLPAR {printf(") "); no_tab();} Statement ElseStat
             ;
ElseStat     :
             |       ELSE {tabular(); printf("else "); no_tab();} Statement
             ;
WhileStat    :       WHILE {tabular(); printf("while");} OPPAR {printf("\(");} Expression
                     CLPAR {printf(") "); no_tab();} Statement
             ;
DoStat       :       DO {tabular(); printf("do "); no_tab();} Statement
                     WHILE {tabular(); printf("while");} OPPAR {printf("\(");} Expression
                     CLPAR {printf(")");}
                     SCOLON {printf(";\n");}
             ;
ForStat      :       FOR {tabular(); printf("for");}
                     OPPAR {printf("\(");} Variable
                     ASSIGN {printf(" <- ");} Expression
                     SCOLON {printf("; ");} Expression
                     SCOLON {printf("; ");} Variable
                     ASSIGN {printf(" <- ");}
                     Expression
                     CLPAR {printf(") ");no_tab();}
                     Statement
             ;
ReadStat     :       READ {tabular(); printf("read");} OPPAR {printf("\(");} ReadList CLPAR {printf(") ");} SCOLON {printf(";\n"); }
             ;
ReadList     :       Variable
             |       ReadList COMMA {printf(", ");} Variable
             ;
WriteStat    :       WRITE {tabular(); printf("write");} OPPAR {printf("\(");} WriteList CLPAR {printf(")");} SCOLON {printf(";\n"); }
             ;
WriteList    :       WriteElem
             |       WriteList COMMA {printf(", ");} WriteElem
             ;
WriteElem    :       STRING {printf("%s",$1);}
             |       Expression
             ;
CallStat     :       CALL {tabular(); printf("call ");} FuncCall SCOLON {printf(";\n");}
             ;
FuncCall     :       ID {printf("%s",$1);} OPPAR {printf("\(");} Arguments CLPAR {printf(") ");}
             ;
Arguments    :
             |       ExprList
             ;
ReturnStat   :       RETURN {tabular(); printf("return ");} SCOLON {printf(";\n");}
             |       RETURN {tabular(); printf("return ");} Expression SCOLON {printf(";\n");}
             ;
AssignStat   :       {tabular();}
                     Variable
                     {if  ($2 != NULL) $2->inic = $2->ref = VERDADE;}
                     ASSIGN {printf(" <- ");}
                     Expression SCOLON
                     {
                         printf (";\n");
                         if ($2 != NULL)
                             if ((($2->tvar == INTEIRO || $2->tvar == CARACTERE) &&
                                 ($6 == REAL || $6 == LOGICO)) ||
                                 ($2->tvar == REAL && $6 == LOGICO) ||
                                 ($2->tvar == LOGICO && $6 != LOGICO))
                                 Incompatibilidade ("Lado direito de comando de atribuicao improprio");
                     }
             ;
ExprList     :       Expression
             |       ExprList COMMA {printf(", ");} Expression
             ;
Expression   :       AuxExpr1
             |       Expression OR {printf(" || ");} AuxExpr1
                     {
                       if ($1 != LOGICO || $4 != LOGICO)
                          Incompatibilidade ("Operando improprio para operador or");
                       $$ = LOGICO;
                     }
             ;
AuxExpr1     :       AuxExpr2
             |       AuxExpr1 AND {printf(" && ");} AuxExpr2
                     {
                       if ($1 != LOGICO || $4 != LOGICO)
                           Incompatibilidade ("Operando improprio para operador and");
                       $$ = LOGICO;
                     }
             ;
AuxExpr2     :       AuxExpr3
             |       NOT {printf("!");} AuxExpr3
                     {
                       if ($3 != LOGICO)
                           Incompatibilidade ("Operando improprio para operador not");
                       $$ = LOGICO;
                     }
             ;
AuxExpr3     :       AuxExpr4
             |       AuxExpr4 RELOP
                     {
                       switch($2){
                         case LT: printf(" < "); break;
                         case LE: printf(" <= "); break;
                         case GT: printf(" > "); break;
                         case GE: printf(" >= "); break;
                         case EQ: printf(" = "); break;
                         case NE: printf(" != "); break;
                       }
                     } AuxExpr4
                     {
                         switch ($2) {
                             case LT: case LE: case GT: case GE:
                                 if ($1 != INTEIRO && $1 != REAL && $1 != CARACTERE || $4 != INTEIRO && $4 != REAL && $4 != CARACTERE)
                                     Incompatibilidade	("Operando improprio para operador relacional");
                                 break;
                             case EQ: case NE:
                                 if (($1 == LOGICO || $4 == LOGICO) && $1 != $4)
                                     Incompatibilidade ("Operando improprio para operador relacional");
                                 break;
                         }
                         $$ = LOGICO;
                     }
             ;
AuxExpr4     :       Term
             |       AuxExpr4 ADOP
                     {
                       if($2 == MAIS)
                         printf(" + ");
                       else
                         printf(" - ");
                     } Term {
                         if ($1 != INTEIRO && $1 != REAL && $1 != CARACTERE || $4 != INTEIRO && $4!=REAL && $4!=CARACTERE)
                             Incompatibilidade ("Operando improprio para operador aritmetico 1");
                         if ($1 == REAL || $4 == REAL) $$ = REAL;
                         else $$ = INTEIRO;
                     }
             ;
Term         :       Factor
             |       Term MULTOP
                     {
                       if($2 == VEZES)
                         printf(" * ");
                       else if($2 == DIV)
                         printf(" / ");
                       else
                         printf(" % ");
                     } Factor {
                         switch ($2) {
                             case VEZES: case DIV:
                                 if ($1 != INTEIRO && $1 != REAL && $1 != CARACTERE
                                     || $4 != INTEIRO && $4!=REAL && $4 != CARACTERE) {
                                     Incompatibilidade ("Operando improprio para operador aritmetico 2");
                                   }
                                 if ($1 == REAL || $4 == REAL) $$ = REAL;
                                 else $$ = INTEIRO;
                                 break;
                             case MOD:
                                 if ($1 != INTEIRO && $1 != CARACTERE
                                     ||  $4 != INTEIRO && $4 != CARACTERE)
                                     Incompatibilidade ("Operando improprio para operador resto");
                                 $$ = INTEIRO;
                                 break;
                         }
                     }
             ;
Factor       :       Variable {
                        if  ($1 != NULL)  {
                            $1->ref  =  VERDADE;
                            $$ = $1->tvar;
                        }
                     }
             |       INTCT   {printf("%d",$1); $$ = INTEIRO;}
             |       FLOATCT {printf("%g",$1); $$ = REAL;}
             |       CHARCT  {printf("%s",$1); $$ = CARACTERE;}
             |       TRUE    {printf("true");  $$ = LOGICO;}
             |       FALSE   {printf("false"); $$ = LOGICO;}
             |       NEG     {printf("~");} Factor {
                       if ($3 != INTEIRO && $3 != REAL && $3 != CARACTERE)
                           Incompatibilidade  ("Operando improprio para menos unario");
                       if ($3 == REAL) $$ = REAL;
                       else $$ = INTEIRO;
                     }
             |       OPPAR   {printf("\(");}
                     Expression
                     {printf(") ");}
                     CLPAR {$$ = $3;}
             |       FuncCall
             ;

Variable     :       ID
                     {
                       printf ("%s ", $1);
                       simb = ProcuraSimb ($1);
                       if (simb == NULL)   NaoDeclarado ($1);
                       else if (simb->tid != IDVAR) TipoInadequado ($1);
                       $<simb>$ = simb;
                     } Subscripts {$$ = $<simb>2;}
             ;
Subscripts   :
             |       OPBRAK {printf("\[");}
                     SubscrList CLBRAK {printf("]");}
             ;
SubscrList   :       AuxExpr4
             |       SubscrList COMMA {printf(",");} AuxExpr4
             ;
%%
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
