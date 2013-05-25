
/*  A Bison parser, made from bib.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse bibparse
#define yylex biblex
#define yyerror biberror
#define yylval biblval
#define yychar bibchar
#define yydebug bibdebug
#define yynerrs bibnerrs
#define	ATSTRING	257
#define	ATCOMMENT	258
#define	ATINCLUDE	259
#define	ATPREAMBLE	260
#define	ENTRYTYPE	261
#define	LATEXCOMMAND	262
#define	KEY	263
#define	EQUALS	264
#define	COMMA	265
#define	COLON	266
#define	DOT	267
#define	OBRACE	268
#define	EBRACE	269
#define	OPAR	270
#define	EPAR	271
#define	NUMBER	272
#define	WORD	273
#define	WHITESPACE	274
#define	NEWLINE	275
#define	ANF	276
#define	COMMENT	277
#define	RAUTE	278
#define	TILDE	279
#define	PIPE	280
#define	PATH	281
#define	MATHMODE	282
#define	ACCENT	283
#define	EXCLAM	284
#define	QUEST	285
#define	TIME	286

#line 1 "bib.y"

/* process with:   bison -p bib -d  bib.y; mv bib.tab.c bib.tab.cxx */
/* Interesting bibtex yacc-grammar: 
   http://www.math.utah.edu/~beebe/software/bibparse/bibparse.html */
#include <map>
#include <iostream>
#include <string>

#include <ctype.h> 
//TODO wctype?

#include "bib.h"
//#include "bib.tab.h"

#define YYDEBUG 0 /* produce trace if (bibdebug!=0) */

extern int bibparse(void);
extern int biblex(void);


extern int nLine;

extern char *bibtext;

CBib& g_oBib = CBib::Instance();


int bibwrap()
    {
    return 1;
    }


void biberror(const char* str)
    {
    std::cerr << "Error in Line " << nLine << ": " << str << std::endl;
    std::cerr << "   (last symbol: \"" << bibtext << "\") " << std::endl;
    }



char* str_tolower ( char* str );





#line 53 "bib.y"
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



#define	YYFINAL		113
#define	YYFLAG		-32768
#define	YYNTBASE	33

#define YYTRANSLATE(x) ((unsigned)(x) <= 286 ? yytranslate[x] : 53)

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
    27,    28,    29,    30,    31,    32
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     6,     8,    12,    14,    20,    26,    34,    42,
    44,    50,    52,    53,    60,    62,    66,    68,    69,    75,
    80,    84,    88,    90,    96,   104,   112,   114,   118,   122,
   126,   130,   134,   138,   142,   146,   150,   154,   158,   162,
   166,   170,   172,   176,   177,   182,   183,   185,   187,   190,
   192
};

static const short yyrhs[] = {    50,
     0,    50,    34,    50,     0,    35,     0,    34,    50,    35,
     0,    23,     0,    38,    50,    14,    39,    15,     0,    38,
    50,    16,    39,    17,     0,    37,    50,    10,    50,    45,
    50,    15,     0,    36,    50,    14,    50,    45,    50,    15,
     0,     6,     0,     3,    50,    14,    50,    19,     0,     7,
     0,     0,    50,    19,    40,    50,    11,    41,     0,    42,
     0,    41,    11,    42,     0,    50,     0,     0,    50,    19,
    43,    50,    44,     0,    10,    50,    45,    50,     0,    22,
    46,    22,     0,    14,    47,    15,     0,    19,     0,    45,
    50,    24,    50,    19,     0,    45,    50,    24,    50,    22,
    46,    22,     0,    45,    50,    24,    50,    14,    47,    15,
     0,    50,     0,    46,    48,    50,     0,    46,    29,    50,
     0,    46,    28,    50,     0,    46,    19,    50,     0,    46,
    18,    50,     0,    46,    11,    50,     0,    46,    13,    50,
     0,    46,    16,    50,     0,    46,    17,    50,     0,    46,
    10,    50,     0,    46,    30,    50,     0,    46,    31,    50,
     0,    46,     8,    50,     0,    46,    27,    50,     0,    46,
     0,    47,    22,    46,     0,     0,    49,    14,    46,    15,
     0,     0,    51,     0,    52,     0,    51,    52,     0,    20,
     0,    21,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    69,    70,    73,    74,    77,    82,    86,    90,    94,   101,
   106,   111,   117,   117,   122,   123,   128,   129,   129,   131,
   134,   137,   140,   144,   148,   151,   157,   162,   166,   170,
   174,   178,   182,   186,   190,   194,   198,   202,   206,   210,
   214,   221,   224,   231,   231,   236,   237,   240,   241,   244,
   245
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","ATSTRING",
"ATCOMMENT","ATINCLUDE","ATPREAMBLE","ENTRYTYPE","LATEXCOMMAND","KEY","EQUALS",
"COMMA","COLON","DOT","OBRACE","EBRACE","OPAR","EPAR","NUMBER","WORD","WHITESPACE",
"NEWLINE","ANF","COMMENT","RAUTE","TILDE","PIPE","PATH","MATHMODE","ACCENT",
"EXCLAM","QUEST","TIME","bibfile","entry_list","entry","entrypreamb","entrystring",
"entrytype","entry_body","@1","inhalt","tagx","@2","tag","content","string_no_anf",
"string_with_anf","explizit","@3","optspace","space","single_space", NULL
};
#endif

