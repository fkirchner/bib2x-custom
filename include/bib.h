#ifndef __BIB__H_
#define __BIB__H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "generic.h"
#include "odb.h"

//#include "output.h"

const long usersigns_word		= 0x0001;
const long usersigns_path		= 0x0002;
const long usersigns_accent		= 0x0003;
const long usersigns_number		= 0x0004;
const long usersigns_comma		= 0x0005;
const long usersigns_dot		= 0x0006;
const long usersigns_opar		= 0x0007;
const long usersigns_epar		= 0x0008;
const long usersigns_latex		= 0x0009;
const long usersigns_missing    = 0x0010;
const long usersigns_mathmode   = 0x0011;
const long usersigns_abbrev     = 0x0012;
const long usersigns_equal		= 0x0013;
const long usersigns_exclam		= 0x0014;
const long usersigns_quest		= 0x0015;

const long usersigns_objectlink = 0xDEAD;
const long usersigns_key		= 0xABBA;
const long usersigns_type		= 0xBEEF;

const long objects_atentry		= 0x0001;
const long objects_atstring		= 0x0002;
const long objects_atpreamble	= 0x0003;
const long objects_atinclude	= 0x0004;
const long objects_atcomment	= 0x0005;
const long objects_tag			= 0x0010;
const long objects_explizit		= 0x0011;

 

class CObjectEntry
{
public:
odb::CObject* poObject;
odb::CClass* poClass;

std::string sName;
std::string sType;
std::string sShort;

CObjectEntry ( odb::CObject* pO, odb::CClass* pC, std::string sN, std::string sT ) : poObject(pO), poClass(pC), sName(sN), sType(sT)
	{
	if ( sType == "Entry" ) sShort = "e";
	else if ( sType == "Tag" ) sShort = "t";
	else if ( sType == "Explizit" ) sShort = "x";
	else if ( sType == "Meta" ) sShort = "m";
	else { std::cerr << "Uh Oh: " << sType << std::endl; exit(2); }
	}

};


typedef std::map<std::string, odb::CClass*> CMapName2Class;

typedef std::map<std::string, odb::CReason*> CMapName2Reason;

typedef std::map<std::string, odb::CObject*> CMapAbbrev2Object;

typedef std::vector<CObjectEntry*> CVectorObjects;

class CBib
{
protected:

bool m_bVerbose;

bool m_bNextPrefix;
bool m_bBeginExplizit;
bool m_bEndExplizit;

int m_nDepth;
int m_nAtoms;

odb::CODB odb;



std::string m_sCurrentObject;

CMapName2Class m_mName2Class;

CMapName2Reason m_mName2Reason;

CMapAbbrev2Object m_mAbbrev2Object;

CVectorObjects m_vObjects;
odb::CAtom* m_poLastAtom;

private:
	CBib();


public:

	static CBib& Instance()
		{
		static CBib oBib;
		return oBib;
		}

	odb::CODB& GetODB ( ) { return odb; }

	void dump() { odb.Dump(); }

	void pd ();

	bool IsVerbose ( ) { return m_bVerbose; }
	void SetVerbose ( bool bVerbose ) { m_bVerbose = bVerbose; }

	void SetPrefix ( bool bWhitespace ) { m_bNextPrefix = bWhitespace; }
	void SetKey ( std::string sText );

	void ExplizitIn (  );
	void ExplizitOut (  );
	void ExplizitFinish (  bool bWhite );
	
	void CreateObject ( std::string sName, std::string sType, long nType );
	void FinishObject ( std::string sName, long nType );
		
	 
    void AddAtom ( std::string sText, bool bWhite, long nUsersign );

	void LinkRopeToObject ( std::string sName );
	
	odb::CAtom* LinkAbbrevToObject ( std::string sAbbrev, odb::CObject* poObject );
	
	
	odb::CObject* ProcessAuthor ( std::string sAuthor );

	
	
	bool ProcessUmlauts ( );
	bool ProcessAuthors ( );
	bool PostProcess ( );

};

#endif

