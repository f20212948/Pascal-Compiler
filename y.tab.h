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
    PROG_ID = 258,                 /* PROG_ID  */
    INT = 259,                     /* INT  */
    REAL = 260,                    /* REAL  */
    BOOL = 261,                    /* BOOL  */
    VAR = 262,                     /* VAR  */
    CHAR = 263,                    /* CHAR  */
    TO = 264,                      /* TO  */
    DOWNTO = 265,                  /* DOWNTO  */
    IF = 266,                      /* IF  */
    ELSE = 267,                    /* ELSE  */
    WHILE = 268,                   /* WHILE  */
    FOR = 269,                     /* FOR  */
    THEN = 270,                    /* THEN  */
    DO = 271,                      /* DO  */
    ARRAY = 272,                   /* ARRAY  */
    OF = 273,                      /* OF  */
    AND = 274,                     /* AND  */
    OR = 275,                      /* OR  */
    NOT = 276,                     /* NOT  */
    BEG = 277,                     /* BEG  */
    END = 278,                     /* END  */
    READ = 279,                    /* READ  */
    WRITE = 280,                   /* WRITE  */
    PLUS = 281,                    /* PLUS  */
    MINUS = 282,                   /* MINUS  */
    MULTIPLY = 283,                /* MULTIPLY  */
    DIVIDE = 284,                  /* DIVIDE  */
    MOD = 285,                     /* MOD  */
    EQUAL = 286,                   /* EQUAL  */
    ASSIGN = 287,                  /* ASSIGN  */
    LT = 288,                      /* LT  */
    GT = 289,                      /* GT  */
    LTE = 290,                     /* LTE  */
    GTE = 291,                     /* GTE  */
    NE = 292,                      /* NE  */
    SEMICOLON = 293,               /* SEMICOLON  */
    COLON = 294,                   /* COLON  */
    COMMA = 295,                   /* COMMA  */
    DOT = 296,                     /* DOT  */
    LP = 297,                      /* LP  */
    RP = 298,                      /* RP  */
    LB = 299,                      /* LB  */
    RB = 300,                      /* RB  */
    NUM = 301,                     /* NUM  */
    STRING = 302,                  /* STRING  */
    ID = 303,                      /* ID  */
    RANGE = 304,                   /* RANGE  */
    REALNUM = 305                  /* REALNUM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define PROG_ID 258
#define INT 259
#define REAL 260
#define BOOL 261
#define VAR 262
#define CHAR 263
#define TO 264
#define DOWNTO 265
#define IF 266
#define ELSE 267
#define WHILE 268
#define FOR 269
#define THEN 270
#define DO 271
#define ARRAY 272
#define OF 273
#define AND 274
#define OR 275
#define NOT 276
#define BEG 277
#define END 278
#define READ 279
#define WRITE 280
#define PLUS 281
#define MINUS 282
#define MULTIPLY 283
#define DIVIDE 284
#define MOD 285
#define EQUAL 286
#define ASSIGN 287
#define LT 288
#define GT 289
#define LTE 290
#define GTE 291
#define NE 292
#define SEMICOLON 293
#define COLON 294
#define COMMA 295
#define DOT 296
#define LP 297
#define RP 298
#define LB 299
#define RB 300
#define NUM 301
#define STRING 302
#define ID 303
#define RANGE 304
#define REALNUM 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 186 "5.y"

        int ival;
        double rval;
        char* sval;
        struct symbol* sym;
        struct quadruple* quad;

#line 175 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
