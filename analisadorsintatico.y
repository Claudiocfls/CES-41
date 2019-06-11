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

#define       IDPROG          1
#define       IDVAR         2
#define     IDFUNC      3
#define     IDBLOC      6
#define     IDGLOB      7


/*  Definicao dos tipos de variaveis   */

#define       NAOVAR          0
#define       INTEIRO         1
#define       LOGICO          2
#define       REAL          3
#define       CARACTERE   4

/*   Definicao de outras constantes   */

#define     NCLASSHASH  23
#define     VERDADE       1
#define     FALSO           0
#define     MAXDIMS     10

/*  Strings para nomes dos tipos de identificadores  */

char *nometipid[4] = {" ", "IDPROG", "IDVAR", "IDFUNC"};

/*  Strings para nomes dos tipos de variaveis  */

char *nometipvar[5] = {"NAOVAR","INTEIRO", "LOGICO", "REAL", "CARACTERE"};

/*    Declaracoes para a tabela de simbolos     */

typedef struct cellist cellist;
typedef struct cellist* list;
typedef struct celsimb celsimb;
typedef celsimb *simbolo;

struct cellist {
    simbolo var;
    int var_aux;
    list prox;
};
struct celsimb {
    char *cadeia;
    int tid, tvar, ndims, dims[MAXDIMS+1];
    char inic, array, ref, param;
    simbolo prox, escopo;
    list listarg;
    int narg;
};



/*  Variaveis globais para a tabela de simbolos e analise semantica */

simbolo tabsimb[NCLASSHASH];
simbolo simb, tempsimb;
simbolo escopo;
int tipocorrente;
int chamadafuncao;
list argaux;
int argn;
simbolo argsimb;
int lendoarg;
/*
    Prototipos das funcoes para a tabela de simbolos e analise semantica
*/

void InicTabSimb (void);
void ImprimeTabSimb (void);
simbolo InsereSimb (char *, int, int,simbolo);
int hash (char *);
simbolo ProcuraSimb (char *,simbolo);
void DeclaracaoRepetida (char *);
void TipoInadequado (char *);
void NaoDeclarado (char *);
void VerificaInicRef (void);
void Incompatibilidade (char *);
void Esperado (char *);
void NaoEsperado (char *);



%}

%union {
    char cadeia[50];
    int atr, valint;
    float valreal;
    char carac;
    simbolo simb;
    int tipoexpr;
  int nsubscr;
}
%type        <simb>             Variable
%type      <tipoexpr>         Expression  AuxExpr1  AuxExpr2
                              AuxExpr3   AuxExpr4   Term   Factor FuncCall
%type      <nsubscr>          Subscripts  SubscrList
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
                     {escopo =  InsereSimb ("##global", IDGLOB, NAOVAR, NULL);lendoarg=FALSO;}
                     PROGRAM {printf("program ");}
                     ID {printf("%s ",$5); InsereSimb ($5, IDPROG, NAOVAR, escopo);}
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
Declaration  :       Type ElemList SCOLON
                     {
                                             if(tipocorrente == VOID)
                                               printf ("\n\n***** Variavel declarada com tipo void *****\n\n");
                                             printf(";\n");
                                         }
             ;
Type         :       INT {tabular(); printf("int ");     tipocorrente = INTEIRO;}
             |       FLOAT {tabular(); printf("float "); tipocorrente = REAL;}
             |       CHAR {tabular(); printf("char ");   tipocorrente = CARACTERE;}
             |       LOGIC {tabular(); printf("logic "); tipocorrente = LOGICO;}
             |       VOID {tabular(); printf("void ");   tipocorrente = VOID;}
             ;
ElemList     :       Elem
             |       ElemList COMMA {printf(", ");} Elem
             ;
Elem         :       ID
                     {
                         printf("%s ",$1);
                         if (ProcuraSimb ($1,escopo)  !=  NULL){
                             DeclaracaoRepetida ($1);}
                         else{
                            simb = InsereSimb ($1, IDVAR, tipocorrente,escopo);
                            simb->array = FALSO; simb->ndims = 0;
                         }
                     }
                     Dims
             ;
Dims         :
             |       OPBRAK
                     {printf("\[");}
                     DimList CLBRAK {printf("]");simb->array = VERDADE;}
             ;
DimList      :       INTCT
                     {
                                             printf("%d",$1);
                                             if ($1 <= 0)
                                                Esperado ("Valor inteiro positivo");
                       simb->ndims++;
                                             simb->dims[simb->ndims] = $1;
                                         }
             |       DimList COMMA {printf(", ");} INTCT
                                 {
                                             printf("%d",$4);
                                             if ($4 <= 0)
                          Esperado ("Valor inteiro positivo");
                       simb->ndims++; simb->dims[simb->ndims] = $4;
                     }
             ;
