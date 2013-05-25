%{
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "bib.tab.h"

//#define DEBUG
#ifdef DEBUG
#define LDEBUG(m) fprintf(stderr," [%s,line %d]=\"\%s\" ",m,nLine,bibtext)
#else
#define LDEBUG(m)
#endif

int nLine = 1;



int checkNewlines ( std::string sTemp )
	{
	int nTemp = 0;
	std::string::iterator sIt = sTemp.begin();
	std::string::iterator sItEnd = sTemp.end();

	for ( ; sIt != sItEnd; ++sIt )
		++nTemp;
	return nTemp;
	}


char* str_tolower ( char* str );

%}
%option noyywrap

/*
[\n]                         return NEWLINE;
[a-zA-Z][a-zA-Z0-9:.+/'\-]*  biblval.string=strdup(bibtext); return WORD;
*/

IW [^\\\" 	\n\r\f\t,\(\)\{\}$=!?]
IWW [^\\\"\n,=\{\}#$]
IAW [^\"#~$]
W [ \r\f\t]
L {W}*



%%
\\[uU][rR][lL][{]{IWW}+[}]     { LDEBUG("PATH"); std::string sTemp = bibtext; sTemp.erase(0,5); sTemp.erase(sTemp.length()-1,1); biblval.string=strdup(sTemp.c_str()); return PATH; }
\\[pP][aA][tT][hH][|]{IWW}+[|]     { LDEBUG("PATH"); std::string sTemp = bibtext; sTemp.erase(0,6); sTemp.erase(sTemp.length()-1,1); biblval.string=strdup(sTemp.c_str()); return PATH; }
\\[pP][aA][tT][hH][=]{IWW}+[=]     { LDEBUG("PATH"); std::string sTemp = bibtext; sTemp.erase(0,6); sTemp.erase(sTemp.length()-1,1); biblval.string=strdup(sTemp.c_str()); return PATH; }


@[sS][tT][rR][iI][nN][gG]          LDEBUG("ATSTRING"); return ATSTRING;
@[cC][oO][mM][mM][eE][nN][tT]      LDEBUG("ATCOMMENT"); return ATCOMMENT;
@[pP][rR][eE][aA][mM][bB][lL][eE]  LDEBUG("ATPREAMBLE"); return ATPREAMBLE;
@[iI][nN][cC][lL][uU][dD][eE]      LDEBUG("ATINCLUDE"); return ATINCLUDE;

@[^\\\"	 \n\(\),=\{\}#~]+          LDEBUG("ENTRYTYPE"); biblval.string=str_tolower(strdup(bibtext)); return ENTRYTYPE;


\{\"\}                             LDEBUG("WORD1"); biblval.string=strdup("\\\""); return WORD;
\![`]                              LDEBUG("ACCENT1"); biblval.string=strdup("!"); return ACCENT;
\?[`]                              LDEBUG("ACCENT2"); biblval.string=strdup("?"); return ACCENT;
\{\\[oO]\}                         LDEBUG("ACCENT3"); biblval.string=strdup(bibtext); return ACCENT;
\{\\[oOaAsS][eEaAsS]\}             LDEBUG("ACCENT4"); biblval.string=strdup(bibtext); return ACCENT;
\{\\[\"'`\^~=\.].\}                LDEBUG("ACCENT5"); biblval.string=strdup(bibtext); return ACCENT;
\{\\[\"'`\^~=\.bcdHrtuv]\\.\}      LDEBUG("ACCENT6"); biblval.string=strdup(bibtext); return ACCENT;
\\[\"'`\^~=\.bcdHrtuv]\{\\.\}      LDEBUG("ACCENT7"); biblval.string=strdup(bibtext); return ACCENT;
\\[\"'`\^~=\.bcdHrtuv]\{[^\}]\}    LDEBUG("ACCENT8"); biblval.string=strdup(bibtext); return ACCENT;
\\[\"'`\^~=\.][^\{]                LDEBUG("ACCENT9"); biblval.string=strdup(bibtext); return ACCENT;
\\[\"'`\^~=\.][\\][a-zA-Z]         LDEBUG("ACCENT10"); biblval.string=strdup(bibtext); return ACCENT;
\\\"                               LDEBUG("ACCENT11"); biblval.string=strdup(bibtext); return ACCENT;
\\\\                               LDEBUG("WORD2"); biblval.string=strdup("\\\\"); return WORD; 
[$]{IAW}+[$]                       { LDEBUG("MATHMODE"); std::string sTemp = bibtext; if ( sTemp.length()>2) { sTemp.erase(0,1); sTemp.erase(sTemp.length()-1,1);} biblval.string=strdup(sTemp.c_str()); nLine += checkNewlines(sTemp); return MATHMODE;  }
\\[-$/&%#\{\}_]                    LDEBUG("LATEXCOMMAND"); biblval.string=strdup(bibtext); return LATEXCOMMAND;

["]                                LDEBUG("ANF"); return ANF;
~                                  LDEBUG("TILDE"); return TILDE;
[{]                                LDEBUG("OBRACE"); return OBRACE;
[}]                                LDEBUG("EBRACE"); return EBRACE;
[(]                                LDEBUG("OPAR"); return OPAR;
[)]                                LDEBUG("EPAR"); return EPAR;
[=]                                LDEBUG("EQUALS"); return EQUALS;
[,]                                LDEBUG("COMMA"); return COMMA;
[!]                                LDEBUG("EXCLAM"); return EXCLAM;
[?]                                LDEBUG("QUEST"); return QUEST;
[#]                                LDEBUG("RAUTE"); return RAUTE;

[\\][a-zA-Z][a-zA-Z]*              LDEBUG("LATEXCOMMAND"); biblval.string=strdup(bibtext); return LATEXCOMMAND;
[\\]                               LDEBUG("WORD3"); biblval.string=strdup("\\"); return WORD;
{IW}+                              LDEBUG("WORD4"); biblval.string=strdup(bibtext); return WORD;

[\n]                               LDEBUG("NEWLINE"); biblval.number = 1; ++nLine; return NEWLINE;

{W}+                               biblval.number = 1; return WHITESPACE;

^{W}*[%].*[\n]{L}                  LDEBUG("COMMENT"); ++nLine; return COMMENT;
.                                  LDEBUG("Unknown Char");
%%

/* This is rule has been removed to accept '%' within 'annote' fields. Fixme: comments are currently not supported
   after some other content within the same line.
[^!?,\(\)\{\}$=\\\"\n][%].*[\n]{L} LDEBUG("COMMENT2"); ++nLine; return COMMENT; // Raimund: added \n; this rule still is buggy, because it maches '%' in <content> even if it isn't a comment
*/
