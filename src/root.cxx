/***************************************************************************
                          root.cpp  -  description
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

#include "root.h"
#include "odb.h"

using namespace odb;

#ifdef WIN32
extern "C"
  int gettimeofday( struct timeval* ptv, struct timezone* ptz)
    {
    int nResult = 0;
    _timeb  stTimeB;
    _ftime(&stTimeB);
    try
      {
      if (ptv != 0)
        {
        ptv->tv_sec  = stTimeB.time;
        ptv->tv_usec = stTimeB.millitm;
        } // if (ptv != 0)
/*
      if (ptz != 0)
        {
        *ptz = stTimeB.timezone;
        } // if (ptz != 0)
*/
      nResult = 1;
      }
    catch(...)
      {
      nResult = 0;
      } // catch(...)
    return nResult;
  } // int gettimeofday(struct timeval *, struct timezone * )
#endif // WIN32

//------------------------------------------------------------------//
// Construction/Destruction
//------------------------------------------------------------------//

IMPLEMENT_RTTI(Root, None, 0x00980430)

/// default constructor
CRoot::CRoot()
  {
  InitBasics();
  } // CRoot::CRoot()

/// constructor
CRoot::CRoot(long lid)
  {
  InitBasics();
  m_lid = lid;
  } // CRoot::CRoot(long lid)

/// constructor
CRoot::CRoot(const std::string& sName)
  {
  InitBasics();
  m_sName = sName;
  } // CRoot::CRoot(const CString& sName)

/// constructor
CRoot::CRoot(const CRoot* src)
  {
  operator = (*src);
  } // CRoot(const CRoot& src)

/// destructor
CRoot::~CRoot()
  {
  } // CRoot::~CRoot()

void CRoot::InitBasics()
  {
  m_lid      = -1;
  m_bDeleted = false;
  m_sName.erase();
  TimeStampUpdate();
  } // void CRoot::InitBasics()

timeval CRoot::TimeStampGet()
  {
  return m_tTimeStamp;
  } // time_t CRoot::TimeStampGet()

bool CRoot::TimeStampUpdate()
  {
  return gettimeofday(&m_tTimeStamp, 0) == 0;
  } // bool CRoot::TimeStampUpdate()

CRoot* CRoot::operator = (const CRoot* src)
  {
  if (src == this)
    {
    return this;
    }

  m_bDeleted = src->m_bDeleted;
  m_sName    = src->m_sName;

  TimeStampUpdate();
  return this;
  } // CRoot& CRoot::operator = (CRoot& src)

CRoot* CRoot::Copy()
  {
  return new CRoot(this);
  };

bool CRoot::Validate(CODB& roODatabase)
  {
  if ( m_lid != -1)
    {
    return true;
    }

  m_lid = roODatabase.IdValidate(this);

  TimeStampUpdate();
  return (m_lid != -1);
  } // CRoot::Validate(CODB& oODatabase)

bool CRoot::IsValid() const
  {
  return (m_lid != -1);
  } // bool CRoot::IsValid()

long CRoot::ID() const
  {
  return m_lid;
  } // long CRoot::ID()

//////////////////////////////////////////////////////////////////////////////
// storing & loading
//////////////////////////////////////////////////////////////////////////////

CStream& CRoot::Save(CStream& oStream)
  {
  oStream << m_bDeleted;
  oStream << m_sName;
  oStream << m_tTimeStamp;

  oStream << (long)m_moReferencingInstances.size();

  for (CMapReferencing::iterator it  = m_moReferencingInstances.begin();
                                 it != m_moReferencingInstances.end();
                               ++it)
    {
    oStream << it->first->ID();
    oStream << it->second;
    } // for (CMapReferencing::iterator it = m_moReferencingInstance.begin();

  return oStream;
  } // CStream& CRoot::Save(CStream& oStream)

CStream& CRoot::Load(CStream& oStream)
  {
  oStream >> m_bDeleted;
  oStream >> m_sName;
  oStream >> m_tTimeStamp;

  long lCount;
  oStream >> lCount;
  for ( long l = 0; l < lCount; l++ )
    {
    long lPtr;
    long lCounter;

    oStream >> lPtr;
    oStream >> lCounter;

    m_moReferencingInstances[(CObject*)lPtr] = lCounter;
    }

  return oStream;
  } // CStream& CRoot::Load(CStream& oStream)

bool CRoot::ResolveIDs(CODB& oDB)
  {
  CMapReferencing moReferencingInstances;
  for (CMapReferencing::iterator it  = m_moReferencingInstances.begin();
                                 it != m_moReferencingInstances.end();
                               ++it)
    {
    moReferencingInstances[oDB.Id2Ptr((CObject*)it->first)] = it->second;
    }

  m_moReferencingInstances.swap( moReferencingInstances );

  return true;
  }

bool CRoot::ReferenceMade(CRoot* poReferencingInstance)
  {
	CMapReferencing::iterator it = m_moReferencingInstances.find(poReferencingInstance);

  if (it != m_moReferencingInstances.end())
    {
    // another link to an already linked object was made
    m_moReferencingInstances[poReferencingInstance] = it->second +1;
    }
  else
    {
    // the first link to an object was created
    m_moReferencingInstances[poReferencingInstance] = 1;
    }

  TimeStampUpdate();
  return true;
  } // bool CRoot::ReferenceMade(CRoot& oReferencingInstance)

bool CRoot::ReferenceRemoved(CRoot* poReferencingInstance)
  {
	CMapReferencing::iterator it = m_moReferencingInstances.find(poReferencingInstance);

  if (it == m_moReferencingInstances.end())
    {
    // this should never happens
    return false;
    }

  if (it->second > 1)
    {
    // one of multiple existing references are removed
    m_moReferencingInstances[poReferencingInstance] = it->second -1;
    }
  else
    {
    // the last reference was removed
    m_moReferencingInstances.erase(it);
    }

  TimeStampUpdate();
  return true;
  } // bool CRoot::ReferenceRemoved(CRoot& oReferencingInstance)

const long CRoot::ParentCount()
  {
  return m_moReferencingInstances.size();
  } // const long CRoot::ParentCount()

const CMapReferencing& CRoot::ParentGet()
  {
  return m_moReferencingInstances;
  } // const CMapReferencing& CRoot::ParentGet()

//////////////////////////////////////////////////////////////////////////////
// operations
//////////////////////////////////////////////////////////////////////////////

bool CRoot::Delete()
  {
  TimeStampUpdate();
  return m_bDeleted = true;
  } // bool CRoot::Delete()

const std::string& CRoot::NameSet(const std::string& sName)
  {
  if ( IsValid() == true )
    {
    // if the instance is validated, name changing
    // is only allowed via database methode!
    return m_sName;
    }
  m_sName = sName;
  TimeStampUpdate();
  return m_sName;
  } // const CString& CRoot::NameSet()

const std::string& CRoot::NameGet() const
  {
  return m_sName;
  } // const CString& CRoot::NameGet()
