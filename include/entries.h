#ifndef __ENTRIES_H__
#define __ENTRIES_H__


#include <vector>
#include <string>
#include <map>
#include <set>
#include <sstream>


typedef std::vector<std::string> CVectorString;
typedef std::set<std::string> CListString;


class CEntry
	{
	public:
		static const int rtti = 0x0001;
		virtual int Rtti ( ) = 0;
	
		virtual std::string& Dump ( ) = 0;
		
		CEntry ( ) {}
	
	};
	
typedef std::vector<CEntry*> CVectorEntries;


class CEntryText : public CEntry
	{
	typedef CEntry inherited;
	protected:
		std::string m_sContent;
		
	public:
		static const int rtti = 0x0002;
		virtual int Rtti ( ) { return rtti; }
		
		CEntryText ( std::string& sText ) : inherited ( ) { m_sContent = sText; }

		virtual ~CEntryText() {}

		void Push ( std::string& sText ) { m_sContent += sText; }
		std::string& Dump ( ) { return m_sContent; } 
	};
	
class CEntryCommand : public CEntry
	{
	typedef CEntry inherited;

	protected:
		std::string m_sCommand;
		
		int m_nSpecific;
		unsigned int m_nModifier;
	
	
		bool m_bRange;
		int m_nRangeBegin;
		int m_nRangeEnd;
		std::string m_sPrefix;
		std::string m_sDelim;
		std::string m_sSuffix;
		
	
	public:
		static const int rtti = 0x0003;

		static const unsigned int mod_none					= 0;
		static const unsigned int mod_lowercase				= 1203; /* LC */
		static const unsigned int mod_lowercase_firstupper	= 1206; /* LF */
		static const unsigned int mod_uppercase				= 2103; /* UC */
		static const unsigned int mod_uppercase_begin		= 2102; /* UB */
		
		virtual int Rtti ( ) { return rtti; }

		CEntryCommand ( std::string& sCommand, int nSpecific ) 
			: inherited(),
			  m_sCommand ( sCommand ),
			  m_nSpecific ( nSpecific ),
			  m_bRange ( false )
			{
			}

		CEntryCommand ( std::string& sCommand, int nSpecific, char cModMajor, char cModMinor ) 
			: inherited(),
			  m_sCommand ( sCommand ),
			  m_nSpecific ( nSpecific ),
			  m_bRange ( false )
			{
			m_nModifier = (toupper(cModMajor)-'A'+1)*100 + (toupper(cModMinor)-'A'+1);
			}

		void SetRange ( int nBegin, int nEnd, std::string sPrefix, std::string sDelim, std::string sSuffix )
			{
			m_bRange = true;
			m_nRangeBegin = nBegin;
			m_nRangeEnd = nEnd;
			m_sPrefix = sPrefix;
			m_sDelim = sDelim;
			m_sSuffix = sSuffix;
			}


		bool HasRange ( ) {return m_bRange; }
		int GetRangeBegin () { return m_nRangeBegin; } 
		int GetRangeEnd () { return m_nRangeEnd; } 
		std::string& GetPrefix () { return m_sPrefix; }
		std::string& GetDelim () { return m_sDelim; }
		std::string& GetSuffix () { return m_sSuffix; }

		unsigned int GetModifier ( ) { return m_nModifier; }

		virtual ~CEntryCommand() {}
			  
		std::string& Dump ( ) { return m_sCommand; } 
	};




class CConstraint
	{

	protected:
		std::string m_sName;
		int m_nSpecific;
		int  m_nOperator;
		CVectorString m_vValues;
	
	public:
	
		CConstraint ( std::string& sName, int nSpecific, int nOperator )
			: m_sName ( sName ),
			  m_nSpecific ( nSpecific ),
			  m_nOperator ( nOperator )
			{ }
			
		int Operator ( ) { return m_nOperator; }
		int Specific ( ) { return m_nSpecific; }
		const std::string& Name ( ) { return const_cast<const std::string&>(m_sName); }
		
		void Push ( std::string& sValue ) { m_vValues.push_back ( sValue ); }
		
		std::string Dump ( );

		CVectorString& Values ( ) { return m_vValues; }
		CVectorString::iterator begin() { return m_vValues.begin(); }
		CVectorString::iterator end()   { return m_vValues.end();   }
	
	};


