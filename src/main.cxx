#include <iostream>
#include <string>
#include <strings.h>
#include <stdio.h>

#include "bib.h"

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif


#include <unistd.h>
#include <ctype.h>

#include "generic.h"
#include "odb.h"

#include "output.h"
#include "outputhtml.h"
#include "outputodb.h"

#include "template.h"


static int g_nVersionMajor = 0;
static int g_nVersionMinor = 9;
static std::string g_sToolName  = "Bib2x";
static std::string g_sAuthor    = "Alexander Feder";
static std::string g_sYear      = "2005";

//namespace bibparser{
	extern int bibparse(void);
	extern FILE* bibin;
	extern void bibrestart ( FILE* );
//};




char* str_tolower ( char* str )
	{ 
	if ( !str ) return 0;
	for ( int i = 0; str[i] != '\0'; ++i )
		str[i] = (char)tolower((int)str[i]);
	return str;
	}



void print_help ( void )
	{
	char* str = "Bib2x (c) 2005 Alexander Feder\n\n"
				"Usage: \n"
				"       -o output               output to specified format (DEPRECATED!)\n"
				"       -f filename             read input from specified file\n"
				"       -h                      this help\n"
				"       -t filename             use template to output\n"
				"       -r CONSTRAINTS          reduce answer set by constraints\n"
				"       -V                      print version and exit\n"
				"       -v                      verbose\n";
	std::cerr << str << std::endl;
	}

int main ( int argc, char **argv )
	{
	bool bOutput	= false;
	bool bTemplate	= false;
	bool bFile		= false;
	
	bool bGetConstraints = false;

	std::string sOutput;
	std::string sTemplate;
	std::string sFile;
	std::string sConstraints;

	int nVerbose = 0;
	char c;

	 opterr = 0;

	while ((c = getopt (argc, argv, "ho:vVf:t:r:")) != -1)
		{
		switch (c)
			{
			case 'h':
				print_help();
				return 1;

			case 'f':
				if ( bFile ) 
					{
					std::cerr << "At the moment, only from one file can be read!" << std::endl;
					return 1;
					}
				bFile = true;
				sFile = optarg;
				std::cerr << "Using file " << sFile << " for input!" << std::endl;
				break;
			
			case 'o':
				if ( bOutput ) 
					{
					std::cerr << "Only one output at a time may be chosen!" << std::endl;
					return 1;
					}
				bOutput = true;
				sOutput = str_tolower(optarg);
				break;

			case 't':
				if ( bTemplate ) 
					{
					std::cerr << "Only one template at a time may be chosen!" << std::endl;
					}
				bTemplate = true;
				sTemplate = optarg;
				break;

			case 'r':
//				std::cerr << "Getting constraints by stdin" << std::endl;
//				bGetConstraints = true;
				sConstraints = optarg;
				break;

			case 'v':
				++nVerbose;
				break;
			
			case 'V':
				std::cout << g_sToolName << " v" << g_nVersionMajor << "." 
                                                 << g_nVersionMinor << std::endl;
                std::cout << "(c) " << g_sYear << " by " << g_sAuthor << std::endl;
                
                return 0;
			case '?':
				std::cerr << "unknown parameter " /*<< optopt*/<< "!" << std::endl;
				print_help();

				return 1;
			
			default:
				abort ();
			}
		}


	CBib& roBib = CBib::Instance();
/*
	if ( bGetConstraints )
		{
		if ( !bFile )
			{
			std::cerr << "When constraints shall be applied, file needs to be specified as file." << std::endl;
			return 1;
			}
		getline(std::cin,sConstraints);
		}
*/

	if ( bOutput && bTemplate ) 
		{
		std::cerr << "Cannot use template at the same time with built-in output" << std::endl;
		return 1;
		}


	COutput* poOutput = 0;
	if ( bOutput )
		{
		if ( sOutput == "html" )  poOutput = (COutput*) new COutputHtml ( roBib.GetODB() );
		if ( sOutput == "plain" ) poOutput = (COutput*) new COutput ( roBib.GetODB() );
		if ( sOutput == "odb" )   poOutput = (COutput*) new COutputOdb ( roBib.GetODB() );
		}


	FILE* pfIn = stdin;

	if ( bFile )
		{
		pfIn = fopen ( sFile.c_str(), "r" );
		if ( !pfIn )
			{
			std::cerr << "cannot open file " << sFile << "!" << std::endl;
			perror ( "blah" );
			return 1;
			}
		}

	bibin = pfIn;




	FILE* pfTemplate = 0;
	if ( bTemplate )
		{
		pfTemplate = fopen ( sTemplate.c_str(), "r" );
		if ( !pfTemplate )
			{
			std::cerr << "cannot open file " << sTemplate << "!" << std::endl;
			perror ( "blah" );
			return 1;
			}
		}


	if ( nVerbose ) roBib.SetVerbose ( true );
	bibrestart ( pfIn );
	int nRet = bibparse();

	if ( nRet )		return nRet;

	roBib.PostProcess();



	if ( poOutput ) poOutput->Dump();
	if ( pfTemplate )
		{
		CTemplate& roTemplate = CTemplate::Instance();
		roTemplate.SetODB ( roBib.GetODB() );
		if ( sConstraints.size() )
			{
			std::cerr << "Using constraints: " << sConstraints << std::endl;
			nRet = roTemplate.BeginParse( pfTemplate, sConstraints );
			}
		else
			nRet = roTemplate.BeginParse( pfTemplate );
		}
		
	if ( nRet )	{ std::cerr << "Error while processing Template (" << nRet << ")" << std::endl; return nRet; }

	return 0;
	}
