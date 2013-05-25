#include <iostream>
#include <string>
#include <strings.h>
#include <sstream>
#include <limits>

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif


#include <unistd.h>
#include <ctype.h>

#include "template.h"
#include "bib.h"

#define CERR std::cerr << "ERROR: - "
#define CDEBUG std::cerr << "DEBUG: " << __PRETTY_FUNCTION__ << ":" << __LINE__ << " - "
#define CWARN std::cerr << "WARNING: - "


extern FILE* templatein;
extern void templaterestart( FILE* );

extern void template_scan_string(const char *str);
extern int templateparse(void);
#ifdef YYDEBUG
extern int templatedebug;
#endif

char* str_tolower ( char* s );


void Write ( std::string sTemp );

std::string& ExplizitBegin ( std::vector<long>& vEnclosings );
std::string& ExplizitEnd ( std::vector<long>& vEnclosings );
std::string& Whitespace( bool& bKillNextWhitespace );

std::string GetAllAtoms ( odb::CObject* poObj, unsigned int nModifier = 0, int nRangeBegin = 0, int nRangeEnd = std::numeric_limits<int>::max(), std::string sRangePrefix = "", std::string sRangeDelim = "", std::string sRangeSuffix = "" );
std::string GetNthAtom ( odb::CObject* poObj, int nNumber );
bool ObjectIsEmpty ( odb::CObject* poObj );
bool CheckObjectForAtoms ( odb::CObject* poObj, CVectorString vValues, int nSpecific );

void ReduceAndSort ( odb::CVectorRoot& vRoot, CConstraint& roConst, bool bSort, bool bSortOrder, CMapString2VectorRoot& mStr2Objects );
void ProcessConstraints ( CEntryRoot* poEntryRoot, odb::CVectorRoot& voObjectRoot, CMapString2VectorRoot& mStr2Objects );

void DumpCommand ( CEntryCommand *poEntryCommand, odb::CObject* poObj );
void DumpRoot ( CEntryRoot* poEntryRoot, odb::CVectorRoot voObjectRoot );
void DumpFor ( CEntryRootFor* poEntryRootFor, odb::CVectorRoot voObjectRoot );
void DumpGroup ( CEntryRootGroup* poEntryRootGroup, odb::CVectorRoot voObjectRoot );
void DumpBib ( CEntryRootBib* poEntryRootBib, odb::CObject* poObj );
void DumpTag ( CEntryRootBib* poEntryRootBib, odb::CObject* poTag, int nToken );
void DumpReduce ( CEntryRootReduce* poEntryRootReduce, odb::CVectorRoot& voObjectRoot );





std::string string2lower ( const std::string& sString )
	{
	std::string sTemp = sString;

	std::string::iterator sIt = sTemp.begin();
	std::string::iterator sItEnd = sTemp.end();
	
	for ( ; sIt != sItEnd; ++sIt )
		{
		(*sIt) = tolower (*sIt);
		}
	return sTemp;
	}


void CTemplate::Between ( std::string sBetween )
	{
//	CDEBUG << std::endl;
	m_poCurrentRoot->Push ( new CEntryText ( sBetween ) );
	}

CEntryCommand* CTemplate::Command ( std::string sCommand, char cA, char cB ) 
	{
	sCommand.erase(0,2);
	sCommand.erase(sCommand.length()-2,2);
//	CDEBUG << "Command: [" << sCommand << "]" << std::endl;
	
	//TODO specific!
	int nSpecific = 0;
	
	CEntryCommand* poEntry = 0;
	if ( cA >= 'A' ) poEntry =  new CEntryCommand ( sCommand, nSpecific, cA, cB );
	else              poEntry = new CEntryCommand ( sCommand, nSpecific );
	m_poCurrentRoot->Push ( poEntry );
	return poEntry;
	}



void CTemplate::ForBegin ( ) 
	{
//	CDEBUG << std::endl;
	m_vValues.clear();
	CEntryRoot* poNewRoot = dynamic_cast<CEntryRoot*>(new CEntryRootFor ( m_poCurrentRoot ));
	m_poCurrentRoot->Push ( poNewRoot );
	m_poCurrentRoot = poNewRoot;
	}

void CTemplate::ForEnd ( )
	{
//	CDEBUG << std::endl;
	m_poCurrentRoot = m_poCurrentRoot->GetParent();
	}

void CTemplate::GroupBegin ( ) 
	{
//	CDEBUG << std::endl;
	m_vValues.clear();
	CEntryRoot* poNewRoot = dynamic_cast<CEntryRoot*>(new CEntryRootGroup ( m_poCurrentRoot ));
	m_poCurrentRoot->Push ( poNewRoot );
	m_poCurrentRoot = poNewRoot;
	}

void CTemplate::GroupEnd ( )
	{
//	CDEBUG << std::endl;
	m_poCurrentRoot = m_poCurrentRoot->GetParent();
	}


void CTemplate::ReduceBegin()
	{
	m_vValues.clear();
	CEntryRoot* poNewRoot = dynamic_cast<CEntryRoot*>(new CEntryRootReduce ( m_poCurrentRoot ));
	m_poCurrentRoot->Push ( poNewRoot );
	m_poCurrentRoot = poNewRoot;
	}

void CTemplate::ReduceEnd()
	{
	m_poCurrentRoot = m_poCurrentRoot->GetParent();
	}



void Write ( std::string sTemp)
	{
	std::cout << sTemp;
	}
	

void CTemplate::SetSortOrder ( std::string sOrder ) 
	{	
//	CDEBUG << std::endl;
//	std::cerr << "(" << sOrder << ")" << std::endl; 
	
	if ( sOrder == "inc" ) { m_poCurrentRoot->SetSortOrder ( sortorder_inc ); return; }
	if ( sOrder == "dec" ) { m_poCurrentRoot->SetSortOrder ( sortorder_dec ); return; }

	return;
	}



void CTemplate::ConditionFinished()
	{
//	CDEBUG << std::endl;
	}


void CTemplate::Condition ( std::string sCondition ) 
	{
//	CDEBUG << "( cond: " << sCondition << " )" << std::endl;
	m_poCurrentRoot->ConditionAdd ( sCondition );
	
	}

