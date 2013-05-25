#include <iostream>
#include <sstream>


#include "output.h"
#include "bib.h"

void COutput::GenerateHeader ()
	{
	std::cout << "Doing plain Output" << std::endl; 
	}
	
void COutput::GenerateTOC ( odb::CVectorRoot& vObjects )
	{
	}
	
void COutput::GenerateFooter ()
	{
	}
	
void COutput::EntryOpen ( std::string sType, std::string sKey ) 
	{
	std::cout << std::endl;


	std::cout << sType << ": " << sKey << std::endl;
	std::cout << "  -> Tag: Content" << std::endl;


	}
	
void COutput::EntryClose ( std::string sKey )
	{
	std::cout << std::endl;

	}
	
void COutput::TagOpen ( std::string sName, bool bMissing )
	{
	std::cout << "  -> " << sName << ": ";
	}
	
void COutput::TagClose ( std::string sName, bool bMissing )
	{
	std::cout << std::endl;
	}	

void COutput::ExplizitBegin ( ) { std::cout << "{"; }
void COutput::ExplizitEnd ( ) { std::cout << "}"; }

void COutput::Whitespace() {std::cout << " ";}


void COutput::Atom ( long nType, std::string sContent )
	{
	std::cout << sContent;
	}

void COutput::StepThroughAtoms ( CVectorAtom::iterator vIt, CVectorAtom::iterator vItEnd )
	{
	for ( ; vIt != vItEnd; ++vIt )
		{
		const std::string& sPrefix = (*vIt)->PrefixGet();
		if ( sPrefix.length() )
			{
			if ( sPrefix.length() > 1 )
				if ( sPrefix[1] == '{' ) ExplizitBegin();

			if ( sPrefix[0] == '{' ) ExplizitBegin();
			if ( sPrefix[0] == ' ' ) Whitespace();
			}
		
		if ( (*vIt)->UserSignGet() == usersigns_objectlink ) //now resolve that object
			{
			std::stringstream stStream;
			stStream << (*vIt)->UIFormat();
			int nObject;
			stStream >> nObject;
			ExplizitBegin();
			CObject* poObject = odb.Id2PtrObject ( nObject );
			if ( poObject )
				{
				CVectorAtom vAtoms = poObject->AtomsGet ();
		
//x3				StepThroughAtoms ( ++vAtoms.begin(), vAtoms.end() );
				StepThroughAtoms ( vAtoms.begin(), vAtoms.end() );
				}
			
			else Atom ( usersigns_missing, "ERROR: Object not found!" );
			
			ExplizitEnd();
			}
		else
			{
			Atom ( (*vIt)->UserSignGet(), (*vIt)->UIFormat() );
			}
		
		const std::string& sSuffix = (*vIt)->SuffixGet();
		if ( sSuffix.length() )
			{
			if ( sSuffix[0] == ' ' ) Whitespace();
			if ( sSuffix[0] == '}' ) ExplizitEnd();
			if ( sSuffix.length() > 1 )
				if ( sSuffix[1] == '}' ) ExplizitEnd();
			}


		}
	}

void COutput::StepThroughTag ( CObject& roObj )
	{
	CVectorAtom vAtoms = roObj.AtomsGet ();
	
	CVectorAtom::iterator vIt = vAtoms.begin();
	CVectorAtom::iterator vItEnd = vAtoms.end();

//x3	std::string sTag = (*vIt)->UIFormat();
	std::string sTag = roObj.NameGet();
	bool bMissing = false;
//x3	if ( ++vIt == vItEnd ) bMissing = true;
	if ( vIt == vItEnd ) bMissing = true;
	TagOpen ( sTag, bMissing );
	StepThroughAtoms ( vIt, vItEnd );
	TagClose ( sTag, bMissing  );
	}


odb::CVectorRoot COutput::SortObjects ( odb::CVectorRoot& vObject, long nKey, sort_direction nDir )
	{
	
	typedef std::map<std::string,odb::CObject*> CMStr2Object;
	
	CMStr2Object mStr2Object;
	
	odb::CVectorRoot::iterator vIt    = vObject.begin();
	odb::CVectorRoot::iterator vItEnd = vObject.end();
	
	for ( ; vIt != vItEnd; ++vIt )
		{
		CObject* poObj = dynamic_cast<CObject*>(*vIt);

		CVectorAtom vKey  = poObj->AtomGetBySign( nKey );
		if ( vKey.begin() != vKey.end()  ) 
			{
			mStr2Object[(*(vKey.begin ()))->UIFormat()] = poObj;
			}
		}

	CMStr2Object::iterator mIt		= mStr2Object.begin();
	CMStr2Object::iterator mItEnd	= mStr2Object.end();
	
	
	odb::CVectorRoot vSorted; 
	
	//TODO reverse-iterator wenn sort_direction = sort_up
	for ( ; mIt != mItEnd; ++mIt )
		{
		vSorted.push_back ( (*mIt).second );
		}
	
	return vSorted;
	}