Functions    :       FUNCTIONS {tab--; tabular(); tab++; printf("functions");} COLON {printf(":\n");} FuncList
             ;
FuncList     :       Function
             |       FuncList Function
             ;
Function     :       Header  OPBRACE {printf("\{\n"); tab++;}
                     LocDecls Stats CLBRACE {escopo = escopo->escopo;} {tab--; tabular(); printf("}\n");}
             ;
Header       :       MAIN
                     {
                                             if (ProcuraSimb ("##main",escopo)  !=  NULL){
                                                     DeclaracaoRepetida ("##main");
                                             } else {
                                                 escopo = InsereSimb ("##main", IDFUNC, tipocorrente, escopo);
                                             }
                                         }
                                         {tabular(); printf("main ");}
             |       Type ID
                                 {
                                             if (ProcuraSimb ($2,escopo)  !=  NULL){
                                                     DeclaracaoRepetida ($2);
                                             } else {
                                                   if (strcmp(escopo->cadeia,$2) == 0){
                                                         printf("\n\n***** possivel recursao detectada: recursoes nao sao permitidas  *****\n\n");}
                                                     else{
                                                        escopo = InsereSimb ($2, IDFUNC, tipocorrente, escopo);}
                                                    escopo -> narg = 0;

                                             }
                                             printf("%s ",$2);
                                         }
                                         OPPAR {printf("\(");} Params CLPAR {printf(") ");}
             ;
Params       :
             |       ParamList
             ;
ParamList    :       Parameter
             |       ParamList COMMA {printf(", ");} Parameter
             ;
Parameter    :       Type ID {
                         printf("%s ",$2);
                         if (ProcuraSimb ($2,escopo)  !=  NULL){
                             DeclaracaoRepetida ($2);}
                         else{
                            simb = InsereSimb ($2, IDVAR, tipocorrente,escopo);
                                                        simb->inic = VERDADE;
                            simb->array = FALSO; simb->ndims = 0;
                            list listaux;

                            listaux = escopo->listarg;
                            while(listaux->prox != NULL)
                                listaux = listaux->prox;
                            listaux ->prox = (list) malloc (sizeof (cellist));
                            listaux -> prox -> prox = NULL;
                            listaux -> prox -> var = simb;
                            escopo->narg = escopo->narg + 1;
                         }
                     }
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
                     CLPAR
                                         {
                                             printf(") ");
                                           if($5 != LOGICO)
                                             printf("\n\n**** expressao nao eh do tipo logico ****\n\n");
                                           no_tab();
                                       } Statement ElseStat
             ;
ElseStat     :
             |       ELSE {tabular(); printf("else "); no_tab();} Statement
             ;
WhileStat    :       WHILE {tabular(); printf("while");} OPPAR {printf("\(");} Expression
                     CLPAR
                                         {
                                             printf(") ");
                                             if($5 != LOGICO)
                                             printf("\n\n**** expressao nao eh do tipo logico ****\n\n");
                                             no_tab();
                                         } Statement
             ;
DoStat       :       DO {tabular(); printf("do "); no_tab();} Statement
                     WHILE {tabular(); printf("while");} OPPAR {printf("\(");} Expression
                     CLPAR
                                         {
                                             printf(")");
                                             if($8 != LOGICO)
                                             printf("\n\n**** expressao nao eh do tipo logico ****\n\n");
                                         }
                     SCOLON {printf(";\n");}
             ;
ForStat      :       FOR {tabular(); printf("for");}
                     OPPAR {printf("\(");} Variable
                                         {
                                             {if  ($5 != NULL) $5->inic = $5->ref = VERDADE;}
                                             if($5 != NULL && $5->array) {
                                                 printf("\n\n**** variavel de inicializacao nao pode ser variavel indexada ****\n\n");
                                             }
                                             else if($5 != NULL &&  $5->tvar != INTEIRO && $5->tvar != CARACTERE) {
                                                 printf("\n\n**** variavel de inicializacao deve ser do tipo INTEIRO ou CARACTERE ****\n\n");
                                             }
                                         }
                     ASSIGN {printf(" <- ");} Expression {if($9 != INTEIRO && $9 != CARACTERE) printf("\n\n**** expressao deve ser do tipo INTEIRO ou CARACTERE ****\n\n");}
                     SCOLON {printf("; ");} Expression {if($13 != LOGICO) printf("\n\n**** expressao deve ser do tipo LOGICO ****\n\n");}
                     SCOLON {printf("; ");} Variable
                     ASSIGN {printf(" <- ");}
                     Expression {if($20 != INTEIRO && $20 != CARACTERE) printf("\n\n**** expressao deve ser do tipo INTEIRO ou CARACTERE ****\n\n");}
                     CLPAR {printf(") ");no_tab();}
                     Statement
             ;
