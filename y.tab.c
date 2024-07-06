/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "5.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
     
    #define MAX_SYMBOLS 1000
     
    int yylex();
    int yyerror(const char *msg);
    extern FILE *yyin;
     
    typedef struct symbol {
    char name[100];
    char type[100];
    int assigned;
    int isArray;
    struct symbol* next;
	} symbol;
     
    symbol symtab[MAX_SYMBOLS];
    int symtab_len = 0;
    char* current_type = "";
    int flag=1;
    int is_array = 0; 
    symbol* lookup(char* name) {
        for(int i = 0; i < symtab_len; i++) {
            if(strcmp(symtab[i].name, name) == 0) {
                return &symtab[i];
            }
        }
        return NULL;
    }


    typedef struct quadruple {
        char op[100];
        char arg1[100];
        char arg2[100];
        char result[100];
    } quadruple;
         
    quadruple quad[1000];
    int quad_len = 0;
    int temp_var_counter = 0;
        
    


    

symbol* insert(char* name) {
    symbol* s = lookup(name);
    if(s != NULL) {
        printf("Error: Duplicate declaration of variable %s\n", name);
        flag=0;
        //exit(1);
    } else {
        s = malloc(sizeof(symbol));
        strcpy(s->name, name);
        s->assigned = 0;
        symtab[symtab_len] = *s;
        symtab_len++;
        return &symtab[symtab_len-1];
    }
}

void emit(char* op, char* arg1, char* arg2, char* result) {
        strcpy(quad[quad_len].op, op);
        strcpy(quad[quad_len].arg1, arg1);
        strcpy(quad[quad_len].arg2, arg2);
        strcpy(quad[quad_len].result, result);
        quad_len++;
    }


char* create_temp_var() {
        char* temp_var = malloc(20);
        sprintf(temp_var, "t%d", temp_var_counter++);
        //insert(temp_var);
        return temp_var;
    }
int temp_label_counter = 1;
char* create_temp_label() {
        char* temp_label = malloc(50);
        sprintf(temp_label, "IFLabel:%d", temp_label_counter++);
        return temp_label;
    }

char* currLabel(){
    char* temp_label = malloc(50);
    sprintf(temp_label, "IFLabel:%d", temp_label_counter-1);
    return temp_label;
}

int wtemp_label_counter = 1;
char* wcreate_temp_label() {
        char* temp_label = malloc(50);
        sprintf(temp_label, "Whilelabel:%d", wtemp_label_counter++);
        return temp_label;
    }

char* wcurrLabel(){
    char* temp_label = malloc(50);
    sprintf(temp_label, "WhileLabel:%d", wtemp_label_counter-1);
    return temp_label;
}


int fortemp_label_counter = 1;
char* forcreate_temp_label() {
        char* temp_label = malloc(50);
        sprintf(temp_label, "Forlabel:%d", fortemp_label_counter++);
        return temp_label;
    }

char* forcurrLabel(){
    char* temp_label = malloc(50);
    sprintf(temp_label, "ForLabel:%d", fortemp_label_counter-1);
    return temp_label;
}


void assign_type(symbol* list, char* type) {
    symbol* s = list;
    while(s != NULL) {
        strcpy(s->type, type);
        //symtab_len++;
        s = s->next;
    }
}
void setArray(symbol* s, int isArr){
    symbol* sym = s;
        sym->isArray = isArr;
        sym->assigned = 1;
}

     
    void assign(char* name) {
        symbol* s = lookup(name);
        if(s == NULL) {
            printf("Error: Undeclared variable %s\n", name);
            flag=0;
            //exit(1);
        } else {
            s->assigned = 1;
        }
    }
     
    void check_expr_type(symbol* s1, symbol* s2) {
    if(s1 != NULL && s2 != NULL) {
        if(s1->name[0]=='t' || s2->name[0]=='t')
            return;
       // printf("TYPE: %s %s\n", s1->type, s2->type);
        if(strcmp(s1->type, s2->type) != 0) {
            printf("Error: Type mismatch in arithmetic operation between %s and %s\n", s1->name, s2->name);
            flag=0;
            //exit(1);
        }
    } 
}
typedef struct assign_stmt {
    symbol* var;
    symbol* expr;
} assign_stmt; 
void check_assign_type(assign_stmt* stmt) {
    if(stmt->var != NULL && stmt->expr != NULL) {
        //printf("TYPE: %s %s\n", stmt->var->type, stmt->expr->type);
        check_expr_type(stmt->var, stmt->expr);
    }
}