void CTemplate::Constraint ( std::string sConstraint, std::string sOperator, bool bSpecific ) 
	{ 
//	CDEBUG << std::endl;
	
	int nSpecific = 0;
	if ( bSpecific ) 
		{
		int nPos = sConstraint.find(':');
		char cSpecific = sConstraint[nPos+1];
        
		if ( cSpecific == 'x' ) nSpecific = -1;
		else
			{
			std::stringstream stStream;
		
			stStream << sConstraint.substr ( nPos+1, sConstraint.length() - (nPos+1));
			stStream >> nSpecific;
			}

		sConstraint.erase ( nPos, sConstraint.length() - nPos );
		}
	
	
	int nCondition = compare_ignore;
	
	if ( sOperator == "=" )  nCondition = compare_equals;
	if ( sOperator == "!=" ) nCondition = compare_not_equal;
	if ( sOperator == "<" )  nCondition = compare_lesser;
	if ( sOperator == ">" )  nCondition = compare_greater;
	
	
	m_poConstraint = new CConstraint ( sConstraint, nSpecific, nCondition );
	//std::cerr << "constr: " << sConstraint << " mit " << sOperator << " " << std::flush; 
	}

void CTemplate::AddValue ( std::string sValue )
	{
//	CDEBUG << "( val: " << sValue << " )" << std::endl;
	if ( !m_poConstraint ) return; //TODO fehler!
	m_poConstraint->Push ( sValue );
	}

void CTemplate::FinishValues ()
	{
//	CDEBUG << std::endl;
	if ( !m_poConstraint ) return; //TODO fehler!
	m_poCurrentRoot->ConstraintAdd ( *m_poConstraint );
	delete m_poConstraint;
	m_poConstraint = 0;
	}
	


std::string& ExplizitBegin ( std::vector<long>& vEnclosings )
	{
	CTemplate& roTemplate = CTemplate::Instance();
	
	static std::string sEmpty = "";
	if ( !vEnclosings.size() ) return roTemplate.GetDefinition(enclosings_explizitopen);
	return sEmpty;
	}

std::string& ExplizitEnd ( std::vector<long>& vEnclosings )
	{
	CTemplate& roTemplate = CTemplate::Instance();

	if ( vEnclosings.size() )
		{
		long nEnclosing = vEnclosings.back();
		vEnclosings.pop_back();
		return roTemplate.GetDefinition( nEnclosing );
		}
	return roTemplate.GetDefinition( enclosings_explizitclose );
	}



std::string& Whitespace( bool& bKillNextWhitespace )
	{
	CTemplate& roTemplate = CTemplate::Instance();

	static std::string sEmpty = "";
	if ( bKillNextWhitespace ) 
		{ 
		bKillNextWhitespace = false;
		return sEmpty;
		} 
	else
		{
		return roTemplate.GetDefinition( definition_whitespace );
		}
	}


bool Modify ( std::string& sTemp, unsigned int nModifier, bool bStatus )
	{
	std::string::iterator sIt = sTemp.begin();
	std::string::iterator sItEnd = sTemp.end();
	
	switch ( nModifier )
		{
		case CEntryCommand::mod_lowercase:
			for ( ; sIt != sItEnd; ++sIt ) (*sIt) = tolower (*sIt);
			break;

		case CEntryCommand::mod_lowercase_firstupper:
			if ( !bStatus && ( sIt != sItEnd ) ) { (*sIt) = toupper (*sIt); ++sIt; }
			for ( ; sIt != sItEnd; ++sIt ) (*sIt) = tolower (*sIt);
			break;

		case CEntryCommand::mod_uppercase:
			for ( ; sIt != sItEnd; ++sIt ) (*sIt) = toupper (*sIt);
			break;

		case CEntryCommand::mod_uppercase_begin:
			if ( sIt != sItEnd ) { (*sIt) = toupper (*sIt); ++sIt; }
			for ( ; sIt != sItEnd; ++sIt ) (*sIt) = tolower (*sIt);			
			break;
		}
	return true;
	}

std::string GetAllAtoms ( odb::CObject* poObj, unsigned int nModifier, int nRangeBegin, int nRangeEnd, std::string sRangePrefix, std::string sRangeDelim, std::string sRangeSuffix )
	{
	
	CTemplate& roTemplate = CTemplate::Instance();
	CLatexConv& roLatex = CLatexConv::Instance();
	
	std::vector<long> vEnclosings;
	bool bKillNextWhitespace = false;
	
	odb::CVectorAtom vAtoms = poObj->AtomsGet ();
	
	odb::CVectorAtom::iterator vIt = vAtoms.begin();
	odb::CVectorAtom::iterator vItEnd = vAtoms.end();
	
	std::string sContent;
	bool bRangeEnd = false;
	bool bInsideRange = false;
	
	bool bStatus = false;
	
	int nExplizit = 0;

	if ( ( vIt != vItEnd ) && ( (int)vAtoms.size() >= nRangeBegin ) && ( (int)vAtoms.size() <= nRangeEnd ) )
		{
		bRangeEnd = true;
		sContent = sRangePrefix;
		}
	
	for (int i=0; vIt != vItEnd; ++vIt, ++i ) 
		{
		if ( bInsideRange ) 
			{
			if ( i > nRangeEnd ) bInsideRange = false;
			else sContent += sRangeDelim;
			}
			
		if ( ( i >= nRangeBegin ) && ( i <= nRangeEnd ) )
			{
			bInsideRange = true;
			}

		long nType = (*vIt)->UserSignGet();
		std::string sTemp = (*vIt)->UIFormat();
		std::string sPath;

		std::string sType = "missing";
		odb::CObject* poTempObject = 0;
		std::stringstream stStream;

		const std::string& sPrefix = (*vIt)->PrefixGet();
		const std::string& sSuffix = (*vIt)->SuffixGet();
	
		if ( sPrefix.length() )
			{
			if ( sPrefix.length() > 1 )
				if ( sPrefix[1] == '{' ) { sContent += (bInsideRange?ExplizitBegin(vEnclosings):""); ++nExplizit; }

			if ( sPrefix[0] == '{' ) { sContent += (bInsideRange?ExplizitBegin(vEnclosings):""); ++nExplizit; }
			if ( sPrefix[0] == ' ' ) sContent += (bInsideRange?Whitespace ( bKillNextWhitespace ):"");
			}

		switch ( nType )
			{
			case usersigns_objectlink:  sType = "link"; 
										sTemp = "";
										stStream << (*vIt)->UIFormat();
										int nObject;
										stStream >> nObject;
										poTempObject = roTemplate.GetODB()->Id2PtrObject ( nObject );
										if ( poTempObject )
											{
											sTemp = GetAllAtoms ( poTempObject, nModifier );
											}
										break;
			case usersigns_word:		sType = "word"; 
										if ( !nExplizit ) //which means that it's not explizit
											{
											bStatus = Modify ( sTemp, nModifier, bStatus );
											}
										break;
			case usersigns_path:		sType = "path";
										sPath = roTemplate.GetDefinition(definition_pathopen);
										sPath += sTemp;
										sPath += roTemplate.GetDefinition(definition_pathmiddle);
										sPath += sTemp;
										sPath += roTemplate.GetDefinition(definition_pathclose);
										sTemp = sPath;
										break;
			case usersigns_accent:		sType = "accent";
										if ( !nExplizit ) //which means that it's not explizit
											{
											int nCase = 0;

											switch ( nModifier )
												{
												case CEntryCommand::mod_lowercase: 
													nCase = utf_char_lowercase; 
													break;
												case CEntryCommand::mod_lowercase_firstupper: 
													nCase = bStatus?utf_char_lowercase:utf_char_uppercase; 
													break;
												case CEntryCommand::mod_uppercase: 
													nCase = utf_char_uppercase;
													break;
												case CEntryCommand::mod_uppercase_begin: 
													if ( (*vIt)->PrefixGet().length() )
														{
														if ( (*vIt)->PrefixGet()[0] == ' ' ) //so this is the beginning of a word
															{
															nCase = utf_char_uppercase;
															}
														else nCase = utf_char_lowercase;
														}												
													break;
												}
											sTemp = TexToUtfCode ( sTemp, nCase ); break;
											}
										else
											{
											sTemp = TexToUtfCode ( sTemp ); break;
											}
			case usersigns_number:		sType = "number"; break;
			case usersigns_comma:		sType = "comma"; break;
			case usersigns_dot: 	 	sType = "dot" ; break;
			case usersigns_opar:		sType = "opar"; break;
			case usersigns_epar:		sType = "epar"; break;
			case usersigns_latex:		sType = "latex";
									if ( roLatex.ElimWhitespace ( sTemp ) ) bKillNextWhitespace = true;
									if ( roLatex.IsEnclosing( sTemp ) )
										{
										POpenClose pOC = roLatex.GetEnclosing( sTemp );
										if ( pOC.second != enclosings_nothing )
											{
											vEnclosings.push_back ( pOC.second );
											}
										sContent += (bInsideRange?roTemplate.GetDefinition(pOC.first):"");
										continue;
										}
									else
										{
										sTemp = roLatex.Latex2Utf ( sTemp ); 
										}
									break;
			case usersigns_missing:     sType = "missing"; break;
			case usersigns_mathmode:    sType = "math"; break;
			default: sType = "word"; break;
			}

		

		
		sContent += (bInsideRange?sTemp:"");

		if ( sSuffix.length() )
			{
			if ( sSuffix[0] == ' ' ) sContent += (bInsideRange?Whitespace ( bKillNextWhitespace ):"");
			if ( sSuffix[0] == '}' ) { sContent += (bInsideRange?ExplizitEnd(vEnclosings):""); --nExplizit; }
			if ( sSuffix.length() > 1 )
				if ( sSuffix[1] == '}' ) { sContent += (bInsideRange?ExplizitEnd(vEnclosings):""); --nExplizit; }
			}
		}
	if ( bRangeEnd )
		{
		sContent += sRangeSuffix;
		}
	return sContent;
	}

