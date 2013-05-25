#ifndef __TEMPLATE_H
#define __TEMPLATE_H

#include <stdio.h>
#include <map>
#include <set>
#include <vector>

#include "generic.h"
#include "odb.h"

#include "utfconv.h"
#include "latexconv.h"
#include "bib.h"

#include "entries.h"

const int compare_ignore	= 0x000;
const int compare_equals	= 0x001;
const int compare_not_equal = 0x002;
const int compare_lesser	= 0x003;
const int compare_greater	= 0x004;
const int compare_exists    = 0x005;

const bool sortorder_inc	= true;
const bool sortorder_dec	= false;

const int bibtoken_generic  = 0;
const int bibtoken_missing  = 1;
const int bibtoken_nonempty = 2;
const int bibtoken_empty	= 3;

typedef std::map<long,std::string> CMapLong2String;
typedef std::map<std::string,odb::CVectorRoot> CMapString2VectorRoot;
typedef std::map<std::string,std::string> CMapString2String;

class CTemplate
{
private:
	
CTemplate()
	{
	m_bIsValid = false;
	m_poCurrentRoot = new CEntryRoot ( 0 );
	m_poConstraint = 0;
	m_mDefines[definition_whitespace] = " ";
	}


protected:
	bool m_bIsValid;
	
	std::string m_sOutput;
	odb::CODB* m_poODB;

	CEntryRoot* m_poCurrentRoot;
	
	
	CVectorString m_vValues;

	CConstraint* m_poConstraint;


	std::string m_sDefine;
	CMapLong2String m_mDefines;
	CMapString2String m_mClasses;

	std::string sLastClass;

public:
	
	static CTemplate& Instance()
		{
		static CTemplate oTemplate;
		return oTemplate;
		}

	bool IsValid ( ) { return m_bIsValid; }
	
	void Between ( std::string sBetween );
	CEntryCommand* Command ( std::string sCommand, char cA = 0, char cB = 0 );

	void ForBegin ( ); 
	void ForEnd ( );

	void GroupBegin ( ); 
	void GroupEnd ( );


	void SetSortOrder ( std::string sOrder ); 
	void Condition ( std::string sCondition ); 
	void ConditionFinished ( ); 
	void Constraint ( std::string sConstraint, std::string sOperator, bool bSpecific ); 
	void AddValue ( std::string sValue);
	void FinishValues ( );
	

	void AddDefinition ( std::string sDef );
	void DefFinish ( std::string sNumber );
	std::string& GetDefinition ( long nDef ) { return m_mDefines[nDef]; }
	
	void BibBegin();
	void BibEnd(); 

	void ReduceBegin();
	void ReduceEnd();

	void Exclusion ( std::string sExcl );
	void Inclusion ( std::string sIncl );
	void Exclusive ( std::string sExcl );
	void SetToken  ( int nNumber );
	
	void SetOutput ( std::string sFilename ) { m_sOutput = sFilename; }
	void SetODB ( odb::CODB& odb ) { m_poODB = &odb; if ( m_poODB ) m_bIsValid=true; else m_bIsValid=false; }
	
	int BeginParse ( FILE* pfTemplate, std::string sConstraints = "" );


	void AddClass ( std::string sClass );
	void AddMember ( std::string sMember );
	CMapString2String& GetClasses ( ) { return m_mClasses; }


	void Modifier ( std::string sMod, std::string sCommand );
	void Step ( std::string sCommand, std::string sPrefix, std::string sDelim, std::string sSuffix, std::string sMod = "" );
	
	
	odb::CODB* GetODB ( ) { return m_poODB; }
	
};













#endif

