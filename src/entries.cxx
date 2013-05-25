#include <iostream>

#define CERR std::cerr << __PRETTY_FUNCTION__ << ":" << __LINE__

#include "entries.h"


CEntryRoot* CEntryRoot::Push ( CEntry* poEntry )
	{
	if ( !poEntry )
		{
		CERR << "poEntry nil" << std::endl;
		return 0;
		}
		
	m_vpoEntries[m_nCurrentToken].push_back ( poEntry );

	if ( poEntry->Rtti ( ) == CEntryRoot::rtti )
		{
		return dynamic_cast<CEntryRoot*>(poEntry);
		}
	
	return this;

	}


std::string CConstraint::Dump ( ) 
	{
	std::string sValues;
	for ( CVectorString::iterator vIt = m_vValues.begin(); vIt != m_vValues.end(); ++vIt )
		sValues += (*vIt);
	
	std::string sSpecific;
	std::stringstream stStream;
	stStream << m_nSpecific;
	stStream >>	sSpecific;
	
	return m_sName + ":" + sSpecific + "??" + sValues;
	}

