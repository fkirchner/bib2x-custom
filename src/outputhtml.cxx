#include <iostream>
#include <sstream>


#include "output.h"
#include "outputhtml.h"

#include "bib.h"
#include "utfconv.h"
#include "latexconv.h"

#include "odb.h"


using namespace odb;

#define _HTML_OUTPUT_VERSION 0.01
#define _IE6_WORKAROUNDS

void COutputHtml::GenerateHeader ()
	{

	std::string sStyleSheetScreen     = "bib.css";
	std::string sStyleSheetPrint      = "bib.css";
	std::string sStyleSheetProjection = "bib.css";
	
	std::string sTitle = "xandi's BibTeX collection"; //TODO
	
	std::string sHeader;
	sHeader  = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"";
	sHeader += " \"http://www.w3.org/TR/html4/transitional.dtd\">\n<html>\n";

	sHeader += "<head>\n";
	sHeader += "<meta name=\"GENERATOR\" content=\"BibX - BibTeX-Tool, (c) Alexander Feder\">\n";
	sHeader += "<TITLE>" + sTitle + "</TITLE>\n";
	
#ifdef _IE6_WORKAROUNDS
	sHeader += "<link rel=\"stylesheet\" href=\"" + sStyleSheetScreen     + "\" media=\"screen\"     type=\"text/css\" />\n";
	sHeader += "<link rel=\"stylesheet\" href=\"" + sStyleSheetPrint      + "\" media=\"print\"      type=\"text/css\" />\n";
	sHeader += "<link rel=\"stylesheet\" href=\"" + sStyleSheetProjection + "\" media=\"projection\" type=\"text/css\" />\n";
	sHeader += "</head>\n\n";
#else
	sHeader += "</head>\n\n";
	sHeader += "<style type=\"text/css\">\n<!--\n";
	sHeader += "@import url(" + sStyleSheetScreen     + ") screen;\n";
	sHeader += "@import url(" + sStyleSheetPrint      + ") print;\n";
	sHeader += "@import url(" + sStyleSheetProjection + ") projection;\n";
	sHeader += "-->\n</style>\n";
#endif
	sHeader += "\n\n<body>\n";
	
	
	write ( sHeader );

	}
	
void COutputHtml::GenerateTOC ( odb::CVectorRoot& vObjects )
	{
	
	std::string sToc;
	std::string sKey;
	sToc += "<div id=\"BibTOC\">";
	
	CVectorRoot::iterator vOIt = vObjects.begin();
	CVectorRoot::iterator vOItEnd = vObjects.end();
	
	for ( ; vOIt != vOItEnd; ++vOIt )
		{
		CObject* poObj = dynamic_cast<CObject*>(*vOIt);
		
	    CVectorAtom vKey  = poObj->AtomGetBySign( usersigns_key );
		
		if ( vKey.begin () != vKey.end()  ) 
			{
			sKey  = (*(vKey.begin ()))->UIFormat();
			sToc += "<a href=\"#" + sKey + "\">"
								  + sKey + "</a><br>\n";

			}
		}
	
	sToc += "<br></div>";
	write ( sToc );
	
	}
	
void COutputHtml::GenerateFooter ()
	{

	std::string sFooter;
	std::stringstream strVersion;
	strVersion << _HTML_OUTPUT_VERSION; 
    sFooter = "<br><br><br>HtmlOutput Version: ";
	sFooter += strVersion.str();
	sFooter += "\n";
	sFooter += "</body>\n</html>\n";
	
	write ( sFooter );

	}

void COutputHtml::Dump() { Inherited::Dump(); }




void COutputHtml::EntryOpen ( std::string sType, std::string sKey ) 
	{

	std::string sEntry = "<br>\n";

	sType.erase(0,1);

	sEntry += "<div class=\"BibEntry\"><a class=\"EntryGoto\" id=\"" + sKey + "\"></a>\n";
	
	sEntry += "<span class=\"EntryType\">" + sType + "</span> <span class=\"EntryKey\">" + sKey + "</span><br>\n"
	       + "<table class=\"EntryTable\">\n"
		   + "<tr class=\"TagRow\"><td class=\"NameCollumn\"><div class=\"EntryTableInfo\">Tag</div></td>"
		   + "<td class=\"ContentColumn\"><div class=\"EntryTableInfo\">Content</div></td></tr>\n";
		   
	write ( sEntry );
	}
	
