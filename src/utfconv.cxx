#include <iostream>
#include <string>
#include <sstream>


#include "utfconv.h"

static const std::string sUtfDiaresis		= "&#x0308;"; // \"o
static const std::string sUtfGrave			= "&#x0300;"; // \ûo
static const std::string sUtfAcute			= "&#x0301;"; // \'o
static const std::string sUtfCircum			= "&#x0302;"; // \^o
static const std::string sUtfTilde			= "&#x0303;"; // \~o
static const std::string sUtfMacron			= "&#x0304;"; // \=o
static const std::string sUtfDotAbove		= "&#x0307;"; // \.o

static const std::string sUtfBreve			= "&#x0306;"; // \u{o}
static const std::string sUtfCaron			= "&#x030C;"; // \v{o}
static const std::string sUtfRingAbove		= "&#x030A;"; // \r{o}
static const std::string sUtfDoubleAcute	= "&#x030B;"; // \H{o}
static const std::string sUtfCedilla		= "&#x0327;"; // \c{o}
static const std::string sUtfDoubleInvBreve	= "&#x0361;"; // \t{oo}
static const std::string sUtfDotBelow		= "&#x0323;"; // \d{o}
static const std::string sUtfMacronBelow	= "&#x0331;"; // \b{o}

static const std::string sUtfUnknown		= "";


const std::string getCombiningUtf ( const char cAccent, const char nChar ) 
        {
            if ( cAccent == '\"' && nChar == 'a' ) return "ä";
            if ( cAccent == '\"' && nChar == 'A' ) return "Ä";
            if ( cAccent == '\"' && nChar == 'e' ) return "ë";
            if ( cAccent == '\"' && nChar == 'E' ) return "Ë";
            if ( cAccent == '\"' && nChar == 'i' ) return "ï";
            if ( cAccent == '\"' && nChar == 'I' ) return "Ï";
            if ( cAccent == '\"' && nChar == 'o' ) return "ö";
            if ( cAccent == '\"' && nChar == 'O' ) return "Ö";
            if ( cAccent == '\"' && nChar == 'u' ) return "ü";
            if ( cAccent == '\"' && nChar == 'U' ) return "Ü";
            if ( cAccent == '\'' && nChar == 'a' ) return "á";
            if ( cAccent == '\'' && nChar == 'A' ) return "Á";
            if ( cAccent == '\'' && nChar == 'e' ) return "é";
            if ( cAccent == '\'' && nChar == 'E' ) return "É";
            if ( cAccent == '`' && nChar == 'a' ) return "à";
            if ( cAccent == '`' && nChar == 'A' ) return "À";
            if ( cAccent == '`' && nChar == 'e' ) return "è";
            if ( cAccent == '`' && nChar == 'E' ) return "È";
            if ( cAccent == '`' && nChar == 'u' ) return "ù";
            if ( cAccent == '`' && nChar == 'U' ) return "Ù";
            if ( cAccent == '^' && nChar == 'a' ) return "â";
            if ( cAccent == '^' && nChar == 'A' ) return "Â";
            if ( cAccent == '^' && nChar == 'e' ) return "ê";
            if ( cAccent == '^' && nChar == 'E' ) return "Ê";
            if ( cAccent == '^' && nChar == 'i' ) return "î";
            if ( cAccent == '^' && nChar == 'I' ) return "Î";
            if ( cAccent == '^' && nChar == 'o' ) return "ô";
            if ( cAccent == '^' && nChar == 'O' ) return "Ô";
            if ( cAccent == '^' && nChar == 'u' ) return "û";
            if ( cAccent == '^' && nChar == 'U' ) return "Û";
            if ( cAccent == '~' && nChar == 'n' ) return "ñ";
            if ( cAccent == 'c' && nChar == 'c' ) return "ç";

            std::cerr << "ERROR: Accent " << cAccent << " and character " << nChar << " are not supported yet, edit utfconv.cxx to fix." << std::endl;
            return "TODO";
        }