static const short yyr1[] = {     0,
    33,    33,    34,    34,    35,    35,    35,    35,    35,    36,
    37,    38,    40,    39,    41,    41,    42,    43,    42,    44,
    45,    45,    45,    45,    45,    45,    46,    46,    46,    46,
    46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
    46,    47,    47,    49,    48,    50,    50,    51,    51,    52,
    52
};

static const short yyr2[] = {     0,
     1,     3,     1,     3,     1,     5,     5,     7,     7,     1,
     5,     1,     0,     6,     1,     3,     1,     0,     5,     4,
     3,     3,     1,     5,     7,     7,     1,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     1,     3,     0,     4,     0,     1,     1,     2,     1,
     1
};

static const short yydefact[] = {    46,
    50,    51,     1,    47,    48,    46,    10,    12,     5,    46,
     3,    46,    46,    46,    49,     0,     2,     0,     0,     0,
    46,     4,    46,    46,    46,    46,     0,     0,     0,     0,
     0,     0,    11,    46,    23,    46,    46,    46,     6,    13,
     7,    42,     0,    27,    44,     0,     0,    46,    46,    46,
    46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
    46,    46,     0,    22,    46,    21,     9,    46,     8,     0,
    40,    37,    33,    34,    35,    36,    32,    31,    41,    30,
    29,    38,    39,    28,    46,    43,     0,    46,    44,    46,
    24,    46,    14,    15,    17,    45,     0,    44,    46,    18,
    26,    25,    16,    46,     0,    46,    19,     0,    46,    20,
     0,     0,     0
};

static const short yydefgoto[] = {   111,
    10,    11,    12,    13,    14,    30,    48,    93,    94,   104,
   107,    37,    42,    43,    62,    63,    44,     4,     5
};

static const short yypact[] = {    11,
-32768,-32768,    13,    11,-32768,    11,-32768,-32768,-32768,    11,
-32768,    11,    11,    11,-32768,   -10,    13,    -5,    -3,   -11,
    11,-32768,    11,    11,    11,    11,    -1,     8,     8,    14,
     9,    24,-32768,    11,-32768,    11,    11,    11,-32768,-32768,
-32768,    65,    18,-32768,    97,   -13,    -7,    11,    11,    11,
    11,    11,    11,    11,    11,    11,    11,    11,    11,    11,
    11,    11,    21,-32768,    11,-32768,-32768,    11,-32768,    32,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,    11,    65,    20,    11,   121,    11,
-32768,    11,    34,-32768,    27,-32768,    48,   145,    11,-32768,
-32768,-32768,-32768,    11,    37,    11,-32768,     8,    11,    41,
    66,    67,-32768
};

static const short yypgoto[] = {-32768,
-32768,    52,-32768,-32768,-32768,    46,-32768,-32768,   -25,-32768,
-32768,   -28,   -21,    -4,-32768,-32768,     0,-32768,    73
};


#define	YYLAST		176