void check_assigned(char* name) {
        symbol* s = lookup(name);
        if(s != NULL && s->assigned == 0) {
            printf("Error: Variable %s used before assignment\n", name);
            flag=0;
            //exit(1);
        }
        else if(s == NULL){
            printf("Error: Undeclared variable %s\n", name);
            flag=0;
        }
    }
    

#line 257 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 418 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROG_ID = 3,                    /* PROG_ID  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_REAL = 5,                       /* REAL  */
  YYSYMBOL_BOOL = 6,                       /* BOOL  */
  YYSYMBOL_VAR = 7,                        /* VAR  */
  YYSYMBOL_CHAR = 8,                       /* CHAR  */
  YYSYMBOL_TO = 9,                         /* TO  */
  YYSYMBOL_DOWNTO = 10,                    /* DOWNTO  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_FOR = 14,                       /* FOR  */
  YYSYMBOL_THEN = 15,                      /* THEN  */
  YYSYMBOL_DO = 16,                        /* DO  */
  YYSYMBOL_ARRAY = 17,                     /* ARRAY  */
  YYSYMBOL_OF = 18,                        /* OF  */
  YYSYMBOL_AND = 19,                       /* AND  */
  YYSYMBOL_OR = 20,                        /* OR  */
  YYSYMBOL_NOT = 21,                       /* NOT  */
  YYSYMBOL_BEG = 22,                       /* BEG  */
  YYSYMBOL_END = 23,                       /* END  */
  YYSYMBOL_READ = 24,                      /* READ  */
  YYSYMBOL_WRITE = 25,                     /* WRITE  */
  YYSYMBOL_PLUS = 26,                      /* PLUS  */
  YYSYMBOL_MINUS = 27,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 28,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 29,                    /* DIVIDE  */
  YYSYMBOL_MOD = 30,                       /* MOD  */
  YYSYMBOL_EQUAL = 31,                     /* EQUAL  */
  YYSYMBOL_ASSIGN = 32,                    /* ASSIGN  */
  YYSYMBOL_LT = 33,                        /* LT  */
  YYSYMBOL_GT = 34,                        /* GT  */
  YYSYMBOL_LTE = 35,                       /* LTE  */
  YYSYMBOL_GTE = 36,                       /* GTE  */
  YYSYMBOL_NE = 37,                        /* NE  */
  YYSYMBOL_SEMICOLON = 38,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 39,                     /* COLON  */
  YYSYMBOL_COMMA = 40,                     /* COMMA  */
  YYSYMBOL_DOT = 41,                       /* DOT  */
  YYSYMBOL_LP = 42,                        /* LP  */
  YYSYMBOL_RP = 43,                        /* RP  */
  YYSYMBOL_LB = 44,                        /* LB  */
  YYSYMBOL_RB = 45,                        /* RB  */
  YYSYMBOL_NUM = 46,                       /* NUM  */
  YYSYMBOL_STRING = 47,                    /* STRING  */
  YYSYMBOL_ID = 48,                        /* ID  */
  YYSYMBOL_RANGE = 49,                     /* RANGE  */
  YYSYMBOL_REALNUM = 50,                   /* REALNUM  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_prog = 52,                      /* prog  */
  YYSYMBOL_v = 53,                         /* v  */
  YYSYMBOL_va = 54,                        /* va  */
  YYSYMBOL_type = 55,                      /* type  */
  YYSYMBOL_t = 56,                         /* t  */
  YYSYMBOL_varlist = 57,                   /* varlist  */
  YYSYMBOL_stmt_list = 58,                 /* stmt_list  */
  YYSYMBOL_stmt = 59,                      /* stmt  */
  YYSYMBOL_Block = 60,                     /* Block  */
  YYSYMBOL_io_stmt = 61,                   /* io_stmt  */
  YYSYMBOL_varlis = 62,                    /* varlis  */
  YYSYMBOL_if_stmt = 63,                   /* if_stmt  */
  YYSYMBOL_64_1 = 64,                      /* $@1  */
  YYSYMBOL_else_part = 65,                 /* else_part  */
  YYSYMBOL_66_2 = 66,                      /* $@2  */
  YYSYMBOL_while_stmt = 67,                /* while_stmt  */
  YYSYMBOL_68_3 = 68,                      /* $@3  */
  YYSYMBOL_for_stmt = 69,                  /* for_stmt  */
  YYSYMBOL_70_4 = 70,                      /* $@4  */
  YYSYMBOL_assign_stmt = 71,               /* assign_stmt  */
  YYSYMBOL_expression = 72,                /* expression  */
  YYSYMBOL_relop = 73,                     /* relop  */
  YYSYMBOL_e = 74,                         /* e  */
  YYSYMBOL_T = 75,                         /* T  */
  YYSYMBOL_f = 76                          /* f  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   174

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  156

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   207,   207,   209,   210,   211,   213,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   226,   227,   228,
     229,   230,   231,   233,   235,   236,   237,   238,   239,   240,
     241,   241,   242,   242,   247,   249,   249,   261,   261,   278,
     279,   282,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   297,   299,   301,   303,   305,   307,
     309,   311,   313,   323,   328,   332,   344,   352,   353,   356,
     359,   364,   365,   366
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROG_ID", "INT",
  "REAL", "BOOL", "VAR", "CHAR", "TO", "DOWNTO", "IF", "ELSE", "WHILE",
  "FOR", "THEN", "DO", "ARRAY", "OF", "AND", "OR", "NOT", "BEG", "END",
  "READ", "WRITE", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MOD", "EQUAL",
  "ASSIGN", "LT", "GT", "LTE", "GTE", "NE", "SEMICOLON", "COLON", "COMMA",
  "DOT", "LP", "RP", "LB", "RB", "NUM", "STRING", "ID", "RANGE", "REALNUM",
  "$accept", "prog", "v", "va", "type", "t", "varlist", "stmt_list",
  "stmt", "Block", "io_stmt", "varlis", "if_stmt", "$@1", "else_part",
  "$@2", "while_stmt", "$@3", "for_stmt", "$@4", "assign_stmt",
  "expression", "relop", "e", "T", "f", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-94)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       2,   -26,    15,    14,   -94,   -14,     3,   -94,   -14,   110,
     -94,    -2,   116,   124,   -12,    -5,   -94,   124,   -94,   -94,
     -94,   -94,    -7,     6,   -94,   -94,    20,    20,    -1,   -94,
       9,    17,   -21,   -94,   -94,    23,    29,    35,    44,    53,
      61,    95,   -94,     8,     8,   -94,   107,   -94,    74,   131,
     115,   -94,    81,    93,   106,   113,    42,     8,   -94,   -94,
     -94,   -94,   -94,   -94,    98,   131,    97,     8,   -94,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,   -94,     8,   119,   123,   -94,   -33,     8,   -94,
     100,   -23,   -94,   -94,    26,    24,   131,   131,   131,   131,
     131,   131,   131,   131,   115,   115,   -94,   -94,   -94,    24,
     112,   -94,     8,   -94,   111,   -94,   131,     8,     8,     8,
       8,     8,     8,     8,     8,   135,   -94,   156,   -94,     8,
       8,    38,   -94,   131,   131,   131,   131,   131,   131,   131,
     131,     8,   -94,   -94,    69,   126,   127,   131,    24,   -94,
      24,   -94,   -94,    24,   -94,   -94
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     4,     1,     0,     0,    14,     3,     0,
      16,     0,     0,     0,     0,     0,     2,     0,     9,    10,
      11,    12,     0,     0,     7,    13,     0,     0,     0,    23,
       0,     0,     0,    15,    17,     0,     0,     0,     0,     0,
       0,     0,     6,     0,     0,    72,    70,    73,     0,    52,
      64,    68,     0,     0,     0,     0,     0,     0,    22,    19,
      21,    20,    18,     5,     0,    51,     0,     0,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    35,     0,     0,     0,    29,     0,     0,    41,
      40,     0,     8,    69,     0,     0,    49,    50,    48,    43,
      44,    45,    46,    47,    62,    63,    65,    66,    67,     0,
       0,    24,     0,    26,     0,    27,    61,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,    34,    36,     0,
       0,     0,    28,    59,    60,    58,    53,    54,    55,    56,
      57,     0,    32,    31,     0,     0,     0,    42,     0,    37,
       0,    25,    33,     0,    39,    38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -94,   -94,   -94,   -94,   152,   108,   163,   -94,   -93,   167,
     -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,   147,   -94,   -43,    87,    67
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     6,     8,    23,    24,     9,    15,    33,    34,
      35,    87,    36,    95,   143,   148,    37,   109,    38,   153,
      39,    48,    89,    49,    50,    51
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      65,    66,   127,    77,    78,     1,    26,   114,    27,    28,
     115,    56,     3,    90,    91,     4,   128,    10,    29,    30,
      31,     5,   125,    57,    94,    10,    96,    97,    98,    99,
     100,   101,   102,   103,     7,    26,    25,    27,    28,    16,
     110,    43,    41,    32,    42,   116,    10,    53,    30,    31,
      44,    54,    77,    78,    45,   152,    46,   154,    47,    55,
     155,    58,    44,    88,    77,    78,    45,    59,    46,   131,
      47,   126,    32,    60,   133,   134,   135,   136,   137,   138,
     139,   140,    61,   146,    44,   149,   144,   145,    45,    68,
      46,    62,    47,    69,    70,    77,    78,    82,   147,    63,
      69,    70,    18,    19,    20,    71,    21,    72,    73,    74,
      75,    76,    71,    64,    72,    73,    74,    75,    76,   117,
     118,   129,   130,    77,    78,    83,    77,    78,    18,    19,
      20,   119,    21,   120,   121,   122,   123,   124,    77,    78,
      93,    22,   150,    79,    80,    81,   106,   107,   108,    13,
      14,    67,    77,    78,    84,    17,    14,    77,    78,   132,
      85,    86,   111,   112,   104,   105,   113,   141,   142,    40,
     151,    12,    92,    11,    52
};

static const yytype_uint8 yycheck[] =
{
      43,    44,    95,    26,    27,     3,    11,    40,    13,    14,
      43,    32,    38,    56,    57,     0,   109,    22,    23,    24,
      25,     7,    45,    44,    67,    22,    69,    70,    71,    72,
      73,    74,    75,    76,    48,    11,    48,    13,    14,    41,
      83,    21,    49,    48,    38,    88,    22,    48,    24,    25,
      42,    42,    26,    27,    46,   148,    48,   150,    50,    42,
     153,    38,    42,    21,    26,    27,    46,    38,    48,   112,
      50,    45,    48,    38,   117,   118,   119,   120,   121,   122,
     123,   124,    38,    45,    42,    16,   129,   130,    46,    15,
      48,    38,    50,    19,    20,    26,    27,    16,   141,    38,
      19,    20,     4,     5,     6,    31,     8,    33,    34,    35,
      36,    37,    31,    18,    33,    34,    35,    36,    37,    19,
      20,     9,    10,    26,    27,    32,    26,    27,     4,     5,
       6,    31,     8,    33,    34,    35,    36,    37,    26,    27,
      43,    17,    16,    28,    29,    30,    79,    80,    81,    39,
      40,    44,    26,    27,    48,    39,    40,    26,    27,    48,
      47,    48,    43,    44,    77,    78,    43,    32,    12,    17,
      43,     8,    64,     6,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    52,    38,     0,     7,    53,    48,    54,    57,
      22,    60,    57,    39,    40,    58,    41,    39,     4,     5,
       6,     8,    17,    55,    56,    48,    11,    13,    14,    23,
      24,    25,    48,    59,    60,    61,    63,    67,    69,    71,
      55,    49,    38,    21,    42,    46,    48,    50,    72,    74,
      75,    76,    72,    48,    42,    42,    32,    44,    38,    38,
      38,    38,    38,    38,    18,    74,    74,    44,    15,    19,
      20,    31,    33,    34,    35,    36,    37,    26,    27,    28,
      29,    30,    16,    32,    48,    47,    48,    62,    21,    73,
      74,    74,    56,    43,    74,    64,    74,    74,    74,    74,
      74,    74,    74,    74,    75,    75,    76,    76,    76,    68,
      74,    43,    44,    43,    40,    43,    74,    19,    20,    31,
      33,    34,    35,    36,    37,    45,    45,    59,    59,     9,
      10,    74,    48,    74,    74,    74,    74,    74,    74,    74,
      74,    32,    12,    65,    74,    74,    45,    74,    66,    16,
      16,    43,    59,    70,    59,    59
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    55,    55,    56,
      56,    56,    56,    57,    57,    58,    58,    59,    59,    59,
      59,    59,    59,    60,    61,    61,    61,    61,    62,    62,
      64,    63,    66,    65,    65,    68,    67,    70,    69,    69,
      71,    71,    71,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    74,    74,    74,    75,    75,    75,    75,    76,
      76,    76,    76,    76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     2,     0,     5,     4,     1,     4,     1,
       1,     1,     1,     3,     1,     2,     0,     1,     2,     2,
       2,     2,     2,     3,     4,     7,     4,     4,     3,     1,
       0,     6,     0,     3,     0,     0,     5,     0,     9,     8,
       3,     3,     6,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     1,     3,     3,     3,     1,     3,
       1,     4,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* prog: PROG_ID SEMICOLON v Block DOT  */
