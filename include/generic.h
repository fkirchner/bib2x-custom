/***************************************************************************
                          generic.h  -  description
                             -------------------
    begin                : Mon Mar 13 2000
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

#if _MSC_VER >= 1000
#pragma once
#pragma warning (disable : 4786)
#endif // _MSC_VER >= 1000

#ifndef __GENERIC_H
#define __GENERIC_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// STL
#include <string>
#include <set>
#include <map>
#include <iostream>
#include <fstream>

namespace odb
  {

  #define ODB_SUCCESS           0L
  #define ODB_FAILURE          -1L

  #define ODB_ROPE_RECURSION   -100L
  #define ODB_UNKNOWN_INSTANCE -101L

  } // namespace odb

#ifdef WIN32
  #include "winsock.h"
  extern "C" int gettimeofday( struct timeval*, struct timezone*);
  #else
  #include <sys/time.h>
  #endif // WIN32
bool operator > (const timeval& t1, const timeval& t2);

#ifndef _TEXT
#  define _TEXT(s) (const std::string&) s
#endif // _TEXT

#endif // __GENERIC_H
