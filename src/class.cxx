/***************************************************************************
                         class.cpp  -  description
                             -------------------
    begin                : Fri Mar 3 2000
    copyright            : (C) 1993..2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *                                                                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place Suite 330,                                            *
 *   Boston, MA  02111-1307, USA.                                          *
 *                                                                         *
 ***************************************************************************/

#include "generic.h"

#include "class.h"
#include "object.h"
#include "odb.h"

using namespace odb;

//------------------------------------------------------------------//
// Construction/Destruction
//------------------------------------------------------------------//

IMPLEMENT_RTTI(Class, Root, 0x00980430)

CClass::CClass()
  : inherited()
  {
  InitBasics();
  } // CClass::CClass()

CClass::CClass(long lid)
  : inherited(lid)
  {
  InitBasics();
  } // CClass::CClass(lid)

CClass::CClass(const std::string& sName, CObject* poOMAL)
  : inherited(sName)
  {
  InitBasics();

  if ( poOMAL != 0 )
    {
    m_poOMAL = poOMAL;
    } // if ( poOMAL != 0 )
  } // CClass::CClass(const string& sName, CObject* poOMAL)

CClass::CClass(CClass& src)
  {
  *this = src;
  }

CClass::~CClass()
  {
  } // CClass::~CClass()

void CClass::InitBasics()
  {
  m_poOMAL  = 0;
  m_poClass = 0;
  } // void CClass::InitBasics()

CClass* CClass::operator = (const CClass* src)
  {
  if (src == this)
    {
    return this;
    }
  m_poOMAL = src->m_poOMAL;
  TimeStampUpdate();
  return this;
  }

CRoot* CClass::Copy()
  {
  return new CClass(*this);
  }

CStream& CClass::Save(CStream& oStream)
  {
  if ( m_poOMAL == 0 )
    oStream << -1L;
  else
    oStream << m_poOMAL->ID();
  return inherited::Save(oStream);
  } // CStream& CClass::Save(CStream& oStream)

CStream& CClass::Load(CStream& oStream)
  {
  long lPtrOMAL;
  oStream >> lPtrOMAL; m_poOMAL = (CObject*)lPtrOMAL;
  return inherited::Load(oStream);
  } // CStream& CClass::Load(CStream& oStream)

bool CClass::ResolveIDs(CODB& oDB)
  {
  m_poOMAL = oDB.Id2Ptr(m_poOMAL);
  inherited::ResolveIDs(oDB);
  return true;
  } // bool CClass::ResolveIDs(CODB& oDB)

CObject* CClass::OmalGet() const
  {
  return m_poOMAL;
  }

bool CClass::OmalSet( const CObject* poOMAL, bool bOverwrite )
  {
  if ( (m_poOMAL != 0) || (bOverwrite == false) )
    {
    // OMAL already exists
    // return true, if it is the same as in the method argument
    return poOMAL == m_poOMAL;
    }
  m_poOMAL = const_cast<CObject*>(poOMAL);
  TimeStampUpdate();
  return true;
  }

CObject* CClass::operator = (const CObject* poOMAL)
  {
  OmalSet( poOMAL, false );
  return m_poOMAL;
  } // CObject* CClass::operator = (CObject* poOMAL)

CClass::operator CObject*() const
  {
  return m_poOMAL;
  } // CObject* CClass::operator = (CObject* poOMAL)


/// ClassSet()
CClass* CClass::ClassSet(const CClass* poClass)
  {
  /* --xandi--
  if ( m_poClass != poClass )
	{
	if ( m_poClass )
		{
		CListObject::iterator lIt    = m_loObjects.begin();
		CListObject::iterator lItEnd = m_loObjects.end();
		
		for ( ; lIt != lItEnd; ++lIt )
			{
			m_poClass->ObjectDeregister ( *lIt );
			}
		}
	if ( poClass )
		{
		CListObject::iterator lIt    = m_loObjects.begin();
		CListObject::iterator lItEnd = m_loObjects.end();
		
		for ( ; lIt != lItEnd; ++lIt )
			{
			const_cast<CClass*>(poClass)->ObjectRegister ( *lIt );
			}
		}
	}
  --xandi-- */
  return m_poClass = const_cast<CClass*>(poClass);
  } // const CClass* CClass::ClassSet()

/// ClassGet()
CClass* CClass::ClassGet() const
  {
  return m_poClass;
  } // const CClass* CClass::ClassGet()


bool CClass::ObjectDeregister ( const CObject* poObject )
  {
  /* --xandi--
  if ( m_poClass )
	{
	m_poClass->ObjectDeregister ( poObject );
	}
  --xandi-- */
  CListObject::iterator lIt    = m_loObjects.find(const_cast<CObject*>(poObject));
  CListObject::iterator lItEnd = m_loObjects.end();

  if ( lIt != lItEnd ) //this MUST happen!
	{

	m_loObjects.erase(lIt);
	return true;
	} 
  else //if ( lIt != lItEnd ) 
	{
	//TODO react or not
	return false;
	} //else if ( lIt != lItEnd )
  }
  
bool CClass::ObjectRegister   ( const CObject* poObject )
  {
  /* --xandi--
  if ( m_poClass )
	{
	m_poClass->ObjectRegister ( poObject );
	}
  --xandi-- */
	
  m_loObjects.insert( const_cast<CObject*>(poObject) );
  return true;
  }

const CListObject& CClass::ObjectsGet() const
  {
  return m_loObjects;
  }