#line 207 "5.y"
                                        {}
#line 1576 "y.tab.c"
    break;

  case 5: /* va: va varlist COLON type SEMICOLON  */
#line 211 "5.y"
                                        {current_type = (yyvsp[-1].sval); assign_type((yyvsp[-3].sym), current_type); if(is_array){ setArray((yyvsp[-3].sym),is_array);
                                                                                                  } is_array=0;}
#line 1583 "y.tab.c"
    break;

  case 6: /* va: varlist COLON type SEMICOLON  */
#line 213 "5.y"
                                   {current_type = (yyvsp[-1].sval); assign_type((yyvsp[-3].sym), current_type); if(is_array){ setArray((yyvsp[-3].sym),is_array);
                                                                                                  } is_array=0; }
#line 1590 "y.tab.c"
    break;

  case 7: /* type: t  */
#line 215 "5.y"
            { strcpy((yyval.sval), (yyvsp[0].sval)); }
#line 1596 "y.tab.c"
    break;

  case 8: /* type: ARRAY RANGE OF t  */
#line 216 "5.y"
                           { strcpy((yyval.sval) , (yyvsp[0].sval)); is_array = 1;}
#line 1602 "y.tab.c"
    break;

  case 9: /* t: INT  */
#line 217 "5.y"
           {strcpy((yyval.sval), "INT");}
