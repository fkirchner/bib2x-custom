%{
#include <iostream>
#include "template.tab.h"
#include "template.h"
#include <string.h>

int nTemplateLine = 1;
bool bBib = false;
bool bMod = false;

#define DUPSTRING templatelval.string=strdup(templatetext)
#define DUPCHAR(c) templatelval.string=strdup(c)
#define DUPNUMBER(n) templatelval.number = n

%}
%option noyywrap

/*
[\n]                        return NEWLINE;
[a-zA-Z][a-zA-Z0-9:.+/'\-]*  biblval.string=strdup(bibtext); return WORD;



*/
W [ \r\f\t]
L {W}*
A [a-zA-Z]
NR {W}+[0-9]+{W}+
XNR [x0-9][0-9]*
STEP [sS][tT][eE][pP][:]
MOD [mM][oO][dD][_]
ANYC \%\%[^%]+\%\%
RNG {XNR}\-{XNR}
Q ["] 
/*"*/

%x DEFINITION HEAD FOR BIB VALUES VALUE BIBVALUES BIBVALUE BIBTOKEN BIBCONTENT CLASS MEMBERS MOD MODBIB STEP STEPCONTENT
%%

<INITIAL>[\\]                           { DUPCHAR("\\"); return TOKEN_ALMOSTANY; }
<INITIAL>[\\][\%]                       { DUPCHAR("%"); return TOKEN_ALMOSTANY; }

<INITIAL>\%\%[fF][oO][rR]\%\%           { BEGIN FOR; DUPSTRING; return TOKEN_FOR; }
<INITIAL>\%\%[rR][oO][fF]\%\%           { DUPSTRING; return TOKEN_ROF; }

<INITIAL>\%\%[gG][rR][pP]\%\%           { BEGIN FOR; DUPSTRING; return TOKEN_GRP; }
<INITIAL>\%\%[pP][rR][gG]\%\%           { DUPSTRING; return TOKEN_PRG; }


<INITIAL>\%\%[bB][iI][bB]\%\%           { BEGIN BIB; DUPSTRING; return TOKEN_BIB; }
<BIBTOKEN>\%\%[bB][iI][bB]\%\%          { BEGIN INITIAL; DUPSTRING; return TOKEN_BIB; }

<INITIAL>\%\%[rR][eE][dD]\%\%			{ BEGIN FOR; return TOKEN_RED; }


<INITIAL>\%\%[dD][eE][fF]\%\%{NR}{Q}    { BEGIN DEFINITION; DUPSTRING; return TOKEN_DEF; }
<DEFINITION>[\n]                        { ++nTemplateLine; DUPCHAR("\n"); return TOKEN_DEFINITION; }
<DEFINITION>[\\]{Q}                     { DUPCHAR("\""); return TOKEN_DEFINITION; }
<DEFINITION>[\\]                        { DUPCHAR("\\"); return TOKEN_DEFINITION; }
<DEFINITION>[\\][\\]                    { DUPCHAR("\\"); return TOKEN_DEFINITION; }
<DEFINITION>[^"\n\\]+                   { /*"*/ DUPSTRING; return TOKEN_DEFINITION; }
<DEFINITION>{Q}{W}*[\n]                 { ++nTemplateLine; BEGIN INITIAL; return TOKEN_FED; }

<INITIAL>\%\%[cC][lL][sS]\%\%{W}+       { BEGIN CLASS; return TOKEN_CLASS; }
<CLASS>{W}*[=]                          { return TOKEN_EQUALS; }
<CLASS>{W}*[{]{W}*                      { BEGIN MEMBERS; return TOKEN_LBRACE; }
<MEMBERS>{W}*[,]{W}*                    { return TOKEN_COMMA; }
<MEMBERS>[}]{W}*[\n]                    { ++nTemplateLine; BEGIN INITIAL; return TOKEN_CLASS; }


<FOR,BIB>[iI][nN][cC]                   { DUPSTRING; return TOKEN_SORT; }
<FOR,BIB>[dD][eE][cC]                   { DUPSTRING; return TOKEN_SORT; }

<FOR,BIB,CLASS,MEMBERS>[a-zA-Z@]{A}*    { DUPSTRING; return TOKEN_WORD; }
<FOR,BIB>[a-zA-Z@]{A}*[:]{XNR}          { DUPSTRING; return TOKEN_WORDX; }

<FOR,BIB,MOD,MODBIB,STEP>{W}*[(]{W}*    { return TOKEN_LPAR; }
<FOR,MOD>{W}*[)]                        { BEGIN INITIAL; return TOKEN_RPAR; }
<MODBIB>{W}*[)]                         { bMod = false; BEGIN BIBCONTENT; return TOKEN_RPAR; }
<STEP>{W}*[)]                           { if ( bMod ) { BEGIN MODBIB; } else { BEGIN BIBCONTENT;} return TOKEN_RPAR; }
<BIB>{W}*[)]                            { BEGIN BIBTOKEN; return TOKEN_RPAR; }
<BIB>[{]{W}*                            { BEGIN BIBVALUES; return TOKEN_LBRACE;  }
<FOR>[{]{W}*                            { BEGIN VALUES; return TOKEN_LBRACE; }
<FOR,BIB>{W}*[:]{W}*                    { return TOKEN_COLON; }
<FOR,BIB>{W}*[;]{W}*                    { return TOKEN_SEMICOLON; }
<FOR,BIB>{W}*[,]{W}*                    { return TOKEN_COMMA; }

<VALUES>{W}*[}][;]                      { BEGIN FOR; return TOKEN_RBRACE; }
<BIBVALUES>{W}*[}][;]                   { BEGIN BIB; return TOKEN_RBRACE; }
<VALUES,BIBVALUES>{W}*[,]{W}*           { return TOKEN_COMMA; }
<VALUES>{Q}                             { BEGIN VALUE; }
<VALUES>{Q}{Q}                          { DUPCHAR("\0"); return TOKEN_VALUE; }
<BIBVALUES>{Q}                          { BEGIN BIBVALUE; }
<BIBVALUES>{Q}{Q}                       { DUPCHAR("\0"); return TOKEN_VALUE; }
<VALUE,BIBVALUE>[\\]{Q}                 { DUPCHAR("\""); return TOKEN_VALUE; }
<VALUE,BIBVALUE>[\\]                    { DUPCHAR("\\"); return TOKEN_VALUE; }
<VALUE,BIBVALUE>[\\][\\]                { DUPCHAR("\\"); return TOKEN_VALUE; }
<VALUE,BIBVALUE>[\n]                    { ++nTemplateLine; DUPCHAR("\n"); return TOKEN_VALUE; }
<VALUE,BIBVALUE>[^"\n\\]+               { /*"*/ DUPSTRING; return TOKEN_VALUE; }
<VALUE>{Q}                              { BEGIN VALUES; }
<BIBVALUE>{Q}                           { BEGIN BIBVALUES;  }