std::string GetNthAtom ( odb::CObject* poObj, int nNumber )
	{
	odb::CVectorAtom vAtoms = poObj->AtomsGet ();
	
	odb::CVectorAtom::iterator vIt = vAtoms.begin();
	odb::CVectorAtom::iterator vItEnd = vAtoms.end();
	
	for ( int i = 1; vIt != vItEnd; ++i, ++vIt )
		{ 
		if ( i == nNumber ) return (*vIt)->UIFormat(); //TODO: Resolve link-atoms!
		}
	return "";
	}



bool ObjectIsEmpty ( odb::CObject* poObj )
	{
	if ( poObj->AtomsGet().begin() == poObj->AtomsGet().end() ) return true;
	return false;
	}

bool CheckObjectForAtoms ( odb::CObject* poObj, CVectorString vValues, int nSpecific )
	{
//	CDEBUG << "Checking if object with ID " << poObj->ID() << " (spec: " << nSpecific << ") contains " << std::flush;
	
 	odb::CVectorAtom vAtoms = poObj->AtomsGet ();
	
	odb::CVectorAtom::iterator vIt = vAtoms.begin();
	odb::CVectorAtom::iterator vItEnd = vAtoms.end();

	if (nSpecific == 0 )
		{
		std::string	sTemp = str_tolower ( strdup( GetAllAtoms(poObj).c_str() ) );

		CVectorString::iterator vStrIt    = vValues.begin();
		CVectorString::iterator vStrItEnd = vValues.end();
			
		for ( ; vStrIt != vStrItEnd; ++vStrIt )
			{
			if ( !(*vStrIt).length() ) continue;
			//std::cerr << "{" << (*vStrIt) << "}" << std::flush;
			if ( sTemp.find ( (*vStrIt) ) <= sTemp.length() ) return true; 
			}
		return false;
		}

	if (nSpecific == -1 )
		{
		for ( ; vIt != vItEnd; ++vIt )
			{
			//TODO: resolv link atoms too, also: 
			// if (usersign_link) CheckObjectForAtoms(odb.getobject(uiformat zu int), sContent)
			
			CVectorString::iterator vStrIt    = vValues.begin();
			CVectorString::iterator vStrItEnd = vValues.end();
				
			for ( ; vStrIt != vStrItEnd; ++vStrIt )
				{
				if ( !(*vStrIt).length() ) continue;

				std::string sTemp = str_tolower ( strdup((*vIt)->UIFormat().c_str()) );
				//std::cerr << "{ " << (*vStrIt) << " == " << sTemp << "}" << std::flush;

				if ( sTemp.find ( (*vStrIt) ) <= sTemp.length() ) { /*std::cerr << " <- it does! (Atom with ID: " 
				<< (*vIt)->ID() << ")" << std::endl;*/ return true; }
				}
			}
		//std::cerr << " <- nope" << std::endl;
		return false;
		}

	std::string	sTemp = str_tolower ( strdup( GetNthAtom ( poObj, nSpecific ).c_str() ) );

	CVectorString::iterator vStrIt    = vValues.begin();
	CVectorString::iterator vStrItEnd = vValues.end();
		
	for ( ; vStrIt != vStrItEnd; ++vStrIt )
		{
		if ( !(*vStrIt).length() ) continue;

		//std::cerr << "{" << (*vStrIt) << "}" << std::flush;
		if ( sTemp.find ( (*vStrIt) ) <= sTemp.length() ) return true; 
		}
	return false;

	}





