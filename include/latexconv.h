#ifndef __LATEXCONV_H
#define __LATEXCONV_H

#include <string>
#include <map>

typedef std::pair<long,long> POpenClose;

static const long enclosings_nothing		= 0x0000;
static const long enclosings_emphopen		= 0x0001;
static const long enclosings_emphclose	    = 0x0002;
static const long enclosings_explizitopen   = 0x0003;
static const long enclosings_explizitclose  = 0x0004;
static const long definition_whitespace     = 0x0005;
static const long definition_pathopen		= 0x0006;
static const long definition_pathmiddle		= 0x0007;
static const long definition_pathclose		= 0x0008;




class CLatexConv
{
private:

	CLatexConv()
		{
		Initialize();
		}


protected:
	typedef std::map<std::string,std::string> MLatex2Utf;

    typedef std::map<std::string, POpenClose> MLatex2Pair;
    typedef std::map<std::string, bool> MLatex2bool;
	

	MLatex2Utf m_mLatex2Utf;
	MLatex2Pair m_mLatex2Pair;

	MLatex2bool	m_mLatex2Elim;

	void Initialize();


public:

	static CLatexConv& Instance()
		{
		static CLatexConv oLatexConv;
		return oLatexConv;
		}


	std::string Latex2Utf ( std::string sLatex );

	bool IsEnclosing ( std::string sLatex );

	POpenClose GetEnclosing ( std::string sLatex );
	
	bool ElimWhitespace ( std::string sLatex );

};

#endif