typedef std::vector<CConstraint> CVectorConstraint;


class CEntryRoot : public CEntry {

public:
	typedef CEntry inherited;

	
	typedef CVectorEntries::iterator iterator;

protected:

	CEntryRoot*       m_poParent;
		
	CVectorEntries    m_vpoEntries[4];
	
	CListString		  m_lConditions;
	CVectorConstraint m_vConstraints;
	

	
	bool m_bSortOrder;
	
	
	std::string sNothing;
	int m_nCurrentToken;
	
		
public:
	static const int rtti = 0x0004;
	virtual int Rtti ( ) { return rtti; }
		
	CEntryRoot ( CEntryRoot* poParent ) 
		: inherited(),
		  m_poParent  ( poParent )
		{
		m_nCurrentToken = 0;
		}
	
	virtual ~CEntryRoot() {}

	CEntryRoot* GetParent ( ) { return m_poParent; }
				
	CEntryRoot* Push ( CEntry* poEntry );
	std::string& Dump ( ) { return sNothing; }

	void ConstraintAdd ( CConstraint& roConstraint ) { m_vConstraints.push_back(roConstraint); }
	void ConditionAdd  ( std::string& sCondition ) { m_lConditions.insert ( sCondition ); }
	
	void SetSortOrder ( bool bSortOrder ) { m_bSortOrder = bSortOrder; }
	bool GetSortOrder ( ) { return m_bSortOrder; }
	
	CVectorEntries::iterator begin() { return m_vpoEntries[0].begin(); }
	CVectorEntries::iterator end()   { return m_vpoEntries[0].end(); }


	CVectorConstraint& GetConstraints() { return m_vConstraints; }
	CListString&       GetConditions() { return m_lConditions; }

	};




class CEntryRootGroup : public CEntryRoot {
	
	typedef CEntryRoot inherited;

public:
	static const int rtti = 0x0005;
	virtual int Rtti ( ) { return rtti; }
	
	CEntryRootGroup ( CEntryRoot* poParent ) 
		: inherited(poParent)
		{ }

	virtual ~CEntryRootGroup() {}

	
};


class CEntryRootFor : public CEntryRoot {
typedef CEntryRoot inherited;
public:
	static const int rtti = 0x0006;
	virtual int Rtti ( ) { return rtti; }
	
	CEntryRootFor ( CEntryRoot* poParent ) 
		: inherited(poParent)
		{ }
	virtual ~CEntryRootFor() {}


};

class CEntryRootBib : public CEntryRoot {
typedef CEntryRoot inherited;


protected:

	CVectorString       m_vIncludes;
	CListString			m_lExcludes;
	bool			  m_bIsExclusive;


public:
	static const int rtti = 0x0007;
	virtual int Rtti ( ) { return rtti; }
	
	CEntryRootBib ( CEntryRoot* poParent ) 
		: inherited(poParent)
		{ }
	virtual ~CEntryRootBib() {}

	void SetToken ( int nToken ) { m_nCurrentToken = nToken; }
	
	void PushInclusion ( std::string& sInclusion ) { m_vIncludes.push_back ( sInclusion ); }
	void PushExclusion ( std::string& sExclusion ) { m_lExcludes.insert ( sExclusion ); }
	void SetExclusive ( ) { m_bIsExclusive = true; }

	bool IsExclusive ( ) { return m_bIsExclusive; }
	
	CVectorString&   GetIncludes ( ) { return m_vIncludes; }
	CListString& GetExcludes ( ) { return m_lExcludes; }


	CVectorEntries::iterator begin(unsigned int n) { if ( n < 4 ) return m_vpoEntries[n].begin(); }
	CVectorEntries::iterator end  (unsigned int n) { if ( n < 4 ) return m_vpoEntries[n].end(); }


};

class CEntryRootReduce : public CEntryRoot {
typedef CEntryRoot inherited;
public:
	static const int rtti = 0x0008;
	virtual int Rtti ( ) { return rtti; }
	
	CEntryRootReduce ( CEntryRoot* poParent ) 
		: inherited(poParent)
		{ }
	virtual ~CEntryRootReduce() {}


};



#endif