void ReduceAndSort ( odb::CVectorRoot& vRoot, CConstraint& roConst, bool bSort, bool bSortOrder, CMapString2VectorRoot& mStr2Objects )
	{
//	CDEBUG << ((bSort)?"-> SORTING!":"") << std::endl;
	
	CTemplate& roTemplate = CTemplate::Instance();

	/*
	for ( odb::CVectorRoot::iterator vIt = vRoot.begin(); vIt != vRoot.end(); ++vIt )
		std::cerr << "[" << (*vIt) << "]" << std::flush;
	std::cerr << std::endl;
	*/

	typedef std::vector<odb::CVectorRoot::iterator> CVectorIterator;
	
	CVectorIterator vDeleteMe;

	
	odb::CVectorRoot::iterator vIt    = vRoot.begin();
	odb::CVectorRoot::iterator vItEnd = vRoot.end();


	std::string sTag = roConst.Name();

	bool bIsBibCat = false;
	bool bIsEmpty = false;
	bool bTagEmpty = false;
	
	
	CVectorString::iterator valIt    = roConst.Values().begin();
	CVectorString::iterator valItEnd = roConst.Values().end();


	int nEmpty = 0;

//	CDEBUG << "****************!! ((" << roConst.Values().size() << "))" << std::endl;
	
	for ( ; valIt != valItEnd; ++valIt )
		{
		//std::cerr << "{" << (*valIt) << "}[" << (*valIt).length() << "] " << std::flush;
		nEmpty += (*valIt).length()?0:1;
		}
	if ( nEmpty )
		{
		//std::cerr << " - YES!" << std::endl;
		bTagEmpty = true;
		}	
	//std::cerr << std::endl;
	

//	CDEBUG << " it is: [" << sTag << "]" << std::endl;
	if ( sTag[0] == '@' )
		{
//		CDEBUG << "Processing an @-condition!" << std::endl;
		sTag.erase(0,1);
		if ( sTag == "entry" ) bIsBibCat = true; //TODO case-insensitive!
		else { CERR << "FATAL: Only @entry recognized as @-condition!" << std::endl; return; }  
		}


	bool bBailOut = false;

	for ( ; vIt != vItEnd; ++vIt )
		{
		odb::CObject* poObj = dynamic_cast<odb::CObject*>(*vIt);

		int nContains = 0;
		bool bAttributeFound = false;
		std::string sFirstContent;

		if ( bIsBibCat )
			{
//			CDEBUG << "0K!" << std::flush;
			sFirstContent = poObj->NameGet();
			sFirstContent.erase(0,1);
			bAttributeFound = true;
			
			CMapString2String& mClasses = roTemplate.GetClasses();
			
			if ( mClasses.find ( sFirstContent ) != mClasses.end() )
				{
				sFirstContent = mClasses[sFirstContent];
				}
			
			
			CVectorString::iterator vsIt	= roConst.Values().begin();
			CVectorString::iterator vsItEnd = roConst.Values().end();
			
			for ( ; vsIt != vsItEnd; ++vsIt )
				{
				if ( sFirstContent.find ( *vsIt ) <= sFirstContent.length() ) ++nContains;
				}
			}
		else
			{
			odb::CMapChildren& mRef = const_cast<odb::CMapChildren&> ( poObj->ChildrenGet() );
		
			odb::CMapChildren::iterator mIt = mRef.begin();
			odb::CMapChildren::iterator mItEnd = mRef.end();

			for ( ; mIt != mItEnd; ++mIt )
				{
				if ( mIt->first->NameGet() != sTag )  continue;
			
				if ( !bAttributeFound ) 
					{
					bAttributeFound = true;
					sFirstContent = GetAllAtoms ( mIt->first );
					}


				if ( CheckObjectForAtoms ( mIt->first, roConst.Values(), roConst.Specific() ) ) 
					{
					//std::cerr << " - Check true - " << std::endl;
					++nContains;
					}
				//else std::cerr << " - Check false - " << std::endl;
				}
			}
		
		if ( !vRoot.size() ) { /*CDEBUG << "??" << std::endl;*/ bBailOut = true; break; }
		
		bIsEmpty = sFirstContent.length()?false:true;

//		std::cerr << std::endl << "##############################" << std::endl;
//		std::cerr << "(" << poObj->ID() << ")-[" << (bIsEmpty?"true":"false") << "][" << (bTagEmpty?"true":"false") << "]-{" << (bAttributeFound?"true":"false") << "} - (" << sFirstContent << ")" << std::endl;
//		std::cerr << "##############################" << std::endl;
	

		switch ( roConst.Operator() )
			{
			case compare_ignore: 
//				CDEBUG << "--" << std::endl; 
				if ( bSort ) mStr2Objects[sFirstContent].push_back(dynamic_cast<odb::CRoot*>(poObj));
				break;
			case compare_equals:
				if ( bIsEmpty && bTagEmpty ) { ++nContains; }
				if ( nContains ) 
					{
					if ( bSort ) mStr2Objects[sFirstContent].push_back(dynamic_cast<odb::CRoot*>(poObj));
					}
				else
					{
					//CDEBUG << "=-> " << poObj->ID() << std::endl;
					if ( !bSort ) vDeleteMe.push_back(vIt);
					}
				break;
			case compare_not_equal:
				if ( bIsEmpty && bTagEmpty ) { ++nContains; }
				if ( nContains ) 
					{
					//CDEBUG << "!=-> " << poObj->ID() << std::endl;
					if ( !bSort ) vDeleteMe.push_back(vIt);
					}
				else
					{
					if ( bSort ) mStr2Objects[sFirstContent].push_back(dynamic_cast<odb::CRoot*>(poObj));
					}
				break;
			case compare_exists:
				if ( bAttributeFound )
					{
					if ( bSort ) mStr2Objects[sFirstContent].push_back(dynamic_cast<odb::CRoot*>(poObj));
					}
				else
					{
					//CDEBUG << "E-> " << poObj->ID() << std::endl;
					if ( !bSort ) vDeleteMe.push_back(vIt);
					}
				break;
			default: break;
			};

		if ( bBailOut ) break;
		}

	if ( !bSort )
		{
		CVectorIterator::reverse_iterator delIt		= vDeleteMe.rbegin();
		CVectorIterator::reverse_iterator delItEnd  = vDeleteMe.rend();

		//CDEBUG << "Deleting: " << std::flush;
		for ( ; delIt != delItEnd; ++delIt )
			{
			//std::cerr << "(" << (*(*delIt))->ID() << std::flush;
			vRoot.erase ( *delIt );
			//std::cerr << ")" << std::flush;
			}
			//std::cerr << " finished!" << std::endl;
		}
	else
		{
		vRoot.clear();

		if ( bSortOrder == sortorder_dec )
			{	
			CMapString2VectorRoot::iterator mIt	= mStr2Objects.begin();
			CMapString2VectorRoot::iterator mItEnd	= mStr2Objects.end();
			for ( ; mIt != mItEnd; ++mIt )	
				{ 
				//std::cerr << "." << std::flush; 
				odb::CVectorRoot::iterator vOIt = (*mIt).second.begin();
				odb::CVectorRoot::iterator vOItEnd = (*mIt).second.end();
				
				for ( ; vOIt != vOItEnd; ++vOIt )
					vRoot.push_back ( dynamic_cast<odb::CObject*>(*vOIt) ); 
				}
			}
		else //uU verkehrt rum TODO
			{
			CMapString2VectorRoot::reverse_iterator mIt		= mStr2Objects.rbegin();
			CMapString2VectorRoot::reverse_iterator mItEnd	= mStr2Objects.rend();
			for ( ; mIt != mItEnd; ++mIt )	
				{ 
				//std::cerr << "-" << std::flush; 
				odb::CVectorRoot::iterator vOIt = (*mIt).second.begin();
				odb::CVectorRoot::iterator vOItEnd = (*mIt).second.end();
				
				for ( ; vOIt != vOItEnd; ++vOIt )
					vRoot.push_back ( dynamic_cast<odb::CObject*>(*vOIt) ); 
				}
			}		
		}

	/*
	for (odb::CVectorRoot::iterator vRIt = vRoot.begin(); vRIt != vRoot.end(); ++vRIt )
		std::cerr << "{" << (*vRIt)->NameGet() << ":" << (*vRIt)->ID() << "}" << std::flush;
	std::cerr << std::endl;
	*/
//	std::cerr << __PRETTY_FUNCTION__ << std::endl << "((" << vRoot.size() << ")), " << sAttrib << "{{"<<vValues.size()<<"}} " << nComp << std::endl;
	
	}




