%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantic.h"

/* Function declarations */
int yylex();
void yyerror(const char* s);
extern int yylineno;

/* Root of the AST */
ASTNode* ast_root = NULL;
%}

/* Define the types for semantic values */
%union {
    char* str;
    int num;
    ASTNode* node;
}

/* Define tokens */
%token ASSESSMENT SECTION MC_QUESTION TF_QUESTION OPTION ANSWER FEEDBACK IF_SCORE
%token ABOVE BELOW CORRECT INCORRECT TRUE_VAL FALSE_VAL
%token <str> STRING
%token <num> NUMBER

/* Define types for non-terminals */
%type <node> assessment sections section questions question 
%type <node> mc_question tf_question options option answer feedback
%type <node> if_score conditional_sections

%%

program:
    assessment { ast_root = $1; }
    ;

assessment:
    ASSESSMENT STRING '{' sections '}' {
        $$ = create_node(NODE_ASSESSMENT, $2);
        add_child($$, $4);
    }
    ;

sections:
    sections section {
        $$ = $1;
        add_child($$, $2);
    }
    | sections if_score {
        $$ = $1;
        add_child($$, $2);
    }
    | section {
        $$ = create_node(NODE_SECTIONS, "sections");
        add_child($$, $1);
    }
    | if_score {
        $$ = create_node(NODE_SECTIONS, "sections");
        add_child($$, $1);
    }
    ;

section:
    SECTION STRING '{' questions '}' {
        $$ = create_node(NODE_SECTION, $2);
        add_child($$, $4);
    }
    ;

questions:
    questions question {
        $$ = $1;
        add_child($$, $2);
    }
    | question {
        $$ = create_node(NODE_QUESTIONS, "questions");
        add_child($$, $1);
    }
    ;

question:
    mc_question { $$ = $1; }
    | tf_question { $$ = $1; }
    ;

mc_question:
    MC_QUESTION STRING '{' options feedback '}' {
        $$ = create_node(NODE_MC_QUESTION, $2);
        add_child($$, $4);
        add_child($$, $5);
    }
    | MC_QUESTION STRING '{' options '}' {
        $$ = create_node(NODE_MC_QUESTION, $2);
        add_child($$, $4);
    }
    ;

options:
    options option {
        $$ = $1;
        add_child($$, $2);
    }
    | option {
        $$ = create_node(NODE_MC_QUESTION, "options");
        add_child($$, $1);
    }
    ;

option:
    OPTION STRING CORRECT {
        $$ = create_node(NODE_OPTION, $2);
        $$->correct = 1;
    }
    | OPTION STRING INCORRECT {
        $$ = create_node(NODE_OPTION, $2);
        $$->correct = 0;
    }
    ;

tf_question:
    TF_QUESTION STRING '{' answer feedback '}' {
        $$ = create_node(NODE_TF_QUESTION, $2);
        add_child($$, $4);
        add_child($$, $5);
    }
    | TF_QUESTION STRING '{' answer '}' {
        $$ = create_node(NODE_TF_QUESTION, $2);
        add_child($$, $4);
    }
    ;

answer:
    ANSWER TRUE_VAL {
        $$ = create_node(NODE_ANSWER, "TRUE");
        $$->answer = 1;
    }
    | ANSWER FALSE_VAL {
        $$ = create_node(NODE_ANSWER, "FALSE");
        $$->answer = 0;
    }
    ;

feedback:
    FEEDBACK STRING {
        $$ = create_node(NODE_FEEDBACK, $2);
    }
    ;

if_score:
    IF_SCORE ABOVE NUMBER '{' conditional_sections '}' {
        $$ = create_node(NODE_IF_SCORE, "if_score_above");
        $$->score_condition = 1;
        $$->score_value = $3;
        add_child($$, $5);
    }
    | IF_SCORE BELOW NUMBER '{' conditional_sections '}' {
        $$ = create_node(NODE_IF_SCORE, "if_score_below");
        $$->score_condition = 0;
        $$->score_value = $3;
        add_child($$, $5);
    }
    ;

conditional_sections:
    conditional_sections section {
        $$ = $1;
        add_child($$, $2);
    }
    | section {
        $$ = create_node(NODE_IF_SCORE, "conditional_sections");
        add_child($$, $1);
    }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, s);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s input_file\n", argv[0]);
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Cannot open file %s\n", argv[1]);
        return 1;
    }
    
    /* Set flex to read from file */
    extern FILE* yyin;
    yyin = file;
    
    /* Parse */
    int parse_result = yyparse();
    
    if (parse_result == 0 && ast_root != NULL) {
        printf("Parsing successful! Printing AST:\n");
        print_ast(ast_root, 0);
        
        /* Perform semantic analysis */
        printf("\nPerforming semantic analysis...\n");
        int semantic_result = validate_semantics(ast_root);
        
        if (semantic_result) {
            printf("Semantic analysis passed! The assessment is valid.\n");
            
            /* Here you would perform code generation */
            printf("Code generation would be performed here.\n");
        } else {
            printf("Semantic analysis failed! Please fix the errors.\n");
        }
        
        /* Free memory */
        free_node(ast_root);
    } else {
        printf("Parsing failed.\n");
    }
    
    fclose(file);
    return (parse_result == 0) ? 0 : 1;
}