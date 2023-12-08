%{
#include <iostream>
#include <vector>
#include "IdList.h"
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);
class IdList ids;
class StructList user_structs;

%}
%union {
     char* string;
}
%token  BGIN END ASSIGN NR STRUCT
%token<string> ID TYPE CONST
%start progr
%%
progr: user_types declarations block {printf("The programme is correct!\n");}
     ;
     

user_types: user_type
            | user_types user_type
            ;

user_type: STRUCT ID '{' list_param_struct '}' ';'  // add to the list of user types
            {   if(!user_structs.existsStruct($2)) {
                    user_structs.addStruct($2, $4);
                }

                     
            }
            ;

declarations :  decl ';'          
	      |  declarations decl ';'   
	      ;

decl       :  TYPE ID { if(!ids.existsVar($2)) {
                          ids.addVar($1,$2);
                     }
                    }
            | TYPE ID '(' list_param ')'  
            | TYPE ID '(' ')' 
            | TYPE ID '[' NR ']'
            | TYPE ID '[' NR ']' '[' NR ']'
            | CONST TYPE ID 
            | CONST TYPE ID '[' NR ']'
            | CONST TYPE ID '[' NR ']' '[' NR ']'
            | STRUCT ID ID ';' {}
     
           ;

list_param : param
            | list_param ','  param 
            ;


            
param : TYPE ID 
      ; 
      

block : BGIN list END  
     ;
     

list :  statement ';' 
     | list statement ';'
     ;

statement: ID ASSIGN ID
         | ID ASSIGN NR  		 
         | ID '(' call_list ')'
         ;
        
call_list : NR
           | call_list ',' NR
           ;
%%
void yyerror(const char * s){
    printf("error: %s at line:%d\n",s,yylineno);
}
int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse();
     cout << "Variables:" <<endl;
     ids.printVars();
    
}