#line 1608 "y.tab.c"
    break;

  case 10: /* t: REAL  */
#line 218 "5.y"
               {strcpy((yyval.sval) ,"REAL");}
#line 1614 "y.tab.c"
    break;

  case 11: /* t: BOOL  */
#line 219 "5.y"
                {strcpy((yyval.sval) ,"BOOL");}
#line 1620 "y.tab.c"
    break;

  case 12: /* t: CHAR  */
#line 220 "5.y"
               {strcpy((yyval.sval), "CHAR");}
#line 1626 "y.tab.c"
    break;

  case 13: /* varlist: varlist COMMA ID  */
#line 221 "5.y"
                              { (yyval.sym) = insert((yyvsp[0].sval)); (yyval.sym)->next = (yyvsp[-2].sym); }
#line 1632 "y.tab.c"
    break;

  case 14: /* varlist: ID  */
#line 222 "5.y"
         { (yyval.sym) = insert((yyvsp[0].sval)); }
#line 1638 "y.tab.c"
    break;

  case 24: /* io_stmt: READ LP ID RP  */
#line 235 "5.y"
                          {  assign((yyvsp[-1].sval)); }
#line 1644 "y.tab.c"
    break;

  case 25: /* io_stmt: READ LP ID LB e RB RP  */
#line 236 "5.y"
                               { assign((yyvsp[-4].sval)); }
