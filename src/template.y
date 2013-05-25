%{
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


%}

%union
{
    int number;
    char* string;
}

%token TOKEN_SORT TOKEN_FOR TOKEN_ROF TOKEN_LPAR TOKEN_RPAR TOKEN_WORD 
%token TOKEN_COMMA TOKEN_BIB TOKEN_DEF TOKEN_FED TOKEN_HASH TOKEN_STEP
%token TOKEN_OPERATOR TOKEN_WHITESPACE TOKEN_SEMICOLON TOKEN_ALMOSTANY
%token TOKEN_COMMAND TOKEN_COLON TOKEN_RBRACE TOKEN_VALUE TOKEN_LBRACE
%token TOKEN_NEWLINE TOKEN_PRG TOKEN_GRP TOKEN_EXCLAM TOKEN_DEFINITION
%token TOKEN_BIBTOKENFINISHED TOKEN_STEPCONTENT TOKEN_MOD TOKEN_EQUALS
%token TOKEN_BIBTOKEN TOKEN_WORDX TOKEN_CLASS TOKEN_RED

%token <string> TOKEN_ALMOSTANY TOKEN_VALUE TOKEN_OPERATOR TOKEN_WORDX
%token <string> TOKEN_WHITESPACE TOKEN_NUMBER TOKEN_COMMAND TOKEN_SORT
%token <string> TOKEN_STEPCONTENT TOKEN_DEF TOKEN_MOD TOKEN_DEFINITION
%token <string> TOKEN_WORD TOKEN_STEP


%token <number> TOKEN_BIBTOKEN

%type <number> optspace single_space space
%type <string> value stepcontent
%% 

mybegin: entries {}


entries: {}
	| entries entry { }
    ;

entry: between { }
	| define {}
	| loop { }
	| TOKEN_COMMAND	{ g_oTemplate.Command($1); }
	| TOKEN_MOD TOKEN_LPAR TOKEN_COMMAND TOKEN_RPAR { g_oTemplate.Modifier($1, $3); }
	| TOKEN_STEP TOKEN_LPAR stepcontent TOKEN_SEMICOLON stepcontent TOKEN_SEMICOLON stepcontent TOKEN_RPAR { g_oTemplate.Step($1,$3,$5,$7); }
	| TOKEN_MOD TOKEN_LPAR TOKEN_STEP TOKEN_LPAR stepcontent TOKEN_SEMICOLON stepcontent TOKEN_SEMICOLON stepcontent TOKEN_RPAR TOKEN_RPAR { g_oTemplate.Step($3,$5,$7,$9,$1); }
	;

stepcontent: TOKEN_STEPCONTENT { $$=strdup($1); }
	| stepcontent TOKEN_STEPCONTENT { std::string sA; sA += $1; sA += $2; $$=strdup(sA.c_str());}

/*
defines: anfang {}
	| defines define {}
	;

anfang: {}
	| anfang between {}
*/

define: TOKEN_DEF definition TOKEN_FED { g_oTemplate.DefFinish( $1 ); }
	 | TOKEN_CLASS classtarget members {  };

definition: 
	| definition TOKEN_DEFINITION { g_oTemplate.AddDefinition($2); }
	;

members: TOKEN_WORD TOKEN_CLASS { g_oTemplate.AddMember($1); }
	| TOKEN_WORD TOKEN_COMMA members { g_oTemplate.AddMember($1); }

classtarget: TOKEN_WORD TOKEN_EQUALS TOKEN_LBRACE { g_oTemplate.AddClass ( $1 ); }



between: 
	 TOKEN_ALMOSTANY	{ g_oTemplate.Between (  $1  ); }
	| TOKEN_NEWLINE		{ g_oTemplate.Between ( "\n" ); }
	| TOKEN_WHITESPACE	{ g_oTemplate.Between (  $1  ); }
	;


loop: myfor TOKEN_LPAR tok_sort TOKEN_COLON conditions entries TOKEN_ROF { g_oTemplate.ForEnd(); }
	| myfor TOKEN_LPAR conditions entries TOKEN_ROF { g_oTemplate.ForEnd(); }
	| mygrp TOKEN_LPAR tok_sort TOKEN_COLON conditions entries TOKEN_PRG { g_oTemplate.GroupEnd(); }
	| mygrp TOKEN_LPAR conditions entries TOKEN_PRG { g_oTemplate.GroupEnd(); }
	| mybib TOKEN_LPAR tok_sort TOKEN_COLON exconditions tokenentries optspace TOKEN_BIB { g_oTemplate.BibEnd(); }
	| mybib TOKEN_LPAR exconditions tokenentries optspace TOKEN_BIB { g_oTemplate.BibEnd(); }
	| myred TOKEN_LPAR tok_sort TOKEN_COLON conditions { g_oTemplate.ReduceEnd(); }
	;

tokenentries: 
	| tokenentries optspace token {}

token: mybibtoken entries TOKEN_BIBTOKENFINISHED

mybibtoken: TOKEN_BIBTOKEN { g_oTemplate.SetToken ($1); }

tok_sort:  TOKEN_SORT  { g_oTemplate.SetSortOrder($1); };

mybib: TOKEN_BIB { g_oTemplate.BibBegin(); };
myfor: TOKEN_FOR { g_oTemplate.ForBegin(); };
mygrp: TOKEN_GRP { g_oTemplate.GroupBegin(); };
myred: TOKEN_RED { g_oTemplate.ReduceBegin(); };

exconditions: incexclusions TOKEN_RPAR { }
	| incexclusions constraints {  }
	| constraints {  }
	;

incexclusions: incexclusion TOKEN_SEMICOLON {}
	| incexclusion TOKEN_COMMA incexclusions {}

incexclusion: 
	TOKEN_HASH TOKEN_WORD { g_oTemplate.Exclusive($2); }
	| TOKEN_EXCLAM TOKEN_WORD { g_oTemplate.Exclusion($2); }
	| TOKEN_WORD { g_oTemplate.Inclusion($1); }


conditions: TOKEN_WORD TOKEN_RPAR { g_oTemplate.Condition($1); g_oTemplate.ConditionFinished(); }
	| TOKEN_WORD TOKEN_SEMICOLON constraints { g_oTemplate.Condition($1); }
	| constraints { g_oTemplate.ConditionFinished(); }
	;


constraints: target TOKEN_LBRACE values TOKEN_RPAR { }
	| target TOKEN_LBRACE values constraints { }
	;

target: TOKEN_WORDX TOKEN_OPERATOR { g_oTemplate.Constraint ( $1, $2, true ) };
	| TOKEN_WORD TOKEN_OPERATOR { g_oTemplate.Constraint ( $1, $2, false ); };

values: value TOKEN_RBRACE { g_oTemplate.FinishValues() }
	| value TOKEN_COMMA values {  }
	;

value: { }
	| value TOKEN_VALUE { g_oTemplate.AddValue(str_tolower($2)); }
	;


optspace: { $$ = 0;}
	| space { $$ = 1;}
	;

space: single_space { $$ = 1;}
	| space single_space { $$ = 1;}
	;

single_space: TOKEN_WHITESPACE { $$=1;}
	| TOKEN_NEWLINE { $$=1;}
	;