void DumpCommand ( CEntryCommand *poEntryCommand, odb::CObject* poObj )
	{
	//CDEBUG << "-{" << poEntryCommand->Dump() << "}" << std::endl;
	odb::CMapChildren& mRef = const_cast<odb::CMapChildren&> ( poObj->ChildrenGet() );

	odb::CMapChildren::iterator mIt = mRef.begin();
	odb::CMapChildren::iterator mItEnd = mRef.end();
	
	odb::CObject* poTag = 0;
	
	if ( poEntryCommand->Dump() == "$odbid" )
		{
		std::stringstream stStream;
		stStream << poObj->ID();
		std::string sNumber;
		stStream >> sNumber;
		Write ( sNumber );
		return;
		}
	if ( poEntryCommand->Dump() == "$bibkey" )
		{
        odb::CVectorAtom oVecAtomTemp = poObj->AtomGetBySign(usersigns_key);
		odb::CVectorAtom::iterator vAIt = oVecAtomTemp.begin();
        odb::CVectorAtom::iterator vAItEnd = oVecAtomTemp.end();

		if ( vAIt == vAItEnd ) return;
		
		Write ( (*vAIt)->UIFormat() );
		return;
		}
	if ( poEntryCommand->Dump() == "$bibtype" )
		{
		Write ( poObj->NameGet() );
		return;
		}
	
	
	
	
	//TODO specific!!!
	
	for ( ; mIt != mItEnd; ++mIt )
		{
		if ( mIt->first->NameGet() == poEntryCommand->Dump() ) 
			{ 
			poTag = mIt->first;
			break;
			}
		if ( !mIt->first->ClassGet() ) { CERR << "no Class!" << std::endl; continue; }
		if ( mIt->first->ClassGet()->NameGet() == poEntryCommand->Dump() )
			{
			poTag = mIt->first;
			break;
			}
		}

	if ( poTag ) Write ( GetAllAtoms ( poTag, poEntryCommand->GetModifier() ) );
	else CERR << "-> object not found" << std::endl;

	}


void ProcessConstraints ( CEntryRoot* poEntryRoot, odb::CVectorRoot& voObjectRoot, CMapString2VectorRoot& mStr2Objects )
	{
	CListString::iterator lIt    = poEntryRoot->GetConditions().begin();
	CListString::iterator lItEnd = poEntryRoot->GetConditions().end();
	
	CVectorConstraint::reverse_iterator cIt    = poEntryRoot->GetConstraints().rbegin();
	CVectorConstraint::reverse_iterator cItEnd = poEntryRoot->GetConstraints().rend();
	
	const bool bCondition = (lIt==lItEnd)?false:true;
	
	for (int i = poEntryRoot->GetConstraints().size(); cIt != cItEnd; ++cIt, --i )
		{
		if ( ( i == 1 ) && !bCondition ) ReduceAndSort ( voObjectRoot, (*cIt), true, poEntryRoot->GetSortOrder ( ), mStr2Objects );
		else ReduceAndSort ( voObjectRoot, (*cIt), false, false, mStr2Objects );
		}
		
	for ( int i = poEntryRoot->GetConditions().size(); lIt != lItEnd; ++lIt, --i )
		{
		std::string sTemp = (*lIt);
		CConstraint oConstraint ( sTemp, '0', compare_exists );
		if ( i == 1 ) ReduceAndSort ( voObjectRoot, oConstraint, true, poEntryRoot->GetSortOrder ( ), mStr2Objects );
		else ReduceAndSort ( voObjectRoot, oConstraint, false, false, mStr2Objects );
		}
	}

void DumpFor ( CEntryRootFor* poEntryRootFor, odb::CVectorRoot voObjectRoot )
	{
	if ( !poEntryRootFor ) { CERR << "PANIK! poEntryRootFor nil" << std::endl; exit(1); }
	
	CMapString2VectorRoot mStr2Objects;

	ProcessConstraints ( dynamic_cast<CEntryRoot*>(poEntryRootFor), voObjectRoot, mStr2Objects );

	odb::CVectorRoot::iterator vIt    = voObjectRoot.begin();
	odb::CVectorRoot::iterator vItEnd = voObjectRoot.end();
	
	for ( ; vIt != vItEnd; ++vIt )
		{
		odb::CObject* poObj = dynamic_cast<odb::CObject*>(*vIt);
		
		CEntryRoot::iterator eIt	= poEntryRootFor->begin();
		CEntryRoot::iterator eItEnd = poEntryRootFor->end();
	
		for ( ; eIt != eItEnd; ++eIt )
			{
			CEntry* poEntry = (*eIt);

			switch ( poEntry->Rtti() )
				{			
				case CEntryRootFor::rtti:
					CERR << "Nested %%FOR%%s have no effect!" << std::endl;
					break;
					
				case CEntryRootGroup::rtti:
					CERR << "%%GRP%% inside of %%FOR%% has no effect!" << std::endl;
					break;
				
				case CEntryRootBib::rtti:	
					DumpBib ( dynamic_cast<CEntryRootBib*>(poEntry), poObj );
					break;

				case CEntryRoot::rtti:
					CERR << "PANIK! EntryRoot impossible at that level" << std::endl;	
					return;
					break;
				
				case CEntryText::rtti:	
					Write ( poEntry->Dump() );
					break;
				
				case CEntryCommand::rtti:
					DumpCommand ( dynamic_cast<CEntryCommand*>(poEntry), poObj );
					break;

				case CEntryRootReduce::rtti:
					CERR << "This is not the right place for a %%REDUCE%%" << std::endl;
					break;

				default:
					CERR << "PANIK: Unknown rtti!" << std::endl;
					return;	
					break;
				}
			}
	
		}
	}