#line 1650 "y.tab.c"
    break;

  case 28: /* varlis: varlis COMMA ID  */
#line 239 "5.y"
                            { check_assigned((yyvsp[0].sval)); }
#line 1656 "y.tab.c"
    break;

  case 29: /* varlis: ID  */
#line 240 "5.y"
                 {check_assigned((yyvsp[0].sval)); }
#line 1662 "y.tab.c"
    break;

  case 30: /* $@1: %empty  */
#line 241 "5.y"
                                { emit("ifFalse", "IfCondition", "GOTO", create_temp_label()); }
#line 1668 "y.tab.c"
    break;

  case 32: /* $@2: %empty  */
#line 242 "5.y"
                    { 
        
        emit(currLabel(), ":", "ElseCode", "-");
        }
#line 1677 "y.tab.c"
    break;

  case 34: /* else_part: %empty  */
#line 247 "5.y"
      { emit(currLabel(), ":", "doNothing", "-"); }
#line 1683 "y.tab.c"
    break;

  case 35: /* $@3: %empty  */
#line 249 "5.y"
                                    {
        emit(wcreate_temp_label(), ":", "WhileCode", "-");
        emit("ifFalse", "Condition", "GOTO", wcreate_temp_label());
    }
#line 1692 "y.tab.c"
    break;

  case 36: /* while_stmt: WHILE expression DO $@3 stmt  */
