/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ASSESSMENT = 258,              /* ASSESSMENT  */
    SECTION = 259,                 /* SECTION  */
    MC_QUESTION = 260,             /* MC_QUESTION  */
    TF_QUESTION = 261,             /* TF_QUESTION  */
    OPTION = 262,                  /* OPTION  */
    ANSWER = 263,                  /* ANSWER  */
    FEEDBACK = 264,                /* FEEDBACK  */
    IF_SCORE = 265,                /* IF_SCORE  */
    ABOVE = 266,                   /* ABOVE  */
    BELOW = 267,                   /* BELOW  */
    CORRECT = 268,                 /* CORRECT  */
    INCORRECT = 269,               /* INCORRECT  */
    TRUE_VAL = 270,                /* TRUE_VAL  */
    FALSE_VAL = 271,               /* FALSE_VAL  */
    STRING = 272,                  /* STRING  */
    NUMBER = 273                   /* NUMBER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ASSESSMENT 258
#define SECTION 259
#define MC_QUESTION 260
#define TF_QUESTION 261
#define OPTION 262
#define ANSWER 263
#define FEEDBACK 264
#define IF_SCORE 265
#define ABOVE 266
#define BELOW 267
#define CORRECT 268
#define INCORRECT 269
#define TRUE_VAL 270
#define FALSE_VAL 271
#define STRING 272
#define NUMBER 273

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "assessment.y"

    char* str;
    int num;
    ASTNode* node;

#line 109 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