static const short yytable[] = {     3,
    38,    67,    25,    21,    26,    16,    24,    69,    23,    17,
    68,    18,    19,    20,    45,     6,    68,    33,     7,     8,
    27,    34,    28,    29,    31,    31,    35,    40,    39,    36,
     1,     2,    64,    90,    85,     9,    46,    47,    91,    65,
    41,    92,    88,    86,    99,   100,   106,    70,    71,    72,
    73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
    83,    84,   101,    89,    68,   112,   113,    87,    22,    65,
    98,    32,    49,   103,    50,    51,    15,    52,   -44,   109,
    53,    54,    55,    56,     0,    97,     0,    95,     0,     0,
     0,    57,    58,    59,    60,    61,     0,     0,    95,     0,
     0,     0,     0,   105,    49,   108,    50,    51,   110,    52,
     0,     0,    53,    54,    55,    56,     0,     0,    66,     0,
     0,     0,     0,    57,    58,    59,    60,    61,    49,     0,
    50,    51,     0,    52,     0,    96,    53,    54,    55,    56,
     0,     0,     0,     0,     0,     0,     0,    57,    58,    59,
    60,    61,    49,     0,    50,    51,     0,    52,     0,     0,
    53,    54,    55,    56,     0,     0,   102,     0,     0,     0,
     0,    57,    58,    59,    60,    61
};