#line 253 "5.y"
        {
        wtemp_label_counter--;
        emit("GOTO", "WhileCode", "", wcurrLabel());
        wtemp_label_counter++;

        emit(wcurrLabel(), ":", "done", "-");

    }
#line 1705 "y.tab.c"
    break;

  case 37: /* $@4: %empty  */
#line 261 "5.y"
                                        { assign((yyvsp[-5].sval));
        emit(forcreate_temp_label(), ":", "ForCode", "-");
        char* temp12 = malloc(20);
        sprintf(temp12 , "%s", (yyvsp[-5].sval));
        char* temp13 = malloc(20);
        strcpy(temp13, "If ");
        strcat(temp13, temp12);
        emit(temp13, "OutOfRange", "GOTO", forcreate_temp_label());
    }
#line 1719 "y.tab.c"
    break;

  case 38: /* for_stmt: FOR ID ASSIGN e TO e DO $@4 stmt  */
#line 269 "5.y"
          {
        fortemp_label_counter--;
        char* temp12 = malloc(20);
        strcpy(temp12, (yyvsp[-7].sval));
        emit("+", temp12 , "1" , temp12);
        emit("GOTO", "ForCode", "", forcurrLabel());
        fortemp_label_counter++;
        emit(forcurrLabel(), ":", "done", "-");
    }
#line 1733 "y.tab.c"
    break;

  case 39: /* for_stmt: FOR ID ASSIGN e DOWNTO e DO stmt  */
#line 278 "5.y"
                                           { assign((yyvsp[-6].sval));}
#line 1739 "y.tab.c"
    break;

  case 40: /* assign_stmt: ID ASSIGN e  */
#line 279 "5.y"
                             { assign((yyvsp[-2].sval)); symbol* s=lookup((yyvsp[-2].sval)); if(s->type!=NULL) check_expr_type(s, (yyvsp[0].sym));
                emit(":=", (yyvsp[0].sym)->name, "", (yyvsp[-2].sval)); 
        }
#line 1747 "y.tab.c"
    break;

  case 41: /* assign_stmt: ID ASSIGN relop  */
#line 282 "5.y"
                         {symbol* xyz=malloc(sizeof(symbol)); strcpy(xyz->type,"BOOL"); symbol* s=lookup((yyvsp[-2].sval)); check_expr_type(s, xyz); assign((yyvsp[-2].sval));
                         emit(":=", (yyvsp[0].sym)->name, "", s->name); }
#line 1754 "y.tab.c"
    break;

  case 42: /* assign_stmt: ID LB e RB ASSIGN e  */
