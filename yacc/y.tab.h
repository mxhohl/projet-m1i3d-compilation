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
    VAR = 258,
    ENTIER = 259,
    STR = 260,
    BACK = 261,
    DO = 262,
    WHILE = 263,
    FOR = 264,
    IF = 265,
    ELSE = 266,
    BREAK = 267,
    SWITCH = 268,
    CASE = 269,
    RETURN = 270,
    MAIN = 271,
    INCLUDE = 272,
    DEFINE = 273,
    UPPER = 274,
    UPPEREG = 275,
    LOWER = 276,
    LOWEREG = 277,
    EQ = 278,
    INEQ = 279,
    PLUS = 280,
    MINUS = 281,
    MULT = 282,
    DIV = 283,
    MODULO = 284,
    EGAL = 285,
    BRACEL = 286,
    BRACER = 287,
    BRACKETL = 288,
    BRACKETR = 289,
    SM = 290,
    COM = 291,
    DOT = 292,
    DOT2 = 293,
    TABL = 294,
    TABR = 295,
    INT = 296,
    VOID = 297,
    PRINTF = 298,
    AND = 299,
    OR = 300
  };
#endif
/* Tokens.  */
#define VAR 258
#define ENTIER 259
#define STR 260
#define BACK 261
#define DO 262
#define WHILE 263
#define FOR 264
#define IF 265
#define ELSE 266
#define BREAK 267
#define SWITCH 268
#define CASE 269
#define RETURN 270
#define MAIN 271
#define INCLUDE 272
#define DEFINE 273
#define UPPER 274
#define UPPEREG 275
#define LOWER 276
#define LOWEREG 277
#define EQ 278
#define INEQ 279
#define PLUS 280
#define MINUS 281
#define MULT 282
#define DIV 283
#define MODULO 284
#define EGAL 285
#define BRACEL 286
#define BRACER 287
#define BRACKETL 288
#define BRACKETR 289
#define SM 290
#define COM 291
#define DOT 292
#define DOT2 293
#define TABL 294
#define TABR 295
#define INT 296
#define VOID 297
#define PRINTF 298
#define AND 299
#define OR 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