<BIBTOKEN>[G]{W}*[=]{W}*{Q}             { BEGIN BIBCONTENT; DUPNUMBER(bibtoken_generic);  return TOKEN_BIBTOKEN; }
<BIBTOKEN>[M]{W}*[=]{W}*{Q}             { BEGIN BIBCONTENT; DUPNUMBER(bibtoken_missing);  return TOKEN_BIBTOKEN; }
<BIBTOKEN>[N]{W}*[=]{W}*{Q}             { BEGIN BIBCONTENT; DUPNUMBER(bibtoken_nonempty); return TOKEN_BIBTOKEN; }
<BIBTOKEN>[E]{W}*[=]{W}*{Q}             { BEGIN BIBCONTENT; DUPNUMBER(bibtoken_empty);    return TOKEN_BIBTOKEN; }
<BIBCONTENT>{Q}                         { BEGIN BIBTOKEN; return TOKEN_BIBTOKENFINISHED; }

<FOR,BIB>{W}*[!][=]{W}*                 { DUPSTRING; return TOKEN_OPERATOR; }
<FOR,BIB>{W}*[<]{W}*                    { DUPSTRING; return TOKEN_OPERATOR; }
<FOR,BIB>{W}*[=]{W}*                    { DUPSTRING; return TOKEN_OPERATOR; }
<FOR,BIB>{W}*[>]{W}*                    { DUPSTRING; return TOKEN_OPERATOR; }
<BIB>{W}*[!]                            { DUPSTRING; return TOKEN_EXCLAM;  }
<BIB>{W}*[#]                            { DUPSTRING; return TOKEN_HASH;  }


<INITIAL,BIBTOKEN>{W}+                  { DUPNUMBER(strlen(templatetext)); DUPSTRING; return TOKEN_WHITESPACE; }
<INITIAL,BIBTOKEN>[\n]                  { ++nTemplateLine; return TOKEN_NEWLINE; }
<INITIAL>[^%\n\\]+                      { DUPSTRING; return TOKEN_ALMOSTANY; }
<BIBCONTENT>[^%\\"]+                    { /*"*/ DUPSTRING; return TOKEN_ALMOSTANY; }
<BIBCONTENT>[\\]{Q}                     { DUPCHAR("\""); return TOKEN_ALMOSTANY; }
<BIBCONTENT>[\\]                        { DUPCHAR("\\"); return TOKEN_ALMOSTANY; }
<BIBCONTENT>[\\][\\]                    { DUPCHAR("\\"); return TOKEN_ALMOSTANY; }


<INITIAL>\%\%{MOD}{A}{A}\%\%	        { BEGIN MOD; DUPSTRING; return TOKEN_MOD; }
<BIBCONTENT>\%\%{MOD}{A}{A}\%\%	        { bMod = true; BEGIN MODBIB; DUPSTRING; return TOKEN_MOD; }
<BIBCONTENT,MODBIB>\%\%{STEP}{RNG}\%\%  { BEGIN STEP; DUPSTRING; return TOKEN_STEP; }
<STEP>{W}*[;]{W}*                       { return TOKEN_SEMICOLON; }
<STEP>{Q}								{ BEGIN STEPCONTENT; }
<STEP>{Q}{Q}							{ return TOKEN_STEPCONTENT; }
<STEPCONTENT>[\\]{Q}                    { DUPCHAR("\""); return TOKEN_STEPCONTENT; }
<STEPCONTENT>[\\]                       { DUPCHAR("\\"); return TOKEN_STEPCONTENT; }
<STEPCONTENT>[\\][\\]                   { DUPCHAR("\\"); return TOKEN_STEPCONTENT; }
<STEPCONTENT>[^\\"]+					{ /*"*/ DUPSTRING; return TOKEN_STEPCONTENT; }
<STEPCONTENT>{Q}						{ BEGIN STEP; }
<INITIAL,BIBCONTENT,MOD,MODBIB>{ANYC}   { DUPSTRING; return TOKEN_COMMAND; }



