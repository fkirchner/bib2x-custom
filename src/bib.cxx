#include <iostream>
#include <string>

#include "bib.h"

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include "generic.h"
#include "odb.h"

using namespace odb;


void print_depth ( int nDepth ) { if ( nDepth < 1 ) return; print_depth(nDepth-1); std::cout << " "; }
void CBib::pd ( ) { if ( IsVerbose() ) { print_depth ( (m_nDepth)*5 ); } }


bool CBib::ProcessUmlauts ( )
	{
	return true;
	}


odb::CObject* CBib::ProcessAuthor ( std::string sAuthor )
	{
	
	std::string sLast;
	std::string sFirst;
	std::string sMiddle;
	std::string sAdd;
	
	unsigned int nJunior = sAuthor.find(", Jr.");
	if ( nJunior < sAuthor.length() ) 
		{ 
		sAdd = "Jr."; 
		sAuthor.replace ( nJunior, 5, ""); 
		}
	else 
		{
		nJunior = sAuthor.find(" Jr.");
		if ( nJunior < sAuthor.length() ) 
			{ 
			sAdd = "Jr."; 
			sAuthor.replace ( nJunior, 4, ""); 
			}  
		}
	
	unsigned int nComma = sAuthor.find(",");
	if ( nComma < sAuthor.length() )
		{
		sLast = sAuthor.substr ( 0, nComma );
		sAuthor.replace ( 0, nComma+2, "" );
		}
	else
		{
		unsigned int nLast = sAuthor.rfind (" ");
		if ( nLast > sAuthor.length() ) 
			{
			sLast = sAuthor;
			sAuthor = "";
			}
		else
			{
			sLast = sAuthor.substr ( nLast+1, sAuthor.length() );
			sAuthor.replace ( nLast, sAuthor.length()-nLast, "" ); 
			
			nLast = sAuthor.rfind(" ");
			if ( nLast < sAuthor.length() )
				{
				if ( nLast+1 < sAuthor.length() )
					{
					if ( islower((int)sAuthor[nLast+1]) )
						{
						sLast = sAuthor.substr(nLast+1, sAuthor.length() ) + " " + sLast;
						sAuthor.replace ( nLast, sAuthor.length()-nLast, "" ); 
						}
					}
				}
			}
		}
	
	unsigned int nSpace;
	
	nSpace = sAuthor.find(" ");
	
	if ( nSpace < sAuthor.length() )
		{
		sFirst = sAuthor.substr( 0, nSpace );
		sAuthor.replace ( 0, nSpace+1, "");
		}
	else
		{
		sFirst = sAuthor;
		sAuthor = "";
		}

	
	nSpace = sAuthor.find(" ");
	for (bool bSpace = false; nSpace < sAuthor.length(); nSpace = sAuthor.find(" ") )
		{
		sMiddle += (bSpace?" ":"") + sAuthor.substr(0,nSpace);
		sAuthor.replace(0,nSpace+1,"");
		}
	sMiddle = sMiddle + ((sMiddle.length()>0)?" ":"") + sAuthor;
	
	
	std::string sName = sLast + ((sLast.length()>0)?", ":"") + sFirst + ((sFirst.length()>0)?" ":"") 
							  + sMiddle + ((sMiddle.length()>0)?", ":"") + sAdd;

	odb::CVectorRoot vObj = odb.GetObject ( sName );
	if ( vObj.begin() != vObj.end() )
		{
		std::cerr << sName << " is known, not adding again" << std::endl;
		return dynamic_cast<odb::CObject*>(*vObj.begin());
		}

	odb::CObject* poObject = odb.NewObject ( sName, m_mName2Class["Author"] );
	
	odb::CAtom* poAtom = 0;
	if ( sFirst.length() )  { poAtom = odb.NewAtom ( _TEXT("First Name") );  *poAtom = sFirst;	poObject->AtomAdd(poAtom);}
	if ( sLast.length() )   { poAtom = odb.NewAtom ( _TEXT("Last Name") );   *poAtom = sLast;	poObject->AtomAdd(poAtom);}
	if ( sMiddle.length() ) { poAtom = odb.NewAtom ( _TEXT("Middle Name") ); *poAtom = sMiddle; poObject->AtomAdd(poAtom);}
	if ( sAdd.length() )	{ poAtom = odb.NewAtom ( _TEXT("Addition") );	 *poAtom = sAdd;	poObject->AtomAdd(poAtom);}
	
	return poObject;
	}

