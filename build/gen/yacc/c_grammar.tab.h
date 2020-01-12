/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_BUILD_GEN_YACC_C_GRAMMAR_TAB_H_INCLUDED
# define YY_YY_BUILD_GEN_YACC_C_GRAMMAR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    EOFILE = 258,
    TYPE_INT = 259,
    TYPE_DOUBLE = 260,
    STATIC_INT = 261,
    STATIC_DOUBLE = 262,
    ID = 263,
    OP_PLUS = 264,
    OP_MINUS = 265,
    OP_MULTIPLY = 266,
    OP_DIVIDE = 267,
    OP_INCREMENT = 268,
    OP_DECREMENT = 269,
    OP_EQ = 270,
    OP_NEQ = 271,
    OP_AND = 272,
    OP_OR = 273,
    OP_LOWER = 274,
    OP_LOWER_EQ = 275,
    OP_GREATER = 276,
    OP_GREATER_EQ = 277,
    OP_NOT = 278,
    MAIN = 279,
    RETURN = 280,
    IF = 281,
    ELSE = 282,
    WHILE = 283,
    FOR = 284,
    PREPRODEFINE = 285,
    PRINTF = 286,
    SEMICOLON = 287,
    COMMA = 288,
    EQUAL = 289,
    LPARENTHESIS = 290,
    RPARENTHESIS = 291,
    LBRACE = 292,
    RBRACE = 293,
    LBRACKET = 294,
    RBRACKET = 295,
    NO_ELSE = 296
  };
#endif
/* Tokens.  */
#define EOFILE 258
#define TYPE_INT 259
#define TYPE_DOUBLE 260
#define STATIC_INT 261
#define STATIC_DOUBLE 262
#define ID 263
#define OP_PLUS 264
#define OP_MINUS 265
#define OP_MULTIPLY 266
#define OP_DIVIDE 267
#define OP_INCREMENT 268
#define OP_DECREMENT 269
#define OP_EQ 270
#define OP_NEQ 271
#define OP_AND 272
#define OP_OR 273
#define OP_LOWER 274
#define OP_LOWER_EQ 275
#define OP_GREATER 276
#define OP_GREATER_EQ 277
#define OP_NOT 278
#define MAIN 279
#define RETURN 280
#define IF 281
#define ELSE 282
#define WHILE 283
#define FOR 284
#define PREPRODEFINE 285
#define PRINTF 286
#define SEMICOLON 287
#define COMMA 288
#define EQUAL 289
#define LPARENTHESIS 290
#define RPARENTHESIS 291
#define LBRACE 292
#define RBRACE 293
#define LBRACKET 294
#define RBRACKET 295
#define NO_ELSE 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 33 "src/c_grammar.y" /* yacc.c:1909  */

    int integer;
    double floating;
    char* str;
    struct {
        char* name;
        int val;
    }define;
    struct s_astNode* ast;

#line 147 "build/gen/yacc/c_grammar.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BUILD_GEN_YACC_C_GRAMMAR_TAB_H_INCLUDED  */