#line 284 "5.y"
                             { assign((yyvsp[-5].sval)); }
#line 1760 "y.tab.c"
    break;

  case 52: /* expression: e  */
#line 294 "5.y"
            { (yyval.sym) = (yyvsp[0].sym); }
#line 1766 "y.tab.c"
    break;

  case 53: /* relop: e LT e  */
#line 295 "5.y"
                  {strcpy((yyval.sym)->name, create_temp_var());
                    emit("<", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, (yyval.sym)->name); }
#line 1773 "y.tab.c"
    break;

  case 54: /* relop: e GT e  */
#line 297 "5.y"
                 {strcpy((yyval.sym)->name, create_temp_var());
                    emit(">", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, (yyval.sym)->name); }
#line 1780 "y.tab.c"
    break;

  case 55: /* relop: e LTE e  */
#line 299 "5.y"
                  {strcpy((yyval.sym)->name, create_temp_var());
                    emit("<=", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, (yyval.sym)->name); }
#line 1787 "y.tab.c"
    break;

  case 56: /* relop: e GTE e  */
#line 301 "5.y"
                  {strcpy((yyval.sym)->name, create_temp_var());
                    emit(">=", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, (yyval.sym)->name); }
#line 1794 "y.tab.c"
    break;

  case 57: /* relop: e NE e  */
#line 303 "5.y"
                 {strcpy((yyval.sym)->name, create_temp_var());
                    emit("<>", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, (yyval.sym)->name); }
#line 1801 "y.tab.c"
    break;

  case 58: /* relop: e EQUAL e  */
#line 305 "5.y"
                    {strcpy((yyval.sym)->name, create_temp_var());
                    emit("=", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, (yyval.sym)->name); }
#line 1808 "y.tab.c"
    break;

  case 59: /* relop: e AND e  */
#line 307 "5.y"
                  {strcpy((yyval.sym)->name, create_temp_var());
                    emit("AND", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, (yyval.sym)->name); }
#line 1815 "y.tab.c"
    break;

  case 60: /* relop: e OR e  */
#line 309 "5.y"
                 {strcpy((yyval.sym)->name, create_temp_var());
                    emit("OR", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, (yyval.sym)->name); }
#line 1822 "y.tab.c"
    break;

  case 61: /* relop: NOT e  */
#line 311 "5.y"
                {strcpy((yyval.sym)->name, create_temp_var());
                    emit("NOT", (yyvsp[0].sym)->name, "", (yyval.sym)->name); }
#line 1829 "y.tab.c"
    break;

  case 62: /* e: e PLUS T  */
#line 313 "5.y"
                { (yyval.sym) = malloc(sizeof(symbol)); 
                        strcpy((yyval.sym)->type, (yyvsp[0].sym)->type); 
                    char* temp = create_temp_var();
                    
                    insert(temp);
                    symbol* s = lookup(temp);
                    strcpy(s->type, "INT");
                    strcpy((yyval.sym)->name, s->name);
                    emit("+", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, (yyval.sym)->name); 
                        }
#line 1844 "y.tab.c"
    break;

  case 63: /* e: e MINUS T  */
#line 323 "5.y"
                    { (yyval.sym) = malloc(sizeof(symbol)); 
                    strcpy((yyval.sym)->type, (yyvsp[0].sym)->type);
                    strcpy((yyval.sym)->name, create_temp_var());
                    emit("-", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, (yyval.sym)->name);
                    }
#line 1854 "y.tab.c"
    break;

  case 64: /* e: T  */
#line 328 "5.y"
            { (yyval.sym) = malloc(sizeof(symbol)); 
                    strcpy((yyval.sym)->type, (yyvsp[0].sym)->type);
                    (yyval.sym) = (yyvsp[0].sym);
                     }
#line 1863 "y.tab.c"
    break;

  case 65: /* T: T MULTIPLY f  */