bool CBib::ProcessAuthors ( )
	{
	odb::CVectorRoot vAuthors = odb.GetObject ( _TEXT("author") );
	
	odb::CVectorRoot::iterator vOIt		= vAuthors.begin();
	odb::CVectorRoot::iterator vOItEnd	= vAuthors.end();
	
	bool bExplizit = false;
	
	odb::CReason* poReasonParent = m_mName2Reason["p: e->a"];
	odb::CReason* poReasonChild  = m_mName2Reason["c: a->e"];
	
	
	
	for ( ; vOIt != vOItEnd; ++vOIt )
		{
		
		CMapReferencing mParents = dynamic_cast<CObject*>(*vOIt)->ParentsGet();
		
		if ( mParents.begin() == mParents.end() ) continue;
		
		if ( IsVerbose() ) std::cerr << "Authors Mutter: " << mParents.begin()->first->NameGet() << " ("   
										<< mParents.begin()->first->ID() << ")" << std::endl;
		
		
		CVectorAtom vAtoms = dynamic_cast<CObject*>(*vOIt)->AtomsGet();
		
		CVectorAtom::iterator vAIt		= vAtoms.begin();
		CVectorAtom::iterator vAItEnd	= vAtoms.end();
		
		std::string sAuthor;
		
		std::string sLastSuffix = "";
		for ( ; vAIt != vAItEnd; ++vAIt )
			{
			std::string sPrefix = (*vAIt)->PrefixGet();
			std::string sSuffix = (*vAIt)->SuffixGet();
		

		
			if ( sPrefix.find( "{" ) < sPrefix.length() ) bExplizit = true;
			if ( sPrefix.find( " " ) < sPrefix.length() ) { if ( sAuthor.length() ) sAuthor += " "; }
			std::string sContent = (*vAIt)->UIFormat();

			if ( !bExplizit )	
				{
				if ( strcasecmp( sContent.c_str(), "and" ) == 0 ) 
					{
					CObject* poObject = ProcessAuthor ( sAuthor );
					
					if ( poObject )
						{
						CObject* poParent = dynamic_cast<CObject*>(mParents.begin()->first);
						if ( !poParent->Link ( poObject, poReasonParent ) ) 
							{
							std::cerr << "PARENTAUTHOR NOT LINKED!"<<std::endl;
							std::cerr << poParent->ClassGet()->NameGet() << "->" << poObject->ClassGet()->NameGet() << std::endl;
							}
						if ( !poObject->Link ( poParent, poReasonChild  ) ) 
							{
							std::cerr << "CHILDAUTHOR NOT LINKED!"<<std::endl;
							std::cerr << poParent->ClassGet()->NameGet() << "<-" << poObject->ClassGet()->NameGet() << std::endl;
							}
						}
					sAuthor = "";
					sContent = "";
					}
				
				}
			
			if ( sAuthor.length() ) sAuthor += sLastSuffix;
			sLastSuffix = "";
			
			sAuthor += sContent;
			
			if ( sSuffix.find( " " ) < sSuffix.length() ) sLastSuffix = " "; 
			if ( sSuffix.find( "}" ) < sSuffix.length() ) bExplizit = false; 
			}

		if ( sAuthor.length() )
			{
			CObject* poObject = ProcessAuthor ( sAuthor );
			if ( poObject )
				{
				CObject* poParent = dynamic_cast<CObject*>(mParents.begin()->first);
				poParent->Link ( poObject, poReasonParent );
				poObject->Link ( poParent, poReasonChild  );
				}
			}
		}

	return true;
	}

bool CBib::PostProcess ( )
	{
	int nRet = 0;
	nRet += ProcessUmlauts()?0:1;
	nRet += ProcessAuthors()?0:1;
	
	return (nRet==0);
	}



