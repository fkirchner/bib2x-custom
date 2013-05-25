%{
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




%}

%token ATSTRING ATCOMMENT ATINCLUDE ATPREAMBLE
%token ENTRYTYPE LATEXCOMMAND KEY EQUALS COMMA COLON DOT OBRACE EBRACE OPAR EPAR NUMBER WORD 
%token WHITESPACE NEWLINE ANF COMMENT RAUTE TILDE PIPE PATH MATHMODE ACCENT EXCLAM QUEST

%union
{
    int number;
    char* string;
}


%token <string> LATEXCOMMAND NUMBER WORD KEY ENTRYTYPE TIME PATH ACCENT MATHMODE
%token <number> WHITESPACE NEWLINE

%type <number> optspace single_space space
%type <string> tag inhalt string_no_anf string_with_anf explizit entrytype
%% 



bibfile: optspace {}
        | optspace entry_list optspace {}
        ;

entry_list: entry {}
	| entry_list optspace entry {}
	;

entry:  COMMENT {
#if defined(YYDEBUG) && (YYDEBUG != 0)
                    bibdebug=1; 
#endif
                }
	| entrytype optspace OBRACE entry_body EBRACE
		{
		  g_oBib.FinishObject ( $1, objects_atentry );
		}
	| entrytype optspace OPAR entry_body EPAR
		{
		  g_oBib.FinishObject ( $1, objects_atentry );
		}
	| entrystring optspace EQUALS optspace content optspace EBRACE
		{
		  g_oBib.FinishObject ( "AtString", objects_atstring );
		}
	| entrypreamb optspace OBRACE optspace content optspace EBRACE
		{
		  g_oBib.FinishObject ( "AtPreamble", objects_atpreamble );
		}
	;
	
	
entrypreamb: ATPREAMBLE 
	{ 
	  g_oBib.CreateObject ( "AtPreamble", "Meta", objects_atpreamble );
	}; 

entrystring: ATSTRING optspace OBRACE optspace WORD 
	{ 
	  g_oBib.CreateObject ( $5, "Meta", objects_atstring  );
	};

entrytype: ENTRYTYPE 
	{
	  g_oBib.CreateObject ( $1, "Entry", objects_atentry ); $$=$1; 
	};


entry_body: optspace WORD { g_oBib.SetKey ( $2 ); } optspace COMMA inhalt
	        {
	        }
	;

inhalt: tagx {}
	| inhalt COMMA tagx
                {
	        }
	;

tagx:   optspace {}
	| optspace WORD {g_oBib.CreateObject ( str_tolower($2), "Tag", objects_tag );} optspace tag { g_oBib.FinishObject ( $2, objects_tag );}

tag:    EQUALS optspace content optspace  { };


content: ANF string_no_anf ANF
		{
		}
	| OBRACE string_with_anf EBRACE
		{
		}
	| WORD
		{
		  g_oBib.AddAtom ( $1, false, usersigns_abbrev );
		}
	| content optspace RAUTE optspace WORD
		{
		  g_oBib.AddAtom ( $5, false, usersigns_abbrev );
		}
	| content optspace RAUTE optspace ANF string_no_anf ANF
		{
		}
	| content optspace RAUTE optspace OBRACE string_with_anf EBRACE
		{
		}
	;


string_no_anf: 
        optspace
                {
		  g_oBib.SetPrefix(($1?true:false)); 
		}
        | string_no_anf explizit optspace
		{
		  g_oBib.ExplizitFinish (  ($3?true:false) );
		}
	| string_no_anf ACCENT optspace
		{
		  g_oBib.AddAtom ( $2, ($3?true:false), usersigns_accent );
		}
	| string_no_anf MATHMODE optspace
		{
		  g_oBib.AddAtom ( $2, ($3?true:false), usersigns_mathmode );
		}
	| string_no_anf WORD optspace
		{
		  g_oBib.AddAtom ( $2, ($3?true:false), usersigns_word);
		}
	| string_no_anf NUMBER optspace
		{
		  g_oBib.AddAtom ( $2, ($3?true:false), usersigns_number );
		}
	| string_no_anf COMMA optspace
		{
		  g_oBib.AddAtom ( ",", ($3?true:false), usersigns_comma);
		}
	| string_no_anf DOT optspace
		{
		  g_oBib.AddAtom ( ".", ($3?true:false), usersigns_dot );
		}
	| string_no_anf OPAR optspace
		{
		  g_oBib.AddAtom ( "(", ($3?true:false), usersigns_opar );
		}
	| string_no_anf EPAR optspace
		{
		  g_oBib.AddAtom ( ")", ($3?true:false), usersigns_epar );
		}
	| string_no_anf EQUALS optspace
		{
		  g_oBib.AddAtom ( "=", ($3?true:false), usersigns_equal );
		}
	| string_no_anf EXCLAM optspace
		{
		  g_oBib.AddAtom ( "!", ($3?true:false), usersigns_exclam );
		}
	| string_no_anf QUEST optspace
		{
		  g_oBib.AddAtom ( "?", ($3?true:false), usersigns_quest );
		}
	| string_no_anf LATEXCOMMAND optspace
		{
		  g_oBib.AddAtom ( $2, ($3?true:false), usersigns_latex );
		}
	| string_no_anf PATH optspace
		{
		  g_oBib.AddAtom ( $2, ($3?true:false), usersigns_path );
		}
	;


string_with_anf: string_no_anf
		{
		}
	| string_with_anf ANF string_no_anf
		{
		    /* FixMe: at the moment just ignore ANF within a brace-limited-string */
		}
	;


explizit: { g_oBib.ExplizitIn(); } OBRACE string_no_anf EBRACE
	{
	  g_oBib.ExplizitOut();
	}

optspace: { $$ = 0;}
	| space { $$ = 1;}
	;

space: single_space { $$ = 1;}
	| space single_space { $$ =1;}
	;

single_space: WHITESPACE {$$=1;}
	| NEWLINE {$$=1; }
	;