void DumpGroup ( CEntryRootGroup* poEntryRootGroup, odb::CVectorRoot voObjectRoot )
	{
	if ( !poEntryRootGroup ) { CERR << "PANIK! poEntryRootGroup nil" << std::endl; exit(1); }
	
	CMapString2VectorRoot mStr2Objects;
	ProcessConstraints ( dynamic_cast<CEntryRoot*>(poEntryRootGroup), voObjectRoot, mStr2Objects );

	CMapString2VectorRoot::iterator mIt    = mStr2Objects.begin();
	CMapString2VectorRoot::iterator mItEnd = mStr2Objects.end();

	for ( ; mIt != mItEnd; ++mIt )
		{
		CEntryRoot::iterator eIt	= poEntryRootGroup->begin();
		CEntryRoot::iterator eItEnd = poEntryRootGroup->end();

		for ( ; eIt != eItEnd; ++eIt )
			{
			CEntry* poEntry = (*eIt);

			switch ( poEntry->Rtti() )
				{			
				case CEntryRootFor::rtti:
					DumpFor ( dynamic_cast<CEntryRootFor*>(poEntry), mIt->second );
					break;
					
				case CEntryRootGroup::rtti:
					DumpGroup ( dynamic_cast<CEntryRootGroup*>(poEntry), mIt->second );
					break;
				
				case CEntryRootBib::rtti:
					CERR << "%%BIB%% does not make any sense at that level!" << std::endl;
					break;

				case CEntryRoot::rtti:
					CERR << "PANIK!" << std::endl;	
					return;
					break;
				
				case CEntryText::rtti:	
					Write ( poEntry->Dump() );
					break;
				
				case CEntryCommand::rtti:
					if ( poEntry->Dump() == "name" )
						{
						std::string sName = mIt->first;
						Modify ( sName, dynamic_cast<CEntryCommand*>(poEntry)->GetModifier(), false );
						Write ( sName );
						}
					else CERR << "Only command %%name%% recognized at that level!" << std::endl;
					break;

				case CEntryRootReduce::rtti:
					DumpReduce ( dynamic_cast<CEntryRootReduce*>(poEntry), mIt->second ); 
					break;

				default:
					CERR << "PANIK: Unknown rtti!" << std::endl;
					return;	
					break;
				}
			}
		}
	}





void DumpReduce ( CEntryRootReduce* poEntryRootReduce, odb::CVectorRoot& voObjectRoot )
	{
	if ( !poEntryRootReduce ) { CERR << "PANIK! poEntryRootFor nil" << std::endl; exit(1); }
	
	CMapString2VectorRoot mStr2Objects;

	ProcessConstraints ( dynamic_cast<CEntryRoot*>(poEntryRootReduce), voObjectRoot, mStr2Objects );
	}









void DumpTag ( CEntryRootBib* poEntryRootBib, odb::CObject* poTag, int nToken )
	{
//	CDEBUG << std::flush;
	if ( poTag->ClassGet() )
		{
		if ( poTag->ClassGet()->NameGet() != "Tag" ) return;
		}
//	std::cerr << "ok[" << nToken << "]" << std::flush;
	
	CVectorEntries::iterator eIt	= poEntryRootBib->begin(nToken);
	CVectorEntries::iterator eItEnd = poEntryRootBib->end(nToken);

	for ( ; eIt != eItEnd; ++eIt )
		{

		CEntry* poEntry = (*eIt);
//		std::cerr << ".(" << poEntry->Rtti() << ")->" << "[" << poEntry->Dump() << "]" << std::flush;

		switch ( poEntry->Rtti() )
			{			
			case CEntryRootFor::rtti:
				CERR << "%%FOR%% does not make any sense inside %%BIB%%!" << std::endl;
				break;
				
			case CEntryRootGroup::rtti:
				CERR << "%%GRP%% does not make any sense inside %%BIB%%!" << std::endl;
				break;
			
			case CEntryRootBib::rtti:
				CERR << "PANIK! IMPOSSIBLE!!" << std::endl;
				break;

			case CEntryRoot::rtti:
				CERR << "PANIK!" << std::endl;	
				return;
				break;

			case CEntryRootReduce::rtti:
				CERR << "%%REDUCE%% does not make any sense inside %%BIB%%!" << std::endl;
				break;

			case CEntryText::rtti:	
				Write ( poEntry->Dump() );
				break;
			
			case CEntryCommand::rtti:

				if ( poEntry->Dump() == "name" ) 
					{
					std::string sName = poTag->NameGet();
					Modify ( sName, dynamic_cast<CEntryCommand*>(poEntry)->GetModifier(), false );
					Write ( sName );
					break; 
					}
				if ( poEntry->Dump() == "content" ) 
					{ 
					Write ( GetAllAtoms ( poTag, dynamic_cast<CEntryCommand*>(poEntry)->GetModifier() ) ); 
					break; 
					}
				if ( poEntry->Dump() == "step" )
					{
					CEntryCommand* poCommand = dynamic_cast<CEntryCommand*>(poEntry);
					Write ( GetAllAtoms ( poTag, poCommand->GetModifier(), 
										  poCommand->GetRangeBegin(), poCommand->GetRangeEnd(), 
										  poCommand->GetPrefix(), poCommand->GetDelim(), poCommand->GetSuffix() )); }
				else CERR << "Command " << poEntry->Dump() << " read. Only %%name%% and %%content%% are recognized" << std::endl;
				break;

			default:
				CERR << "PANIK: Unknown rtti!" << std::endl;
				return;	
				break;
			}
		}
	//std::cerr << std::endl;
	}


bool IncludeBib ( CEntryRootBib* poEntryRootBib, odb::CObject* poTag )
	{
	bool bInclude = true;
	
	if ( poEntryRootBib->GetConstraints().size() )
		{
		CVectorConstraint::iterator vcIt    = poEntryRootBib->GetConstraints().begin();
		CVectorConstraint::iterator vcItEnd = poEntryRootBib->GetConstraints().end();

		for ( ; vcIt != vcItEnd; ++vcIt )
			{
			if ( (*vcIt).Name() == poTag->NameGet() )
				{

				bool bFound = false;
				if ( CheckObjectForAtoms ( poTag, (*vcIt).Values(), (*vcIt).Specific() ) ) bFound = true;
				
				switch ( (*vcIt).Operator() )
					{
					case compare_equals:

						bInclude = bFound;
						break;

					case compare_not_equal:
					default:
						bInclude = !bFound;
						break;
					}
				break;
				}
			}
		}
	else
		return true;
	return bInclude;
	}



