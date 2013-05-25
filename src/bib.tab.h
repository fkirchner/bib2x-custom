typedef union
{
    int number;
    char* string;
} YYSTYPE;
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


extern YYSTYPE biblval;