const std::string& getCombining ( const char cAcent )
	{
	switch ( cAcent )
		{
		case '\"': return sUtfDiaresis;
		case '`':  return sUtfGrave;
		case '\'': return sUtfAcute;
		case '^':  return sUtfCircum;
		case '~':  return sUtfTilde;
		case '=':  return sUtfMacron;
		case '.':  return sUtfDotAbove;
		case 'u':  return sUtfBreve;
		case 'v':  return sUtfCaron;
		case 'r':  return sUtfRingAbove;
		case 'H':  return sUtfDoubleAcute;
		case 'c':  return sUtfCedilla;
		case 't':  return sUtfDoubleInvBreve;
		case 'd':  return sUtfDotBelow;
		case 'b':  return sUtfMacronBelow;
		}
	return sUtfUnknown;
	}


const std::string getHex ( unsigned int nChar )
	{
    std::stringstream strUtf;

    strUtf.setf(std::ios_base::hex,std::ios_base::basefield);
    strUtf << nChar;
	return strUtf.str();
	}

char caseChar ( char cChar, int nCase )
	{
	if ( nCase == utf_char_lowercase ) return tolower ( cChar );
	if ( nCase == utf_char_uppercase ) return toupper ( cChar );
	return cChar;
	}

std::string TexToUtfCode ( std::string sContent, int nCase )
	{
	for ( unsigned long i = sContent.find ( "\\" ); i < sContent.length(); i = sContent.find("\\") )
		sContent.replace ( i, 1, "" );
	for ( unsigned long i = sContent.find ( "{" ); i < sContent.length(); i = sContent.find("{") )
		sContent.replace ( i, 1, "" );
	for ( unsigned long i = sContent.find ( "}" ); i < sContent.length(); i = sContent.find("}") )
		sContent.replace ( i, 1, "" );

	if ( sContent.length() > 2 ) // was absurdes, wie z.B. oo mit geschwungener Brcke darber
		{
		if ( sContent[0] == 't' )
			{
			std::string sTemp = "&#x";
			sTemp += getHex ( caseChar ( sContent[1], nCase ) );
			sTemp += ";" + sUtfDoubleInvBreve + caseChar ( sContent[2], nCase );
			return sTemp;
			}
		else sContent.replace(0,1,"");
		return sContent;
		}
	if ( sContent.length() < 2 ) // uU war das etwas wie ein i ohne punkt -> who cares.
		{
		if ( sContent.length() == 1 ) 
			{
			
			switch ( caseChar ( sContent[0], nCase ) )
				{
				case 'o': return "&#x00F8;";
				case 'O': return "&#x00D8;";
				case 'i': return "&#x0131;";
				case 'I': return "&#x0130;";
				case 'l': return "&#x0142;";
				case 'L': return "&#x0141;";
				case '!': return "&#x00A1;";
				case '?': return "&#x00BF;";
				}
			}
		
				
		return sContent;
		}

	/* unsigned int nChar = sContent[1]; */
	
	const std::string& sCombined = getCombiningUtf( sContent[0] , sContent[1] );

	if ( sCombined.length() > 0 )	
            return sCombined;
		/* return ( "&#x" + getHex ( nChar ) + ";" + sCombined ); */
	
	char cA = caseChar ( sContent[0], nCase );
	char cB = caseChar ( sContent[1], nCase );
	
	if ( cA == 'a' && cB == 'e' ) return "&#x00E6;";
	if ( cA == 'A' && cB == 'E' ) return "&#x00C6;";
	if ( cA == 'o' && cB == 'e' ) return "&#x0153;";
	if ( cA == 'O' && cB == 'E' ) return "&#x0152;";
	if ( cA == 'a' && cB == 'a' ) return "&#x0061;&#x030A;";
	if ( cA == 'A' && cB == 'A' ) return "&#x0041;&#x030A;";
	if ( cA == 's' && cB == 's' ) return "&#x00DF;";
	if ( cA == 'S' && cB == 'S' ) return "SS";

	return sContent;
	}