void DumpBib ( CEntryRootBib* poEntryRootBib, odb::CObject* poObj )
	{
//	CDEBUG << "-> ok" << std::endl;

	typedef std::map<std::string, odb::CObject*> CMapString2Object;
	CMapString2Object mString2Object;
	
	odb::CMapChildren& mRef = const_cast<odb::CMapChildren&> ( poObj->ChildrenGet() );
		
	odb::CMapChildren::iterator mIt = mRef.begin();
	odb::CMapChildren::iterator mItEnd = mRef.end();
			
//	std::cerr << "Pushing:" << std::flush; bool bFirst = true;
	for ( ; mIt != mItEnd; ++mIt )
		{
//		std::cerr << (bFirst?" ":", ") << string2lower(mIt->first->NameGet()) << std::flush; bFirst = false;
		mString2Object[string2lower(mIt->first->NameGet())] = mIt->first;
		}
//	std::cerr << std::endl;
	
	CVectorString::iterator vIt	   = poEntryRootBib->GetIncludes().begin();
	CVectorString::iterator vItEnd = poEntryRootBib->GetIncludes().end();
	
	for ( ; vIt != vItEnd; ++vIt )
		{
//		CDEBUG << "Processing Include: {" << (*vIt) << "}" << std::flush;
		CMapString2Object::iterator mChildIt = mString2Object.find(string2lower(*vIt));
		if ( mChildIt != mString2Object.end() )
			{
			odb::CObject* poTag = mChildIt->second;
			int nToken = 0;
			if ( ObjectIsEmpty( poTag ) ) nToken = bibtoken_empty;
			else nToken = bibtoken_nonempty;
			if ( IncludeBib ( poEntryRootBib, poTag ) )
				{
				DumpTag ( poEntryRootBib, poTag, nToken );
				}
			mString2Object.erase(mChildIt);
			}
		else
			{
//			std::cerr << " - not found - " << std::flush;
			odb::CObject oObject ( _TEXT(*vIt) );
//			std::cerr << " - created object - " << std::flush;
			DumpTag ( poEntryRootBib, &oObject, bibtoken_missing );
			}
//		std::cerr << " ok." << (*vIt) << std::endl;

		}
	if ( poEntryRootBib->IsExclusive() ) 
		{
//		CDEBUG << "-> finished." << std::endl;
		return;
		}
					
	if ( poEntryRootBib->GetSortOrder()  == sortorder_inc )
		{	
		CMapString2Object::iterator mChildrenIt    = mString2Object.begin();
		CMapString2Object::iterator mChildrenItEnd = mString2Object.end();

		for ( ; mChildrenIt != mChildrenItEnd; ++mChildrenIt )
			{
			odb::CObject* poTag = mChildrenIt->second;
			
			int nToken = 0;
			if ( ObjectIsEmpty( poTag ) ) nToken = bibtoken_empty;
			else nToken = bibtoken_generic;

			
			//TODO check here if there are constraints and such.
			if ( poEntryRootBib->GetExcludes().find ( poTag->NameGet() ) != poEntryRootBib->GetExcludes().end() ) continue;

			if ( IncludeBib ( poEntryRootBib, poTag ) )
				{
				DumpTag ( poEntryRootBib, poTag, nToken );
				}
			}
		}
	else 
		{	
		CMapString2Object::reverse_iterator mChildrenIt    = mString2Object.rbegin();
		CMapString2Object::reverse_iterator mChildrenItEnd = mString2Object.rend();

		for ( ; mChildrenIt != mChildrenItEnd; ++mChildrenIt )
			{
			odb::CObject* poTag = mChildrenIt->second;
			
			int nToken = 0;
			if ( ObjectIsEmpty( poTag ) ) nToken = bibtoken_empty;
			else nToken = bibtoken_generic;
			
			//TODO check here if there are constraints and such.
			if ( poEntryRootBib->GetExcludes().find ( poTag->NameGet() ) != poEntryRootBib->GetExcludes().end() ) continue;

			if ( IncludeBib ( poEntryRootBib, poTag ) )
				{		
				DumpTag ( poEntryRootBib, poTag, nToken );
				}
			}
		}		
	}



	
void DumpRoot ( CEntryRoot* poEntryRoot, odb::CVectorRoot voObjectRoot )
	{
	//CDEBUG << std::endl;
	if ( !poEntryRoot ) { CERR << "WAAAAAAAAAS" << std::endl; return; }
	CEntryRoot::iterator eIt	= poEntryRoot->begin();
	CEntryRoot::iterator eItEnd = poEntryRoot->end();
	
	for ( ; eIt != eItEnd; ++eIt )
		{
		CEntry* poEntry = (*eIt);

		switch ( poEntry->Rtti() )
			{
			case CEntryRootFor::rtti:	
				DumpFor ( dynamic_cast<CEntryRootFor*>(poEntry), voObjectRoot ); 
				break;
			
			case CEntryRootGroup::rtti: 
				DumpGroup ( dynamic_cast<CEntryRootGroup*>(poEntry), voObjectRoot ); 
				break;
			
			case CEntryRootBib::rtti:	
				CERR << "%%BIB%% makes no Sense here" << std::endl; 
				break;
			
			case CEntryRoot::rtti:		
				CERR << "MILD PANIK!" << std::endl; 
				return; 

			case CEntryRootReduce::rtti:
				DumpReduce ( dynamic_cast<CEntryRootReduce*>(poEntry), voObjectRoot ); 
				break;
		
			case CEntryCommand::rtti:
				if ( true ) { //damn "case crosses initialization of..
				std::string sTemp = poEntry->Dump();
				Modify ( sTemp, dynamic_cast<CEntryCommand*>(poEntry)->GetModifier(), false );
				Write ( sTemp ); break;
				}
			default:					
				Write ( poEntry->Dump() ); break;
			}
		}
	}


