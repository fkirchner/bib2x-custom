#ifndef __output__H_
#define __output__H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "generic.h"
#include "odb.h"


#include "bib.h"
using namespace odb;



typedef long sort_direction;
static const sort_direction sort_up	= 0x0001;
static const sort_direction sort_down = 0x0002;


typedef std::set<std::string> CSetString;

class COutput
{
protected:

	odb::CODB& odb;

	void write ( std::string sText ) { std::cout << sText; }

	virtual void GenerateHeader ();
	virtual void GenerateTOC ( odb::CVectorRoot& vObjects );
	//virtual void GenerateEntries ();
	virtual void GenerateFooter ();
	
	virtual void EntryOpen ( std::string sType, std::string sKey );
	virtual void EntryClose ( std::string sKey );
	
	virtual void TagOpen ( std::string sName, bool bMissing );
	virtual void TagClose ( std::string sName, bool bMissing );
	
	virtual void ExplizitBegin ( );
	virtual void ExplizitEnd ( );
	
	virtual void Author ( std::string sName, CSetString lLinks );
	
	virtual void Whitespace ();
	
	virtual void Atom ( long nType, std::string sContent );
	
	void StepThroughAtoms ( odb::CVectorAtom::iterator vIt, odb::CVectorAtom::iterator vItEnd );
	void StepThroughTag ( odb::CObject& roObj );

	odb::CVectorRoot SortObjects ( odb::CVectorRoot& vObject, long nKey, sort_direction nDir );

public:

	COutput ( odb::CODB& rOdb ) : odb ( rOdb ) { }

	virtual void Dump();
};

#endif