#line 332 "5.y"
                    { (yyval.sym) = malloc(sizeof(symbol)); 
                        if(strcmp((yyvsp[-2].sym)->type,"REAL")==0) strcpy((yyval.sym)->type, "REAL");
                        else if(strcmp((yyvsp[0].sym)->type,"REAL")==0) strcpy((yyval.sym)->type, "REAL");
                        else
                    strcpy((yyval.sym)->type, (yyvsp[0].sym)->type); 
                    
                    strcpy((yyval.sym)->name, create_temp_var());
                   // printf("ooooo%s\n",$1->name);
                    emit("*", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, (yyval.sym)->name);


                    }
#line 1880 "y.tab.c"
    break;

  case 66: /* T: T DIVIDE f  */
#line 344 "5.y"
                     { (yyval.sym) = malloc(sizeof(symbol)); strcpy((yyval.sym)->type, "REAL");
                           
                    
                    strcpy((yyval.sym)->name, create_temp_var());
                   // printf("%d\n",temp_var_counter);
                    emit("/", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, (yyval.sym)->name);
                   
        }
#line 1893 "y.tab.c"
    break;

  case 67: /* T: T MOD f  */
#line 352 "5.y"
                  { (yyval.sym) = malloc(sizeof(symbol)); strcpy((yyval.sym)->type, "INT");}
#line 1899 "y.tab.c"
    break;

  case 68: /* T: f  */
#line 353 "5.y"
            { (yyval.sym) = malloc(sizeof(symbol)); 
                    strcpy((yyval.sym)->type, (yyvsp[0].sym)->type);
                    (yyval.sym) = (yyvsp[0].sym); }
#line 1907 "y.tab.c"
    break;

  case 69: /* f: LP e RP  */
#line 356 "5.y"
                { (yyval.sym) = malloc(sizeof(symbol)); 
                    strcpy((yyval.sym)->type, (yyvsp[-1].sym)->type); 
                    (yyval.sym)=(yyvsp[-1].sym);}
#line 1915 "y.tab.c"
    break;

  case 70: /* f: ID  */
#line 359 "5.y"
            { check_assigned((yyvsp[0].sval)); (yyval.sym) = malloc(sizeof(symbol)); symbol* s = lookup((yyvsp[0].sval)); 
                if(s->type=="INT" || s->type=="REAL")
                    strcpy((yyval.sym)->type, s->type);
                    strcpy((yyval.sym)->name, (yyvsp[0].sval));
                     }
#line 1925 "y.tab.c"
    break;

  case 71: /* f: ID LB e RB  */
#line 364 "5.y"
                    { check_assigned((yyvsp[-3].sval)); }
#line 1931 "y.tab.c"
    break;

  case 72: /* f: NUM  */
#line 365 "5.y"
             { (yyval.sym) = malloc(sizeof(symbol)); sprintf((yyval.sym)->name,"%d",(yyvsp[0].ival)); strcpy((yyval.sym)->type, "INT"); }
#line 1937 "y.tab.c"
    break;

  case 73: /* f: REALNUM  */
#line 366 "5.y"
                 { (yyval.sym) = malloc(sizeof(symbol)); strcpy((yyval.sym)->type, "REAL"); }
#line 1943 "y.tab.c"
    break;


#line 1947 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 367 "5.y"

     
   int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("No filename provided!\n");
        return 1;
    }
    char *filename = argv[1];
    yyin = fopen(filename, "r");
    if(yyin == NULL){
        printf("Error opening file!\n");
        return 1;
    }
    yyparse();
    if(flag==1){
        //printf("valid input\n");
    }
        printf("symbol table\n");
        printf("%-25s %-25s %-25s %-25s\n", "Name", "Type", "Assigned", "isArray");
        for(int i=0;i<symtab_len;i++){
            if(symtab[i].name[0]!='t')
            printf("%-25s %-25s %-25d %-25d\n", symtab[i].name, symtab[i].type, symtab[i].assigned, symtab[i].isArray);
        }
    // printf("quadruple table\n");
    //     for(int i=0;i<quad_len;i++  ){
    //         printf("%-25s %-25s %-25s %-25s\n", quad[i].op, quad[i].arg1, quad[i].arg2, quad[i].result);
    //     }
    fclose(yyin);
    return 0;
}
     
    int yyerror(const char *msg) {
        printf("Syntax error: %s\n", msg);
        return 0;
    }