void COutput::Dump() 
	{ 
	//odb.Dump();
	std::cerr << "Dumping" << std::endl;
	GenerateHeader();

	std::cerr << "Getting Entries..." << std::flush;
	
	CVectorRoot vClass = odb.GetClass ( _TEXT("Entry") );
	
	CVectorRoot::iterator vIt = vClass.begin();
	if ( vIt == vClass.end() ) return;
	
	CListObject lObject = dynamic_cast<CClass*>(*vIt)->ObjectsGet();
	
	CListObject::iterator lIt = lObject.begin();
	CListObject::iterator lItEnd = lObject.end();
	
	CVectorRoot vObject;
	
	for ( ;lIt != lItEnd; ++lIt )
		{
		CRoot* poRoot = dynamic_cast<CRoot*>(*lIt);
		if ( poRoot ) vObject.push_back(poRoot);
		}
	
	
	std::cerr << " ok" << std::endl << "Sorting..." << std::flush;
	
	vObject = SortObjects ( vObject, usersigns_key, sort_up );
	
	std::cerr << " ok" << std::endl << "Generating TOC..." << std::flush;
	
	GenerateTOC(vObject);
	std::cerr << " ok" << std::endl << "Generating Entries..." << std::flush;

	
	CVectorRoot::iterator vOIt = vObject.begin();
	CVectorRoot::iterator vOItEnd = vObject.end();
	
	for ( ; vOIt != vOItEnd; ++vOIt )
		{
		CObject* poObj = dynamic_cast<CObject*>(*vOIt);
		

		
	    CVectorAtom vKey  = poObj->AtomGetBySign( usersigns_key );

		std::string sKey  = "MISSING!"; 
		std::string sType = poObj->NameGet();
		
		if ( vKey.begin () != vKey.end()  ) sKey  = (*(vKey.begin ()))->UIFormat();
		
		EntryOpen ( sType, sKey );
			
		CMapChildren& mRef = const_cast<CMapChildren&> ( (dynamic_cast<CObject*>(*vOIt))->ChildrenGet());
		
		CMapChildren::iterator mIt = mRef.begin();
		CMapChildren::iterator mItEnd = mRef.end();

		for ( ; mIt != mItEnd; ++mIt )
			{
			if ( mIt->first->ClassGet()->NameGet() == "Author" )  continue;

			StepThroughTag ( (*mIt->first) );
			}
		EntryClose ( sKey );
		}





	CVectorRoot vClass2 = odb.GetClass ( _TEXT("Author") );
	
	CVectorRoot::iterator vIt2 = vClass2.begin();
	if ( vIt2 == vClass2.end() ) return;
	
	CListObject lAuthors = dynamic_cast<CClass*>(*vIt2)->ObjectsGet();
	
	CListObject::iterator lAIt	  = lAuthors.begin();
	CListObject::iterator lAItEnd = lAuthors.end();
	
	for ( ; lAIt != lAItEnd; ++lAIt )
		{
		CSetString lLinks;
		
		CMapReferencing mParents = (*lAIt)->ParentsGet();
		
		CMapReferencing::iterator refIt		= mParents.begin();
		CMapReferencing::iterator refItEnd	= mParents.end();
			
		for ( ; refIt != refItEnd; ++refIt )
			{
		    CVectorAtom vKey  = dynamic_cast<CObject*>(refIt->first)->AtomGetBySign( usersigns_key );

			std::string sKey  = "MISSING!"; 
			
			if ( vKey.begin () != vKey.end()  ) sKey  = (*(vKey.begin ()))->UIFormat();
			lLinks.insert ( sKey );
			}
		Author ( (*lAIt)->NameGet(), lLinks );	
		}
		
	std::cerr << " ok" << std::endl << "Generating Footer..." << std::flush;

	GenerateFooter();
	std::cerr << " ok" << std::endl;

	}
	
void COutput::Author ( std::string sName, CSetString lLinks ) 
	{ 
	std::cout << sName << ": ";
	
	CSetString::iterator lIt = lLinks.begin();
	CSetString::iterator lItEnd = lLinks.end();
	
	for (bool bBegin = true; lIt != lItEnd; ++lIt )
		{
		std::cout << (bBegin?"":", ") << (*lIt);
		bBegin = false;
		}
	std::cout << std::endl;
	}