ReadStat     :       READ {tabular(); printf("read");} OPPAR {printf("\(");} ReadList CLPAR {printf(") ");} SCOLON {printf(";\n"); }
             ;
ReadList     :       Variable
                     {if  ($1 != NULL) $1->inic = $1->ref = VERDADE;}
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
CallStat     :       CALL {tabular(); printf("call ");} FuncCall
                     {
                       if($3 != VOID) {
                           printf("\n\n**** funcoes chamadas por CALL devem ser do tipo void %d****\n\n",$3 );
                       }

                                         }
                     SCOLON {printf(";\n");}
             ;
FuncCall     :       ID
                     {
											 if (lendoarg == VERDADE)
											 		printf("\n\n*****Nao usar funcao como argumento*****\n\n" );
											 lendoarg = VERDADE;
                       simbolo escaux;
                       escaux = escopo;
                       simb = ProcuraSimb ($1, escaux);
                       while (escaux && !simb) {
                            escaux = escaux->escopo;
                            if (escaux)
                                simb = ProcuraSimb ($1, escaux);
                       }
                         if(!simb) printf("\n\n**** funcao nao declarada %d %s****\n\n",simb,$1);
												 else if(strcmp(simb->cadeia, escopo->cadeia) == 0) printf("\n\n **** recursoes nao sao permitidas ****\n\n");
                                             if(simb && simb->tid != IDFUNC) printf("\n\n**** variavel %s nao eh uma funcao ****\n\n",$1);
                                             tempsimb = simb;
                        argsimb = simb;

                     }
                                         {printf("%s",$1);} OPPAR {printf("\(");chamadafuncao = VERDADE;argaux = (list) malloc (sizeof (cellist));argn=0;} Arguments CLPAR {printf(") ");lendoarg=FALSO;}
                                         {
                                             if (tempsimb) $$ = tempsimb->tvar;
                                             chamadafuncao = FALSO;
                                             //VERIFICANDO argumentos

                                             if(argn!=argsimb->narg){

                                                printf("\n\n *** numero de argumentos incompativeis %d != %d*** \n\n",argn,argsimb->narg);
                                             }else{
                                                int p =0;
                                                list aux1,aux2;
                                                aux1 = argaux->prox;
                                                aux2 = argsimb->listarg->prox;
                                                while(p < argn){

                                                    if(aux1->var_aux != aux2->var->tvar)
                                                        printf("\n\n *** argumento com tipos incompativeis *** \n\n");
                                                    aux1=aux1->prox;
                                                    aux2=aux2->prox;
                                                    p = p+1;
                                                }
                                             }



                                         }
             ;
Arguments    :
             |       ExprList
             ;
ReturnStat   :       RETURN {tabular(); printf("return ");}
                     {
                                             if(escopo->tvar != VOID) {
                                                 printf("\n\n *** a funcao deve retornar uma expressao *** \n\n");
                                             }
                                         }
                                         SCOLON {printf(";\n");}
             |       RETURN {tabular(); printf("return ");} Expression
                                         {
                                             if(escopo->tvar == VOID) {
                                                 printf("\n\n *** a funcao nao deve retornar nenhuma expressao *** \n\n");
                                             }
																						 if(escopo->tvar != $3) {
																							 printf("\n\n**** retorno de funcao de tipo diferente do declarado *** \n\n");
																						 }
                                         }
                                         SCOLON {printf(";\n");}
             ;
AssignStat   :       {tabular();}
                     Variable
                     {if  ($2 != NULL) $2->inic = $2->ref = VERDADE;}
                     ASSIGN {printf(" <- ");}
                     Expression SCOLON
                     {
                         printf (";\n");
                         if ($2 != NULL){
                                                         int err = 0;
                                                         switch ($2->tvar) {
                                                             case INTEIRO: if($6 != INTEIRO && $6 != CARACTERE) err = 1; break;
                                                             case REAL: if($6 != INTEIRO && $6 != CARACTERE && $6 != REAL) err = 1; break;
                                                             case CARACTERE: if($6 != INTEIRO && $6 != CARACTERE) err = 1; break;
                                                             case LOGICO: if($6 != LOGICO) err = 1; break;
                                                         }
                                                         if(err)
                                                           Incompatibilidade ("Lado direito de comando de atribuicao improprio");
                                                 }
                     }
             ;
