/***************************************************************************
                          stream.cpp  -  description
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

#include "stream.h"
#include "root.h"

using namespace odb;

//------------------------------------------------------------------//
// Construction/Destruction
//------------------------------------------------------------------//

CStream::CStream()
  {
  }

CStream::CStream(const std::string& sFileName, bool bWrite)
  {
  try
    {
    if (bWrite)
      {
      m_oFile.open(sFileName.c_str(), std::ios::out | std::ios::binary);
      }
    else
      {
      m_oFile.open(sFileName.c_str(), std::ios::in | std::ios::binary);
      }
    }
  catch (...) // (CFileException* e)
    {
//    MessageBox(0, e->m_strFileName, "ERROR - Opening", IDOK);
    throw;
    }
  } // CStream::CStream(const std::string& sFileName, bool bWrite)

CStream::~CStream()
  {
  try
    {
    m_oFile.close();
    }
  catch (...)
    {
//    MessageBox(0, e->m_strFileName, "ERROR - Closing", IDOK);
    throw;
    }
  } // CStream::~CStream()

bool CStream::Seek(long lPosition)
  {
  try
    {
    m_oFile.seekg(lPosition);
    }
  catch (...)
    {
//  MessageBox(0, e->m_strFileName, "ERROR - Seeking", IDOK);
//  e->Delete();
    return false;
    }
  return true;
  } // bool CStream::Seek(long lPosition)

CStream& CStream::Read(void* pData, unsigned long ulSize)
  {
  try
    {
#ifdef WIN32
    m_oFile.read( (char*)pData, ulSize );
#else
    m_oFile.read( (char*)pData, ulSize );
#endif
    }
  catch (...)
    {
//    e->Delete();
    }
  return *this;
  } // bool CStream::Read(void* pData, unsigned long ulSize)

CStream& CStream::Write(void* pData, unsigned long ulSize)
  {
  try
    {
#ifdef WIN32
    m_oFile.write( (char*)pData, ulSize );
#else
    m_oFile.write( (char*)pData, ulSize );
#endif
    }
  catch (...)
    {
//    e->Delete();
    }
  return *this;
  } // bool CStream::Write(void* pData, unsigned long ulSize)


CStream& CStream::operator >> (long& data)
  {
  try
    {
    Read(&data, sizeof(data));
    }
  catch (...)
    {
//    e->Delete();
    }
  return *this;
  }

CStream& CStream::operator << (long data)
  {
  try
    {
    Write(&data, sizeof(data));
    }
  catch (...)
    {
//    e->Delete();
    }
  return *this;
  }

CStream& CStream::operator >> (bool& data)
  {
  try
    {
    Read(&data, sizeof(data));
    }
  catch (...)
    {
//    e->Delete();
    }
  return *this;
  }

CStream& CStream::operator << (bool data)
  {
  try
    {
    Write(&data, sizeof(data));
    }
  catch (...)
    {
//    e->Delete();
    }
  return *this;
  }

CStream& CStream::operator >> (CRoot& data)
  {
  return data.Load(*this);
  }

CStream& CStream::operator << (CRoot& data)
  {
  return data.Save(*this);
  }

CStream& CStream::operator >> (std::string& data)
  {
  try
    {
    long size;
    Read(&size,  sizeof(size));
    char* psz = new char[size];
    Read(psz, size);
    data = psz;
    delete [] psz;
    }
  catch (...)
    {
//    e->Delete();
    }
  return *this;
  }

CStream& CStream::operator << (std::string& data)
  {
  try
    {
    static char c0 = 0;
    long size = data.length()+1;
    Write(&size, sizeof(size));
    Write((void*)data.c_str(), size-1);
    Write((void*)&c0, 1);
    }
  catch (...)
    {
//    e->Delete();
    }
  return *this;
  }

CStream& CStream::operator >> (double& data)
  {
  try
    {
    Read(&data, sizeof(data));
    }
  catch (...)
    {
//    e->Delete();
    }
  return *this;
  }

CStream& CStream::operator << (double data)
  {
  try
    {
    Write(&data, sizeof(data));
    }
  catch (...)
    {
//    e->Delete();
    }
  return *this;
  }

CStream& CStream::operator >> (timeval& data)
  {
  try
    {
    Read(&data, sizeof(data));
    }
  catch (...)
    {
//    e->Delete();
    }
  return *this;
  }

CStream& CStream::operator << (timeval data)
  {
  try
    {
    Write(&data, sizeof(data));
    }
  catch (...)
    {
//    e->Delete();
    }
  return *this;
  }