CBib::CBib() :	m_nDepth(0), m_nAtoms(0)
	{ 
	CClass *e, *t, *x, *m, *a;
	
	m_mName2Class["Entry"]    = e = odb.NewClass (_TEXT("Entry"));
	m_mName2Class["Tag"]      = t = odb.NewClass (_TEXT("Tag"));
	m_mName2Class["Explizit"] = x = odb.NewClass (_TEXT("Explizit"));
	m_mName2Class["Meta"]     = m = odb.NewClass (_TEXT("Meta"));
	m_mName2Class["Author"]   = a = odb.NewClass (_TEXT("Author"));
	


	m_mName2Reason["p: t->e"] = odb.NewReason(_TEXT("Parent"), t, e );
	m_mName2Reason["c: e->t"] = odb.NewReason(_TEXT("Child"), e, t );

	m_mName2Reason["p: t->m"] = odb.NewReason(_TEXT("Parent"), t, m );
	m_mName2Reason["c: m->t"] = odb.NewReason(_TEXT("Child"), m, t );

	m_mName2Reason["p: x->m"] = odb.NewReason(_TEXT("Parent"), x, m );
	m_mName2Reason["c: m->x"] = odb.NewReason(_TEXT("Child"), m, x );

	m_mName2Reason["p: m->m"] = odb.NewReason(_TEXT("Parent"), m, m );
	m_mName2Reason["c: m->m"] = odb.NewReason(_TEXT("Child"), m, m );

	m_mName2Reason["p: x->e"] = odb.NewReason(_TEXT("Parent"), x, e );
	m_mName2Reason["c: e->x"] = odb.NewReason(_TEXT("Child"), e, x );
	
	m_mName2Reason["p: x->t"] = odb.NewReason(_TEXT("Parent"), x, t );
	m_mName2Reason["c: t->x"] = odb.NewReason(_TEXT("Child"), t, x );
	
	m_mName2Reason["p: x->x"] = odb.NewReason(_TEXT("Parent"), x, x );
	m_mName2Reason["c: x->x"] = odb.NewReason(_TEXT("Child"), x, x );

	m_mName2Reason["p: e->a"] = odb.NewReason(_TEXT("Parent"), e, a );
	m_mName2Reason["c: a->e"] = odb.NewReason(_TEXT("Child"),  a, e );

	
	m_bVerbose = false;
	m_bNextPrefix = false;
	m_bBeginExplizit = false;
	m_bEndExplizit = false;
	m_poLastAtom = 0;
	
	m_nDepth = 0;
	}


void CBib::ExplizitIn (  ) 
	{
	m_poLastAtom = 0;
	
//x1	if ( IsVerbose() ) std::cout << std::endl;
//x1	pd();
//x1	if ( IsVerbose() ) std::cout << "New Explizit Object" << std::endl;
//x1	CreateObject ( "UnnamedExplizit", "Explizit", objects_explizit );

	if ( !m_nDepth ) m_bBeginExplizit=true;
	++m_nDepth;
//x1	pd();
//x1	if ( IsVerbose() ) std::cout << "{" << std::endl;
	}
void CBib::ExplizitOut (  )
	{
//x1	pd();
//x1	if ( IsVerbose() ) std::cout << "}" << std::endl;
	--m_nDepth;
	if ( !m_nDepth ) m_bEndExplizit=true;
	}
void CBib::ExplizitFinish (  bool bWhite )
    {
//x1	pd(); 
	
	
	if ( m_bEndExplizit )
		{
		m_bEndExplizit = false;
		if ( m_poLastAtom )
			{
			std::string sTemp = m_poLastAtom->SuffixGet();
			sTemp += "}";
			m_poLastAtom->SuffixSet ( sTemp );
			}
		m_poLastAtom = 0;
		}
	m_bNextPrefix=bWhite;
	
	//TODO check
//x1	CObject* poCurrentObject = m_vObjects.back()->poObject;
	
//x1	long lId = poCurrentObject->ID();
	
//x1	FinishObject ( "Explizit", objects_explizit );
//x1	poCurrentObject = m_vObjects.back()->poObject;

//x1	pd();
//x1	
//x1	CAtom* poAtom = odb.NewAtom ( _TEXT("Link") );
//x1	*poAtom = lId;

//x1	poAtom->PrefixSet ( (m_bNextPrefix?" ":"") );
//x1	poAtom->SuffixSet ( (bWhite?" ":"") );
//x1	m_bNextPrefix=false;

//x1	poAtom->UserSignSet (usersigns_objectlink);

//x1	poCurrentObject->AtomAdd ( poAtom );
	
	
//x1    if ( IsVerbose() ) std::cout << "Add atom with " << (bWhite?" whitespace-":"empty ")
//x1			  << "suffix and meta-link object with id " << lId << std::endl;
    }