void COutputHtml::EntryClose ( std::string sKey )
	{
	std::string sEntry;
	
	
	sEntry = "</table></div><br><br>\n";

	write ( sEntry );
	}
	
void COutputHtml::TagOpen ( std::string sName, bool bMissing )
	{
	std::string sTag;
	
	std::string sContentClass = "ContentText";
	std::string sNameClass = "NameText";
	
	if ( bMissing ) sNameClass = "NameTextMissing";
	
	sTag = "<tr class=\"TagRow\"><td class=\"" + sName + "\" class=\"NameCollumn\"><div class=\"" + sNameClass + "\">" + sName + "</div></td>\n"
		 + "<td class=\"" + sName + "\" class=\"ContentColumn\"><span class=\"" + sContentClass + "\">";
	
	write ( sTag );
	}
	

void COutputHtml::TagClose ( std::string sName, bool bMissing )
	{
	std::string sTag;
	
	sTag = "</span></td></tr>\n";
	
	write ( sTag );
	}

void COutputHtml::ExplizitBegin ( )
	{
	if ( !m_vEnclosings.size() ) write ( "<span class=\"Explizit\">" );
	}
void COutputHtml::ExplizitEnd ( )
	{
	if ( m_vEnclosings.size() )
		{
		long nEnclosing = m_vEnclosings.back();
		m_vEnclosings.pop_back();
		write ( Enclosings2String ( nEnclosing ) );
		}
	else write ( "</span>" );
	}
void COutputHtml::Whitespace()
	{ 
	if ( m_bKillNextWhitespace ) 
		{ 
		m_bKillNextWhitespace = false; 
		} 
	else
		{
		write ( " " );
		}
	}

std::string COutputHtml::Enclosings2String ( long nEnclosing )
	{
	if ( nEnclosing == enclosings_emphopen )	return "<i>";
	if ( nEnclosing == enclosings_emphclose )	return "</i>";

	return "";
	}


void COutputHtml::Atom ( long nType, std::string sContent )
	{
	std::string sAtom;
	
	std::string sType;
	switch ( nType )
		{
		case usersigns_word:		sType = "word"; break;
		case usersigns_path:		sType = "path"; sContent = "<a href=\"" + sContent + "\">" + sContent + "</a>"; break;
		case usersigns_accent:		sType = "accent"; sContent = TexToUtfCode ( sContent ); break;
		case usersigns_number:		sType = "number"; break;
		case usersigns_comma:		sType = "comma"; break;
		case usersigns_dot: 	 	sType = "dot" ; break;
		case usersigns_opar:		sType = "opar"; break;
		case usersigns_epar:		sType = "epar"; break;
		case usersigns_latex:		sType = "latex";
									if ( m_oLatexConv.ElimWhitespace ( sContent ) ) m_bKillNextWhitespace = true;
									if ( m_oLatexConv.IsEnclosing(sContent) )
										{
										POpenClose pOC = m_oLatexConv.GetEnclosing(sContent);
										if ( pOC.second != enclosings_nothing )
											{
											m_vEnclosings.push_back ( pOC.second );
											}
										sContent = Enclosings2String ( pOC.first );
										write(sContent);
										return;
										}
									else
										{
										sContent = m_oLatexConv.Latex2Utf ( sContent ); 
										}
									break;
		case usersigns_missing:     sType = "missing"; break;
		case usersigns_mathmode:    sType = "math"; break;
		default: sType = "word"; break;
		}
	
	
	
	sAtom = "<span class=\"Text_" + sType + "\">" + sContent + "</span>";





	write ( sAtom );
	}

void COutputHtml::Author ( std::string sName, CSetString lLinks ) 
	{ 
	std::cout << "<br>" << sName << ": ";
	
	CSetString::iterator lIt = lLinks.begin();
	CSetString::iterator lItEnd = lLinks.end();
	
	for (bool bBegin = true; lIt != lItEnd; ++lIt )
		{
		std::cout << (bBegin?"":", ") << "<a href=\"#" << (*lIt) << "\">" << (*lIt) << "</a>";
		bBegin = false;
		}
	std::cout << "" << std::endl;
	}

