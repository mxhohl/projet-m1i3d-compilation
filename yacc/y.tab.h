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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    ENTIER = 258,
    VAR = 259,
    STR = 260,
    EXT = 261,
    END = 262,
    DO = 263,
    WHILE = 264,
    FOR = 265,
    IF = 266,
    ELSE = 267,
    BREAK = 268,
    SWITCH = 269,
    CASE = 270,
    RETURN = 271,
    INCLUDE = 272,
    DEFINE = 273,
    DIESE = 274,
    UPPER = 275,
    UPPEREG = 276,
    LOWER = 277,
    LOWEREG = 278,
    EQ = 279,
    INEQ = 280,
    PLUS = 281,
    MINUS = 282,
    MULT = 283,
    DIV = 284,
    MODULO = 285,
    ASSIGN = 286,
    BRACEL = 287,
    BRACER = 288,
    BRACKETL = 289,
    BRACKETR = 290,
    SM = 291,
    COM = 292,
    DOT = 293,
    DOT2 = 294,
    TABL = 295,
    TABR = 296,
    INT = 297,
    VOID = 298,
    PRINTF = 299,
    MAIN = 300,
    AND = 301,
    OR = 302
  };
#endif
/* Tokens.  */
#define ENTIER 258
#define VAR 259
#define STR 260
#define EXT 261
#define END 262
#define DO 263
#define WHILE 264
#define FOR 265
#define IF 266
#define ELSE 267
#define BREAK 268
#define SWITCH 269
#define CASE 270
#define RETURN 271
#define INCLUDE 272
#define DEFINE 273
#define DIESE 274
#define UPPER 275
#define UPPEREG 276
#define LOWER 277
#define LOWEREG 278
#define EQ 279
#define INEQ 280
#define PLUS 281
#define MINUS 282
#define MULT 283
#define DIV 284
#define MODULO 285
#define ASSIGN 286
#define BRACEL 287
#define BRACER 288
#define BRACKETL 289
#define BRACKETR 290
#define SM 291
#define COM 292
#define DOT 293
#define DOT2 294
#define TABL 295
#define TABR 296
#define INT 297
#define VOID 298
#define PRINTF 299
#define MAIN 300
#define AND 301
#define OR 302

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 10 "c_gram.y" /* yacc.c:1909  */

  char* str;

#line 152 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
