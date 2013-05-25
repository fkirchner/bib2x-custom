
/*  A Bison parser, made from template.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse templateparse
#define yylex templatelex
#define yyerror templateerror
#define yylval templatelval
#define yychar templatechar
#define yydebug templatedebug
#define yynerrs templatenerrs
#define	TOKEN_SORT	257
#define	TOKEN_FOR	258
#define	TOKEN_ROF	259
#define	TOKEN_LPAR	260
#define	TOKEN_RPAR	261
#define	TOKEN_WORD	262
#define	TOKEN_COMMA	263
#define	TOKEN_BIB	264
#define	TOKEN_DEF	265
#define	TOKEN_FED	266
#define	TOKEN_HASH	267
#define	TOKEN_STEP	268
#define	TOKEN_OPERATOR	269
#define	TOKEN_WHITESPACE	270
#define	TOKEN_SEMICOLON	271
#define	TOKEN_ALMOSTANY	272
#define	TOKEN_COMMAND	273
#define	TOKEN_COLON	274
#define	TOKEN_RBRACE	275
#define	TOKEN_VALUE	276
#define	TOKEN_LBRACE	277
#define	TOKEN_NEWLINE	278
#define	TOKEN_PRG	279
#define	TOKEN_GRP	280
#define	TOKEN_EXCLAM	281
#define	TOKEN_DEFINITION	282
#define	TOKEN_BIBTOKENFINISHED	283
#define	TOKEN_STEPCONTENT	284
#define	TOKEN_MOD	285
#define	TOKEN_EQUALS	286
#define	TOKEN_BIBTOKEN	287
#define	TOKEN_WORDX	288
#define	TOKEN_CLASS	289
#define	TOKEN_RED	290
#define	TOKEN_NUMBER	291

#line 1 "template.y"

#include <map>
#include <iostream>
#include <string>

#include <ctype.h> 

#include "template.h"

extern int templateparse(void);
extern int templatelex(void);
extern int nTemplateLine;


CTemplate& g_oTemplate = CTemplate::Instance();

char* str_tolower(char* c);


int templatewrap()
    {
    return 1;
    }


void templateerror(const char* str)
    {
    std::cerr << "Error in Line " << nTemplateLine << ": " << str << std::endl;
    }



#line 34 "template.y"
typedef union
{
    int number;
    char* string;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		134
#define	YYFLAG		-32768
#define	YYNTBASE	38

#define YYTRANSLATE(x) ((unsigned)(x) <= 291 ? yytranslate[x] : 67)

static const char yytranslate[] = {     0,
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
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     3,     6,     8,    10,    12,    14,    19,    28,
    40,    42,    45,    49,    53,    54,    57,    60,    64,    68,
    70,    72,    74,    82,    88,    96,   102,   111,   118,   124,
   125,   129,   133,   135,   137,   139,   141,   143,   145,   148,
   151,   153,   156,   160,   163,   166,   168,   171,   175,   177,
   182,   187,   190,   193,   196,   200,   201,   204,   205,   207,
   209,   212,   214
};

static const short yyrhs[] = {    39,
     0,     0,    39,    40,     0,    46,     0,    42,     0,    47,
     0,    19,     0,    31,     6,    19,     7,     0,    14,     6,
    41,    17,    41,    17,    41,     7,     0,    31,     6,    14,
     6,    41,    17,    41,    17,    41,     7,     7,     0,    30,
     0,    41,    30,     0,    11,    43,    12,     0,    35,    45,
    44,     0,     0,    43,    28,     0,     8,    35,     0,     8,
     9,    44,     0,     8,    32,    23,     0,    18,     0,    24,
     0,    16,     0,    53,     6,    51,    20,    59,    39,     5,
     0,    53,     6,    59,    39,     5,     0,    54,     6,    51,
    20,    59,    39,    25,     0,    54,     6,    59,    39,    25,
     0,    52,     6,    51,    20,    56,    48,    64,    10,     0,
    52,     6,    56,    48,    64,    10,     0,    55,     6,    51,
    20,    59,     0,     0,    48,    64,    49,     0,    50,    39,
    29,     0,    33,     0,     3,     0,    10,     0,     4,     0,
    26,     0,    36,     0,    57,     7,     0,    57,    60,     0,
    60,     0,    58,    17,     0,    58,     9,    57,     0,    13,
     8,     0,    27,     8,     0,     8,     0,     8,     7,     0,
     8,    17,    60,     0,    60,     0,    61,    23,    62,     7,
     0,    61,    23,    62,    60,     0,    34,    15,     0,     8,
    15,     0,    63,    21,     0,    63,     9,    62,     0,     0,
    63,    22,     0,     0,    65,     0,    66,     0,    65,    66,
     0,    16,     0,    24,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    60,    63,    64,    67,    68,    69,    70,    71,    72,    73,
    76,    77,    88,    89,    91,    92,    95,    96,    98,   102,
   104,   105,   109,   110,   111,   112,   113,   114,   115,   118,
   119,   121,   123,   125,   127,   128,   129,   130,   132,   133,
   134,   137,   138,   140,   142,   143,   146,   147,   148,   152,
   153,   156,   157,   159,   160,   163,   164,   168,   169,   172,
   173,   176,   177
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","TOKEN_SORT",
"TOKEN_FOR","TOKEN_ROF","TOKEN_LPAR","TOKEN_RPAR","TOKEN_WORD","TOKEN_COMMA",
"TOKEN_BIB","TOKEN_DEF","TOKEN_FED","TOKEN_HASH","TOKEN_STEP","TOKEN_OPERATOR",
"TOKEN_WHITESPACE","TOKEN_SEMICOLON","TOKEN_ALMOSTANY","TOKEN_COMMAND","TOKEN_COLON",
"TOKEN_RBRACE","TOKEN_VALUE","TOKEN_LBRACE","TOKEN_NEWLINE","TOKEN_PRG","TOKEN_GRP",
"TOKEN_EXCLAM","TOKEN_DEFINITION","TOKEN_BIBTOKENFINISHED","TOKEN_STEPCONTENT",
"TOKEN_MOD","TOKEN_EQUALS","TOKEN_BIBTOKEN","TOKEN_WORDX","TOKEN_CLASS","TOKEN_RED",
"TOKEN_NUMBER","mybegin","entries","entry","stepcontent","define","definition",
"members","classtarget","between","loop","tokenentries","token","mybibtoken",
"tok_sort","mybib","myfor","mygrp","myred","exconditions","incexclusions","incexclusion",
"conditions","constraints","target","values","value","optspace","space","single_space", NULL
};
#endif

static const short yyr1[] = {     0,
    38,    39,    39,    40,    40,    40,    40,    40,    40,    40,
    41,    41,    42,    42,    43,    43,    44,    44,    45,    46,
    46,    46,    47,    47,    47,    47,    47,    47,    47,    48,
    48,    49,    50,    51,    52,    53,    54,    55,    56,    56,
    56,    57,    57,    58,    58,    58,    59,    59,    59,    60,
    60,    61,    61,    62,    62,    63,    63,    64,    64,    65,
    65,    66,    66
};

static const short yyr2[] = {     0,
     1,     0,     2,     1,     1,     1,     1,     4,     8,    11,
     1,     2,     3,     3,     0,     2,     2,     3,     3,     1,
     1,     1,     7,     5,     7,     5,     8,     6,     5,     0,
     3,     3,     1,     1,     1,     1,     1,     1,     2,     2,
     1,     2,     3,     2,     2,     1,     2,     3,     1,     4,
     4,     2,     2,     2,     3,     0,     2,     0,     1,     1,
     2,     1,     1
};

static const short yydefact[] = {     2,
     1,    36,    35,    15,     0,    22,    20,     7,    21,    37,
     0,     0,    38,     3,     5,     4,     6,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    13,    16,    11,     0,     0,     0,     0,     0,    14,    34,
    46,     0,     0,     0,     0,    30,     0,     0,    41,     0,
     0,     0,     2,    49,     0,     2,     0,     0,    12,     0,
     8,    19,     0,    17,    53,    44,    45,    52,     0,    58,
    39,     0,    40,     0,    42,    56,    47,     0,     0,     0,
     0,     0,     0,     0,     0,    18,    30,    62,    63,     0,
    59,    60,    46,    43,     0,     0,    48,     2,    24,     2,
    26,    29,     0,     0,    58,    28,    33,    31,     2,    61,
    50,    51,    56,    54,    57,     0,     0,     0,     0,     0,
     0,    55,    23,    25,     9,     0,    27,    32,     0,     0,
    10,     0,     0,     0
};

static const short yydefgoto[] = {   132,
     1,    14,    34,    15,    22,    39,    26,    16,    17,    70,
   108,   109,    45,    18,    19,    20,    21,    46,    47,    48,
    53,    54,    50,    95,    96,    90,    91,    92
};

static const short yypact[] = {-32768,
   148,-32768,-32768,-32768,     6,-32768,-32768,-32768,-32768,-32768,
    11,    36,-32768,-32768,-32768,-32768,-32768,    41,    43,    55,
    70,     1,    48,    -9,    47,    93,    28,     8,     8,    99,
-32768,-32768,-32768,     2,   101,   115,   119,    -2,-32768,-32768,
   130,   109,   132,   131,   105,-32768,    17,    68,-32768,   134,
   156,   128,-32768,-32768,   133,-32768,   145,    48,-32768,    48,
-32768,-32768,    93,-32768,-32768,-32768,-32768,-32768,    96,    84,
-32768,   130,-32768,   142,-32768,-32768,-32768,    29,    30,     4,
    30,    56,    30,    69,    94,-32768,-32768,-32768,-32768,    24,
    84,-32768,-32768,-32768,    19,   110,-32768,-32768,-32768,-32768,
-32768,-32768,    48,    48,    84,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,    79,   102,    58,   117,    61,
   125,-32768,-32768,-32768,-32768,    48,-32768,-32768,    66,   161,
-32768,   170,   178,-32768
};

static const short yypgoto[] = {-32768,
   -50,-32768,   -58,-32768,-32768,   118,-32768,-32768,-32768,    95,
-32768,-32768,   147,-32768,-32768,-32768,-32768,   111,   112,-32768,
   -25,   -26,-32768,    72,-32768,    82,-32768,    97
};


#define	YYLAST		188


static const short yytable[] = {    84,
    49,    85,    80,    56,    35,    82,    63,     2,    99,    36,
    40,    23,    31,     3,     4,    51,    24,     5,    58,     6,
    73,     7,     8,    71,    72,   111,    72,     9,    32,    10,
    40,    59,    64,   106,    11,    41,    72,    51,    12,    13,
    42,    44,    49,    25,   118,   119,    27,   116,    28,   117,
    44,    97,    44,    98,    43,   100,   107,   102,   121,     2,
    29,    44,    44,    44,   125,     3,     4,   129,   112,     5,
   127,     6,   130,     7,     8,    30,    74,    33,    37,     9,
   101,    10,     2,   123,    75,   103,    11,    59,     3,     4,
    12,    13,     5,   107,     6,    59,     7,     8,    59,    88,
    38,    40,     9,    41,    10,     2,    60,    89,    42,    11,
   104,     3,     4,    12,    13,     5,    66,     6,   113,     7,
     8,    61,    43,    59,    69,     9,   124,    10,     2,    44,
   114,   115,    11,   126,     3,     4,    12,    13,     5,    67,
     6,    62,     7,     8,    65,    68,    59,    79,     9,    93,
    10,     2,    81,   128,    42,    11,    76,     3,     4,    12,
    13,     5,    77,     6,    83,     7,     8,   131,    43,   133,
    65,     9,    78,    10,    52,    55,    57,   134,    11,    87,
    86,   105,    12,    13,   122,    94,   120,   110
};

static const short yycheck[] = {    58,
    27,    60,    53,    29,    14,    56,     9,     4,     5,    19,
     3,     6,    12,    10,    11,     8,     6,    14,    17,    16,
    47,    18,    19,     7,     8,     7,     8,    24,    28,    26,
     3,    30,    35,    10,    31,     8,     8,     8,    35,    36,
    13,    34,    69,     8,   103,   104,     6,    98,     6,   100,
    34,    78,    34,    79,    27,    81,    33,    83,   109,     4,
     6,    34,    34,    34,     7,    10,    11,   126,    95,    14,
    10,    16,     7,    18,    19,     6,     9,    30,    32,    24,
    25,    26,     4,     5,    17,    17,    31,    30,    10,    11,
    35,    36,    14,    33,    16,    30,    18,    19,    30,    16,
     8,     3,    24,     8,    26,     4,     6,    24,    13,    31,
    17,    10,    11,    35,    36,    14,     8,    16,     9,    18,
    19,     7,    27,    30,    20,    24,    25,    26,     4,    34,
    21,    22,    31,    17,    10,    11,    35,    36,    14,     8,
    16,    23,    18,    19,    15,    15,    30,    20,    24,     8,
    26,     4,    20,    29,    13,    31,    23,    10,    11,    35,
    36,    14,     7,    16,    20,    18,    19,     7,    27,     0,
    15,    24,    17,    26,    28,    29,    30,     0,    31,    69,
    63,    87,    35,    36,   113,    74,   105,    91
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 60 "template.y"
{;
    break;}
case 2:
#line 63 "template.y"
{;
    break;}
case 3:
#line 64 "template.y"
{ ;
    break;}
case 4:
#line 67 "template.y"
{ ;
    break;}
case 5:
#line 68 "template.y"
{;
    break;}
case 6:
#line 69 "template.y"
{ ;
    break;}
case 7:
#line 70 "template.y"
{ g_oTemplate.Command(yyvsp[0].string); ;
    break;}
case 8:
#line 71 "template.y"
{ g_oTemplate.Modifier(yyvsp[-3].string, yyvsp[-1].string); ;
    break;}
case 9:
#line 72 "template.y"
{ g_oTemplate.Step(yyvsp[-7].string,yyvsp[-5].string,yyvsp[-3].string,yyvsp[-1].string); ;
    break;}
case 10:
#line 73 "template.y"
{ g_oTemplate.Step(yyvsp[-8].string,yyvsp[-6].string,yyvsp[-4].string,yyvsp[-2].string,yyvsp[-10].string); ;
    break;}
case 11:
#line 76 "template.y"
{ yyval.string=strdup(yyvsp[0].string); ;
    break;}
case 12:
#line 77 "template.y"
{ std::string sA; sA += yyvsp[-1].string; sA += yyvsp[0].string; yyval.string=strdup(sA.c_str());;
    break;}
case 13:
#line 88 "template.y"
{ g_oTemplate.DefFinish( yyvsp[-2].string ); ;
    break;}
case 14:
#line 89 "template.y"
{  ;
    break;}
case 16:
#line 92 "template.y"
{ g_oTemplate.AddDefinition(yyvsp[0].string); ;
    break;}
case 17:
#line 95 "template.y"
{ g_oTemplate.AddMember(yyvsp[-1].string); ;
    break;}
case 18:
#line 96 "template.y"
{ g_oTemplate.AddMember(yyvsp[-2].string); ;
    break;}
case 19:
#line 98 "template.y"
{ g_oTemplate.AddClass ( yyvsp[-2].string ); ;
    break;}
case 20:
#line 103 "template.y"
{ g_oTemplate.Between (  yyvsp[0].string  ); ;
    break;}
case 21:
#line 104 "template.y"
{ g_oTemplate.Between ( "\n" ); ;
    break;}
case 22:
#line 105 "template.y"
{ g_oTemplate.Between (  yyvsp[0].string  ); ;
    break;}
case 23:
#line 109 "template.y"
{ g_oTemplate.ForEnd(); ;
    break;}
case 24:
#line 110 "template.y"
{ g_oTemplate.ForEnd(); ;
    break;}
case 25:
#line 111 "template.y"
{ g_oTemplate.GroupEnd(); ;
    break;}
case 26:
#line 112 "template.y"
{ g_oTemplate.GroupEnd(); ;
    break;}
case 27:
#line 113 "template.y"
{ g_oTemplate.BibEnd(); ;
    break;}
case 28:
#line 114 "template.y"
{ g_oTemplate.BibEnd(); ;
    break;}
case 29:
#line 115 "template.y"
{ g_oTemplate.ReduceEnd(); ;
    break;}
case 31:
#line 119 "template.y"
{;
    break;}
case 33:
#line 123 "template.y"
{ g_oTemplate.SetToken (yyvsp[0].number); ;
    break;}
case 34:
#line 125 "template.y"
{ g_oTemplate.SetSortOrder(yyvsp[0].string); ;
    break;}
case 35:
#line 127 "template.y"
{ g_oTemplate.BibBegin(); ;
    break;}
case 36:
#line 128 "template.y"
{ g_oTemplate.ForBegin(); ;
    break;}
case 37:
#line 129 "template.y"
{ g_oTemplate.GroupBegin(); ;
    break;}
case 38:
#line 130 "template.y"
{ g_oTemplate.ReduceBegin(); ;
    break;}
case 39:
#line 132 "template.y"
{ ;
    break;}
case 40:
#line 133 "template.y"
{  ;
    break;}
case 41:
#line 134 "template.y"
{  ;
    break;}
case 42:
#line 137 "template.y"
{;
    break;}
case 43:
#line 138 "template.y"
{;
    break;}
case 44:
#line 141 "template.y"
{ g_oTemplate.Exclusive(yyvsp[0].string); ;
    break;}
case 45:
#line 142 "template.y"
{ g_oTemplate.Exclusion(yyvsp[0].string); ;
    break;}
case 46:
#line 143 "template.y"
{ g_oTemplate.Inclusion(yyvsp[0].string); ;
    break;}
case 47:
#line 146 "template.y"
{ g_oTemplate.Condition(yyvsp[-1].string); g_oTemplate.ConditionFinished(); ;
    break;}
case 48:
#line 147 "template.y"
{ g_oTemplate.Condition(yyvsp[-2].string); ;
    break;}
case 49:
#line 148 "template.y"
{ g_oTemplate.ConditionFinished(); ;
    break;}
case 50:
#line 152 "template.y"
{ ;
    break;}
case 51:
#line 153 "template.y"
{ ;
    break;}
case 52:
#line 156 "template.y"
{ g_oTemplate.Constraint ( yyvsp[-1].string, yyvsp[0].string, true ) ;
    break;}
case 53:
#line 157 "template.y"
{ g_oTemplate.Constraint ( yyvsp[-1].string, yyvsp[0].string, false ); ;
    break;}
case 54:
#line 159 "template.y"
{ g_oTemplate.FinishValues() ;
    break;}
case 55:
#line 160 "template.y"
{  ;
    break;}
case 56:
#line 163 "template.y"
{ ;
    break;}
case 57:
#line 164 "template.y"
{ g_oTemplate.AddValue(str_tolower(yyvsp[0].string)); ;
    break;}
case 58:
#line 168 "template.y"
{ yyval.number = 0;;
    break;}
case 59:
#line 169 "template.y"
{ yyval.number = 1;;
    break;}
case 60:
#line 172 "template.y"
{ yyval.number = 1;;
    break;}
case 61:
#line 173 "template.y"
{ yyval.number = 1;;
    break;}
case 62:
#line 176 "template.y"
{ yyval.number=1;;
    break;}
case 63:
#line 177 "template.y"
{ yyval.number=1;;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 180 "template.y"
