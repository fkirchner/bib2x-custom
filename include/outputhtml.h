#ifndef __outputhtml__H_
#define __outputhtml__H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "generic.h"
#include "odb.h"
#include "latexconv.h"


#include "bib.h"
#include "output.h"


class COutputHtml : public COutput
{
private:
	typedef COutput Inherited;

protected:


std::vector<long> m_vEnclosings;
bool m_bKillNextWhitespace;

CLatexConv& m_oLatexConv;


void GenerateHeader ();
void GenerateTOC ( odb::CVectorRoot& vObjects );
//void GenerateEntries ();
void GenerateFooter ();


void EntryOpen ( std::string sType, std::string sKey );
void EntryClose ( std::string sKey );
	
void TagOpen ( std::string sName, bool bMissing );
void TagClose ( std::string sName, bool bMissing );

void ExplizitBegin ( );
void ExplizitEnd ( );

void Author ( std::string sName, CSetString lLinks );


void Whitespace ();


void Atom ( long nType, std::string sContent );

std::string Enclosings2String ( long nEnclosing );

public:

	COutputHtml ( odb::CODB& rOdb ) : Inherited ( rOdb ), m_oLatexConv (CLatexConv::Instance())  { m_bKillNextWhitespace = false; }

	virtual ~COutputHtml () {}

	void Dump();
};

#endif

