#ifndef __outputodb__H_
#define __outputodb__H_

#include "generic.h"
#include "odb.h"
#include "bib.h"
#include "output.h"


class COutputOdb : public COutput
{
private:
	typedef COutput Inherited;

protected:

public:

	COutputOdb ( odb::CODB& rOdb ) : Inherited ( rOdb ) { }

	void Dump() { odb.Dump(); }
};

#endif