ExprList     :       Expression {

                        argn = argn + 1;
                        list add = argaux;
                        while (add->prox != NULL){
                            add = add->prox;
                        }
                        add->prox = (list) malloc (sizeof (cellist));
                        add->prox->prox = NULL;
                        add->prox->var_aux = $1;
                     }
             |       ExprList COMMA {printf(", ");} Expression{
                        argn = argn + 1;
                        list add = argaux;
                        while (add->prox != NULL){
                            add = add->prox;
                        }
                        add->prox = (list) malloc (sizeof (cellist));
                        add->prox->prox = NULL;
                        add->prox->var_aux = $4;
                     }
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
                                     Incompatibilidade  ("Operando improprio para operador relacional");
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
                     {
                          if($1 != INTEIRO && $1 != CARACTERE && $1 != REAL && $1 != LOGICO)
                                       printf("\n\n **** a funcao deve retornar algum valor **** \n\n");
                     }
             ;

Variable     :       ID
                     {
                       printf ("%s ", $1);
                       simbolo escaux;
                       escaux = escopo;
                       simb = ProcuraSimb ($1, escaux);
                       while (escaux && !simb) {
                            escaux = escaux->escopo;
                            if (escaux)
                                simb = ProcuraSimb ($1, escaux);
                        }
                       if (simb == NULL)   NaoDeclarado ($1);
                       else if (simb->tid != IDVAR) TipoInadequado ($1);
                       $<simb>$ = simb;
                     } Subscripts {
                        $$ = $<simb>2;
                        if ($$ != NULL) {
                            if ($$->array == FALSO && $3 > 0)
                                    NaoEsperado ("Subscrito\(s)");
                            else if ($$->array == VERDADE && $3 == 0)
                                Esperado ("Subscrito\(s)");
                            else if ($$->ndims != $3)
                                Incompatibilidade ("Numero de subscritos incompativel com declaracao");
                        }
                    }
             ;
Subscripts   :      {$$ = 0;}
             |       OPBRAK {printf("\[");}
                     SubscrList CLBRAK {printf("]");$$ = $3;}

             ;
SubscrList   :       AuxExpr4
                     {
                        if ($1 != INTEIRO && $1 != CARACTERE)
                            Incompatibilidade ("Tipo inadequado para subscrito");
                        $$ = 1;
                     }
             |       SubscrList COMMA {printf(",");} AuxExpr4
                     {
                        if ($4 != INTEIRO && $4 != CARACTERE)
                            Incompatibilidade ("Tipo inadequado para subscrito");
                        $$ = $1 + 1;
                     }
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

simbolo ProcuraSimb (char *cadeia, simbolo esc) {
    simbolo s; int i;
    i = hash (cadeia);
    for (s = tabsimb[i]; (s!=NULL) && (strcmp(cadeia, s->cadeia) || esc != s->escopo); s = s->prox);
    return s;
}

/*
    InsereSimb (cadeia, tid, tvar): Insere cadeia na tabela de
    simbolos, com tid como tipo de identificador e com tvar como
    tipo de variavel; Retorna um ponteiro para a celula inserida
 */

simbolo InsereSimb (char *cadeia, int tid, int tvar, simbolo esc) {
    int i; simbolo aux, s;
    i = hash (cadeia); aux = tabsimb[i];
    s = tabsimb[i] = (simbolo) malloc (sizeof (celsimb));
    s->cadeia = (char*) malloc ((strlen(cadeia)+1) * sizeof(char));
    strcpy (s->cadeia, cadeia);
    s->tid = tid;       s->tvar = tvar;
    s->inic = FALSO;    s->ref = FALSO;
    s->prox = aux;      s->escopo = esc;
    s->listarg = (list) malloc (sizeof (cellist));
    s->listarg->var = NULL;
    s->listarg->prox = NULL;
    return s;
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
                if (s->tid == IDVAR){
                    printf (", %s, %d, %d", nometipvar[s->tvar], s->inic, s->ref);
          if (s->array == VERDADE) {
            int j;
            printf (", EH ARRAY\n\tndims = %d, dimensoes:", s->ndims);
            for (j = 1; j <= s->ndims; j++)
              printf ("  %d", s->dims[j]);
          }
        } else if(s->tid == IDFUNC) {
                    if(s->tvar < 0 || s->tvar > 4){
                            printf (", VOID");
                    } else
                        printf (", %s", nometipvar[s->tvar]);
                }

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
                        printf ("%s (%s): Nao Inicializada\n", s->cadeia, s->escopo->cadeia);
                    if (s->ref == FALSO)
                        printf ("%s (%s): Nao Referenciada\n", s->cadeia, s->escopo->cadeia);
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
void Esperado (char *s) {
    printf ("\n\n***** Esperado: %s *****\n\n", s);
}

void NaoEsperado (char *s) {
    printf ("\n\n***** Nao Esperado: %s *****\n\n", s);
}