int CTemplate::BeginParse ( FILE* pfTemplate, std::string sConstraints )
	{
	//CDEBUG << std::endl;
//templatedebug=1;
 	if ( !m_bIsValid ) return -1;
	if ( !pfTemplate ) return -2;

	if ( sConstraints.size() )
		{
		sConstraints = "%%RED%%(inc:" + sConstraints + ")";
		/*char *csTemp = strdup(sConstraints.c_str());
		std::cerr << "Using " << csTemp << std::endl;
		FILE* pfTemp = fopen(csTemp, "rs");
		std::cerr << "File is " << (int)pfTemp << std::endl;
		templaterestart ( pfTemp );
		*/
		template_scan_string(sConstraints.c_str());
		int nRetTemp = templateparse ( );
		if ( nRetTemp )
			{
			CERR << "Error parsing command-line supplied constraints." << std::endl;
			}
		//int nRetTemp = templateparse ( );
		}
	std::cerr << "Continuing parsing..." << std::endl;			
	templaterestart ( pfTemplate );
	int nRet;
	nRet = templateparse ( );
	
	
	odb::CVectorRoot vClass = m_poODB->GetClass ( _TEXT("Entry") );
	
	odb::CVectorRoot::iterator vIt = vClass.begin();
	if ( vIt == vClass.end() ) return -1;
	
	odb::CListObject lObject = dynamic_cast<odb::CClass*>(*vIt)->ObjectsGet();
	
	odb::CListObject::iterator lIt = lObject.begin();
	odb::CListObject::iterator lItEnd = lObject.end();
	
	odb::CVectorRoot vAnswerSet;
	
	for ( ;lIt != lItEnd; ++lIt )
		{
		odb::CRoot* poRoot = dynamic_cast<odb::CRoot*>(*lIt);
		if ( poRoot ) vAnswerSet.push_back(poRoot);
		}
	

	if ( nRet )
		{
		CERR << "Parse error" << std::endl;
		}
	else
		{
		DumpRoot ( m_poCurrentRoot, vAnswerSet );
		}

	return nRet;
	}



void CTemplate::BibBegin() 
	{
	//CDEBUG << "-> ok" << std::endl;
	m_vValues.clear();
	CEntryRoot* poNewRoot = dynamic_cast<CEntryRoot*>(new CEntryRootBib ( m_poCurrentRoot ));
	m_poCurrentRoot->Push ( poNewRoot );
	m_poCurrentRoot = poNewRoot;
	}

void CTemplate::BibEnd() 
	{
	//CDEBUG << "-> ok" << std::endl;
	m_poCurrentRoot = m_poCurrentRoot->GetParent();
	}
	

	

void CTemplate::SetToken  ( int nNumber )
	{
	//CDEBUG << std::endl;
	if ( m_poCurrentRoot->Rtti() == CEntryRootBib::rtti )
		dynamic_cast<CEntryRootBib*>(m_poCurrentRoot)->SetToken ( nNumber );
	}


void CTemplate::Exclusive ( std::string sExcl ) 
	{ 
	//CDEBUG << std::endl;
	if ( m_poCurrentRoot->Rtti() == CEntryRootBib::rtti )
		{
		CEntryRootBib* poCurrentRoot = dynamic_cast<CEntryRootBib*>(m_poCurrentRoot);
		poCurrentRoot->PushInclusion (sExcl ); 
		poCurrentRoot->SetExclusive ( ); 
		}
	}
	
void CTemplate::Exclusion ( std::string sExcl ) 
	{ 
	//CDEBUG << std::endl;
	if ( m_poCurrentRoot->Rtti() == CEntryRootBib::rtti )
		dynamic_cast<CEntryRootBib*>(m_poCurrentRoot)->PushExclusion (sExcl); 
	}
void CTemplate::Inclusion ( std::string sIncl ) 
	{ 
	//CDEBUG << std::endl;
	if ( m_poCurrentRoot->Rtti() == CEntryRootBib::rtti )
		dynamic_cast<CEntryRootBib*>(m_poCurrentRoot)->PushInclusion (sIncl); 
	}

void CTemplate::DefFinish ( std::string sNumber ) 
	{
	//CDEBUG << std::endl;
	sNumber.erase(0,8);
	sNumber.erase(sNumber.length()-1,1);
	
	std::stringstream stStream;
	stStream << sNumber;
	int nNumber;
	stStream >> nNumber;
	
	m_mDefines[nNumber] = m_sDefine;
	m_sDefine="";
	}


void CTemplate::AddDefinition ( std::string sDef )
	{
	//CDEBUG << std::endl;
	m_sDefine += sDef;
	}
	
	
	
void CTemplate::AddClass ( std::string sClass )
	{
	//CDEBUG << sClass << std::endl;
	sLastClass = sClass;
	}
	
void CTemplate::AddMember ( std::string sMember )
	{
	//CDEBUG << sMember << std::endl;
	m_mClasses[sMember] = sLastClass;
	}
	
void CTemplate::Modifier ( std::string sMod, std::string sCommand )
	{
	//CDEBUG << "{" << sCommand << "<---- " << sMod << "}" << std::endl;
	
	Command ( sCommand, sMod[6], sMod[7] );
	}
	
void CTemplate::Step ( std::string sCommand, std::string sPrefix, std::string sDelim, std::string sSuffix, std::string sMod )
	{
	std::string sName = sCommand.substr ( 0, sCommand.find(":") );
	
	std::string sRange = sCommand.substr ( sName.length()+1, std::string::npos );
	sName = sName + "%%"; //TODO das ist ja nicht mein ernst - das %%-erasen bitte ins .y verschieben!! GANZ WICHTIG!

	std::string sBegin = sRange.substr ( 0, sRange.find("-"));
	std::string sEnd = sRange.substr ( sBegin.length()+1, std::string::npos );
	
	int nBegin;
	int nEnd;
	

	
	if ( sBegin[0] == 'x' ) nBegin = 0;
	else
		{
		std::stringstream stStream;
		stStream << sBegin;
		stStream >> nBegin;
		}

	if ( sEnd[0] == 'x' ) nEnd = std::numeric_limits<int>::max();
	else
		{
		std::stringstream stStream;
		stStream << sEnd;
		stStream >> nEnd;
		}
	
	if ( nBegin > nEnd )
		{
		CWARN << "reversing Range" << std::endl;
		int nTemp = nBegin;
		nBegin = nEnd;
		nEnd = nTemp;
		}
	
	std::cerr << ">>> " << sName << " -->" << sPrefix << ";" << sDelim <<";" << sSuffix << "<-- Range: (" << nBegin << "-" << nEnd << ")" << std::endl;
	
	CEntryCommand* poCommand = 0;
	if ( sMod.length() ) poCommand = Command ( sName, sMod[6], sMod[7] );
	else poCommand = Command ( sName );
	poCommand->SetRange ( nBegin, nEnd, sPrefix, sDelim, sSuffix );
	
	}
	
	

//{ std::cerr << __PRETTY_FUNCTION__ << ":" << __LINE__ << " -> PANIK!" << std::endl; exit(1);}