odb::CAtom* CBib::LinkAbbrevToObject ( std::string sAbbrev, odb::CObject* poParent )
	{
	CMapAbbrev2Object::iterator mIt = m_mAbbrev2Object.find ( sAbbrev );
	if ( mIt == m_mAbbrev2Object.end() )
		{
		if ( IsVerbose() ) std::cerr << "Abbreviation [" << sAbbrev << "] not found!" << std::endl;
		return 0;
		}
		
	odb::CObject* poString = mIt->second;
	
	
//	std::cout << "[" << poParent->ClassGet()->NameGet() << "]->" << std::flush;
//	std::cout << "[" << poString->ClassGet()->NameGet() << "]" << std::flush;

	char cParent = (char)tolower(poParent->ClassGet()->NameGet()[0]);
	char cString = (char)tolower(poString->ClassGet()->NameGet()[0]);

	std::string sParReason = "p:  ";
	sParReason[3] = cParent;
	sParReason += "-> ";
	sParReason[6] = cString;


	std::string sChiReason = "c:  ";
	sChiReason[3] = cString;
	sChiReason += "-> ";
	sChiReason[6] = cParent;

//	std::cout << "  {" << sParReason << "} und {" << sChiReason << "}   --> " << std::flush;
	if ( m_mName2Reason.find ( sParReason ) == m_mName2Reason.end() )
		{
		std::cerr << "Error: could not find Reason: [" << sParReason << "]" << std::endl;
		exit(1); 
		}
	if ( m_mName2Reason.find ( sChiReason ) == m_mName2Reason.end() )
		{
		std::cerr << "Error: could not find Reason: [" << sChiReason << "]" << std::endl;
		exit(1); 
		}
	
	
	if ( !poParent->Link( poString, m_mName2Reason[sParReason] ) ) std::cerr << " *!: " << sAbbrev << " (" << poString->ID() << ")<-("
																  << poParent->ID() << ")" << std::endl;

	if ( !poString->Link( poParent, m_mName2Reason[sChiReason] ) ) std::cerr << " *!: " << sAbbrev << " (" << poString->ID() << ")->("
																  << poParent->ID() << ")" << std::endl;
	
	CAtom* poAtom = odb.NewAtom ( _TEXT("Link") );
	*poAtom = poString->ID();

	return poAtom;
	}



void CBib::AddAtom ( std::string sText, bool bWhite, long nUsersign )
    {
	pd(); 
    if ( IsVerbose() ) std::cout << "[" << sText << "] as Atom with " << (bWhite?"whitespace-":"empty ") << "suffix to current Object. (Usersign " << nUsersign << ")" << std::endl;
    
	
	//TODO: do casual checking
	CObject* poCurrentObject = m_vObjects.back()->poObject;


	CAtom* poAtom;
	
	
	switch ( nUsersign )
		{
		case usersigns_word:		poAtom = odb.NewAtom ( _TEXT("Word") );		*poAtom = sText; break;
		case usersigns_path:		poAtom = odb.NewAtom ( _TEXT("Path") );		*poAtom = sText; break;
		case usersigns_accent:		poAtom = odb.NewAtom ( _TEXT("Accent") );	*poAtom = sText; break;
		case usersigns_number:		poAtom = odb.NewAtom ( _TEXT("Number") );	*poAtom = sText; break;
		case usersigns_comma:		poAtom = odb.NewAtom ( _TEXT("Comma") );	*poAtom = sText; break;
		case usersigns_dot:			poAtom = odb.NewAtom ( _TEXT("Dot") );		*poAtom = sText; break;
		case usersigns_opar:		poAtom = odb.NewAtom ( _TEXT("Opar") );		*poAtom = sText; break;
		case usersigns_epar:		poAtom = odb.NewAtom ( _TEXT("Epar") );		*poAtom = sText; break;
		case usersigns_latex:		poAtom = odb.NewAtom ( _TEXT("Latex") );	*poAtom = sText; break;
		case usersigns_mathmode:	poAtom = odb.NewAtom ( _TEXT("Math") );		*poAtom = sText; break;
		case usersigns_abbrev:		poAtom = LinkAbbrevToObject ( sText, poCurrentObject ); 
									if ( !poAtom ) return; nUsersign = usersigns_objectlink; break;
		default:					poAtom = odb.NewAtom ( _TEXT("Content") );	*poAtom = sText; break;
		}

	m_poLastAtom = poAtom;
	poAtom->UserSignSet (nUsersign);

	
	
	std::string sTemp	= ( m_bNextPrefix?" ":"");
	sTemp			   += ( m_bBeginExplizit?"{":"");
	
	
	poAtom->PrefixSet ( sTemp );
	poAtom->SuffixSet ( (bWhite?" ":"") );

	m_bNextPrefix		= false;
	m_bBeginExplizit	= false;


	poCurrentObject->AtomAdd ( poAtom );
	}
	