static const short yycheck[] = {     0,
    29,    15,    14,    14,    16,     6,    10,    15,    14,    10,
    24,    12,    13,    14,    36,     3,    24,    19,     6,     7,
    21,    14,    23,    24,    25,    26,    19,    19,    15,    22,
    20,    21,    15,    14,    14,    23,    37,    38,    19,    22,
    17,    22,    11,    65,    11,    19,    10,    48,    49,    50,
    51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
    61,    62,    15,    85,    24,     0,     0,    68,    17,    22,
    92,    26,     8,    99,    10,    11,     4,    13,    14,   108,
    16,    17,    18,    19,    -1,    90,    -1,    88,    -1,    -1,
    -1,    27,    28,    29,    30,    31,    -1,    -1,    99,    -1,
    -1,    -1,    -1,   104,     8,   106,    10,    11,   109,    13,
    -1,    -1,    16,    17,    18,    19,    -1,    -1,    22,    -1,
    -1,    -1,    -1,    27,    28,    29,    30,    31,     8,    -1,
    10,    11,    -1,    13,    -1,    15,    16,    17,    18,    19,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    29,
    30,    31,     8,    -1,    10,    11,    -1,    13,    -1,    -1,
    16,    17,    18,    19,    -1,    -1,    22,    -1,    -1,    -1,
    -1,    27,    28,    29,    30,    31
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
#line 69 "bib.y"
{;
    break;}
case 2:
#line 70 "bib.y"
{;
    break;}
case 3:
#line 73 "bib.y"
{;
    break;}
case 4:
#line 74 "bib.y"
{;
    break;}
case 5:
#line 77 "bib.y"
{
#if defined(YYDEBUG) && (YYDEBUG != 0)
                    bibdebug=1; 
#endif
                ;
    break;}
case 6:
#line 83 "bib.y"
{
		  g_oBib.FinishObject ( yyvsp[-4].string, objects_atentry );
		;
    break;}
case 7:
#line 87 "bib.y"
{
		  g_oBib.FinishObject ( yyvsp[-4].string, objects_atentry );
		;
    break;}
case 8:
#line 91 "bib.y"
{
		  g_oBib.FinishObject ( "AtString", objects_atstring );
		;
    break;}
case 9:
#line 95 "bib.y"
{
		  g_oBib.FinishObject ( "AtPreamble", objects_atpreamble );
		;
    break;}
case 10:
#line 102 "bib.y"
{ 
	  g_oBib.CreateObject ( "AtPreamble", "Meta", objects_atpreamble );
	;
    break;}
case 11:
#line 107 "bib.y"
{ 
	  g_oBib.CreateObject ( yyvsp[0].string, "Meta", objects_atstring  );
	;
    break;}
case 12:
#line 112 "bib.y"
{
	  g_oBib.CreateObject ( yyvsp[0].string, "Entry", objects_atentry ); yyval.string=yyvsp[0].string; 
	;
    break;}
case 13:
#line 117 "bib.y"
{ g_oBib.SetKey ( yyvsp[0].string ); ;
    break;}
case 14:
#line 118 "bib.y"
{
	        ;
    break;}
case 15:
#line 122 "bib.y"
{;
    break;}
case 16:
#line 124 "bib.y"
{
	        ;
    break;}
case 17:
#line 128 "bib.y"
{;
    break;}
case 18:
#line 129 "bib.y"
{g_oBib.CreateObject ( str_tolower(yyvsp[0].string), "Tag", objects_tag );;
    break;}
case 19:
#line 129 "bib.y"
{ g_oBib.FinishObject ( yyvsp[-3].string, objects_tag );;
    break;}
case 20:
#line 131 "bib.y"
{ ;
    break;}
case 21:
#line 135 "bib.y"
{
		;
    break;}
case 22:
#line 138 "bib.y"
{
		;
    break;}
case 23:
#line 141 "bib.y"
{
		  g_oBib.AddAtom ( yyvsp[0].string, false, usersigns_abbrev );
		;
    break;}
case 24:
#line 145 "bib.y"
{
		  g_oBib.AddAtom ( yyvsp[0].string, false, usersigns_abbrev );
		;
    break;}
case 25:
#line 149 "bib.y"
{
		;
    break;}
case 26:
#line 152 "bib.y"
{
		;
    break;}
case 27:
#line 159 "bib.y"
{
		  g_oBib.SetPrefix((yyvsp[0].number?true:false)); 
		;
    break;}
case 28:
#line 163 "bib.y"
{
		  g_oBib.ExplizitFinish (  (yyvsp[0].number?true:false) );
		;
    break;}
case 29:
#line 167 "bib.y"
{
		  g_oBib.AddAtom ( yyvsp[-1].string, (yyvsp[0].number?true:false), usersigns_accent );
		;
    break;}
case 30:
#line 171 "bib.y"
{
		  g_oBib.AddAtom ( yyvsp[-1].string, (yyvsp[0].number?true:false), usersigns_mathmode );
		;
    break;}
case 31:
#line 175 "bib.y"
{
		  g_oBib.AddAtom ( yyvsp[-1].string, (yyvsp[0].number?true:false), usersigns_word);
		;
    break;}
case 32:
#line 179 "bib.y"
{
		  g_oBib.AddAtom ( yyvsp[-1].string, (yyvsp[0].number?true:false), usersigns_number );
		;
    break;}
case 33:
#line 183 "bib.y"
{
		  g_oBib.AddAtom ( ",", (yyvsp[0].number?true:false), usersigns_comma);
		;
    break;}
case 34:
#line 187 "bib.y"
{
		  g_oBib.AddAtom ( ".", (yyvsp[0].number?true:false), usersigns_dot );
		;
    break;}
case 35:
#line 191 "bib.y"
{
		  g_oBib.AddAtom ( "(", (yyvsp[0].number?true:false), usersigns_opar );
		;
    break;}
case 36:
#line 195 "bib.y"
{
		  g_oBib.AddAtom ( ")", (yyvsp[0].number?true:false), usersigns_epar );
		;
    break;}
case 37:
#line 199 "bib.y"
{
		  g_oBib.AddAtom ( "=", (yyvsp[0].number?true:false), usersigns_equal );
		;
    break;}
case 38:
#line 203 "bib.y"
{
		  g_oBib.AddAtom ( "!", (yyvsp[0].number?true:false), usersigns_exclam );
		;
    break;}
case 39:
#line 207 "bib.y"
{
		  g_oBib.AddAtom ( "?", (yyvsp[0].number?true:false), usersigns_quest );
		;
    break;}
case 40:
#line 211 "bib.y"
{
		  g_oBib.AddAtom ( yyvsp[-1].string, (yyvsp[0].number?true:false), usersigns_latex );
		;
    break;}
case 41:
#line 215 "bib.y"
{
		  g_oBib.AddAtom ( yyvsp[-1].string, (yyvsp[0].number?true:false), usersigns_path );
		;
    break;}
case 42:
#line 222 "bib.y"
{
		;
    break;}
case 43:
#line 225 "bib.y"
{
		    /* FixMe: at the moment just ignore ANF within a brace-limited-string */
		;
    break;}
case 44:
#line 231 "bib.y"
{ g_oBib.ExplizitIn(); ;
    break;}
case 45:
#line 232 "bib.y"
{
	  g_oBib.ExplizitOut();
	;
    break;}
case 46:
#line 236 "bib.y"
{ yyval.number = 0;;
    break;}
case 47:
#line 237 "bib.y"
{ yyval.number = 1;;
    break;}
case 48:
#line 240 "bib.y"
{ yyval.number = 1;;
    break;}
case 49:
#line 241 "bib.y"
{ yyval.number =1;;
    break;}
case 50:
#line 244 "bib.y"
{yyval.number=1;;
    break;}
case 51:
#line 245 "bib.y"
{yyval.number=1; ;
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
#line 249 "bib.y"