void CBib::SetKey ( std::string sName )
	{
	pd(); 
	if ( IsVerbose() ) std::cout << "Setting Key [" << sName << "] of previously created Object." << std::endl;


	CObject* poCurrentObject = m_vObjects.back()->poObject;

	CAtom* poAtom = odb.NewAtom ( "Key" );
	poAtom->UserSignSet (usersigns_key);

	*poAtom = sName;

	poCurrentObject->AtomAdd ( poAtom );
	}

void CBib::CreateObject ( std::string sName, std::string sType, long nType )
	{
	pd(); 
	if ( m_bVerbose ) std::cout << "-->Create " << sType << "-Object [" << sName << "]" << std::endl;
	
	if ( m_mName2Class.find ( sType ) == m_mName2Class.end() )
		{
		std::cerr << "Error in bib.y or bib.h/bib.cxx: unknown class" << std::endl;
		exit(1); 
		}
		
	CObject* pObj = odb.NewObject ( sName, m_mName2Class[sType] );
	
	switch ( nType )
		{
		case objects_atstring: m_mAbbrev2Object[sName] = pObj; break;
		default: break;
		}
	
	
	
	
//x2	CAtom* poAtom = odb.NewAtom ( _TEXT("Type") );
//x2	*poAtom = sName;
//x2	poAtom->UserSignSet (usersigns_type);
//x2	pObj->AtomAdd ( poAtom );
	
	m_vObjects.push_back ( new CObjectEntry ( pObj, m_mName2Class[sType], sName, sType ) );
	}

void CBib::FinishObject ( std::string sName, long nType )
	{
	pd(); 
	if ( IsVerbose() ) std::cout << "Finish Object [" << sName << "]" << std::endl;
	
	CObjectEntry* pChildObject = m_vObjects.back();

	m_vObjects.pop_back();
	
	if ( m_vObjects.size() )
		{
		CObjectEntry* pParentObject = m_vObjects.back();

		std::string sReason1 = "c: " + pParentObject->sShort + "->" + pChildObject->sShort;
//		std::string sReason2 = "p: " + pChildObject->sShort  + "->" + pParentObject->sShort;
		
		
//		std::string sClass1 = pChildObject->poObject->ClassGet()->NameGet();
//		std::string sClass2 = pParentObject->poObject->ClassGet()->NameGet();
		
		
		
		if ( m_mName2Reason.find ( sReason1 ) == m_mName2Reason.end() )
			{
			std::cerr << "Error: could not find Reason: [" << sReason1 << "]" << std::endl;
			exit(1); 
			}
		CReason* poReason1 = m_mName2Reason[sReason1];
		
//		if ( m_mName2Reason.find ( sReason2 ) == m_mName2Reason.end() )
//			{
//			std::cerr << "Error: could not find Reason: [" << sReason2 << "]" << std::endl;
//			exit(1); 
//			}
//		CReason* poReason2 = m_mName2Reason[sReason2];


//Kann es sein dass die zweiseitige Verlinkung zur GŠnze wertlos ist??
		
		pd();
		//if ( IsVerbose() )
//			std::cout << "Linking P with C using Reason  [" << sClass2 << "->" << sReason1 << "]" << std::flush;
			if ( !pParentObject->poObject->Link( pChildObject->poObject, poReason1 ) ) std::cout << " *" << std::flush;
//			std::cout << std::endl;

//			std::cout << "Linking C with P using Reason  [" << sClass1 << "->" << sReason2 << "]" << std::flush;
//			if ( !pChildObject->poObject->Link( pParentObject->poObject, poReason2 ) ) std::cout << " *" << std::flush; 
//			std::cout << std::endl;

		}
	
	delete pChildObject;

	}



