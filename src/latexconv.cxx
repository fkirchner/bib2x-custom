#include "latexconv.h"


void CLatexConv::Initialize()
	{
	m_mLatex2Utf["Gamma"]		= "&#x0393;";
	m_mLatex2Utf["Delta"]		= "&#x0394;";
	m_mLatex2Utf["Theta"]		= "&#x0398;";
	m_mLatex2Utf["Lambda"]		= "&#x039B;";
	m_mLatex2Utf["Xi"]			= "&#x039E;";
	m_mLatex2Utf["Pi"]			= "&#x03A0;";
	m_mLatex2Utf["Sigma"]		= "&#x03A3;";
	m_mLatex2Utf["Upsilon"]		= "&#x03A5;";
	m_mLatex2Utf["Phi"]			= "&#x03A6;";
	m_mLatex2Utf["Psi"]			= "&#x03A8;";
	m_mLatex2Utf["Omega"]		= "&#x03A9;";
	m_mLatex2Utf["alpha"]		= "&#x03B1;";
	m_mLatex2Utf["beta"]		= "&#x03B2;";
	m_mLatex2Utf["gamma"]		= "&#x03B3;";
	m_mLatex2Utf["delta"]		= "&#x03B4;";
	m_mLatex2Utf["epsilon"]		= "&#x03B5;";
	m_mLatex2Utf["varepsilon"]	= "&#x03B5;"; //schade
	m_mLatex2Utf["zeta"]		= "&#x03B6;";
	m_mLatex2Utf["eta"]			= "&#x03B7;";
	m_mLatex2Utf["theta"]		= "&#x03B8;";
	m_mLatex2Utf["vartheta"]	= "&#x03D1;";
	m_mLatex2Utf["iota"]		= "&#x03B9;";
	m_mLatex2Utf["kappa"]		= "&#x03BA;";
	m_mLatex2Utf["lambda"]		= "&#x03BB;";
	m_mLatex2Utf["mu"]			= "&#x03BC;";
	m_mLatex2Utf["nu"]			= "&#x03BD;";
	m_mLatex2Utf["xi"]			= "&#x03BE;";
	m_mLatex2Utf["omicron"]		= "&#x03BF;";
	m_mLatex2Utf["pi"]			= "&#x03C0;";
	m_mLatex2Utf["varpi"]		= "&#x03D6;";
	m_mLatex2Utf["rho"]			= "&#x03C1;";
	m_mLatex2Utf["varrho"]		= "&#x03F1;";
	m_mLatex2Utf["sigma"]		= "&#x03C3;";
	m_mLatex2Utf["varsigma"]	= "&#x03C2;";
	m_mLatex2Utf["tau"]			= "&#x03C4;";
	m_mLatex2Utf["upsilon"]		= "&#x03C5;";
	m_mLatex2Utf["phi"]			= "&#x03D5;";
	m_mLatex2Utf["varphi"]		= "&#x03C6;";
	m_mLatex2Utf["chi"]			= "&#x03C7;";
	m_mLatex2Utf["psi"]			= "&#x03C8;";
	m_mLatex2Utf["omega"]		= "&#x03C9;";
	m_mLatex2Utf["#"]			= "&#x0023;";
	m_mLatex2Utf["$"]			= "&#x0024;";
	m_mLatex2Utf["&"]			= "&#x0026;";
	m_mLatex2Utf["%"]			= "&#x0025;";
	m_mLatex2Utf["S"]			= "&#x00A7;";
	m_mLatex2Utf["P"]			= "&#x00B6;";
	m_mLatex2Utf["{"]			= "&#x007B;";
	m_mLatex2Utf["}"]			= "&#x007D;";
	m_mLatex2Utf["_"]			= "&#x005F;";
	m_mLatex2Utf["pounds"]		= "&#x00A3;";
	m_mLatex2Utf["ss"]			= "&#x00DF;";
	m_mLatex2Utf["SS"]			= "SS";
	m_mLatex2Utf["ae"]			= "&#x00E6;";
	m_mLatex2Utf["AE"]			= "&#x00C6;";
	m_mLatex2Utf["oe"]			= "&#x0153;";
	m_mLatex2Utf["OE"]			= "&#x0152;";
	m_mLatex2Utf["aa"]			= "&#x0061;&#x030A;";
	m_mLatex2Utf["AA"]			= "&#x0041;&#x030A;";
	m_mLatex2Utf["o"]			= "&#x00F8;";
	m_mLatex2Utf["O"]			= "&#x00D8;";
	m_mLatex2Utf["i"]			= "&#x0131;";
	m_mLatex2Utf["I"]			= "&#x0130;";
	m_mLatex2Utf["l"]			= "&#x0142;";
	m_mLatex2Utf["L"]			= "&#x0141;";
	m_mLatex2Utf["/"]			= "/";
	m_mLatex2Utf["slash"]		= "/";
	m_mLatex2Utf["-"]			= "";
	m_mLatex2Utf["emdash"]		= "-";
	m_mLatex2Utf["LaTeX"]		= "LaTeX";
	
	
	
	m_mLatex2Pair["em"]			= POpenClose ( enclosings_emphopen, enclosings_emphclose );
	m_mLatex2Pair["emph"]		= POpenClose ( enclosings_emphopen, enclosings_emphclose );


	m_mLatex2Elim["slash"]		= true;
	m_mLatex2Elim["emdash"]		= true;
	}


bool CLatexConv::ElimWhitespace ( std::string sLatex )
	{
	sLatex.erase(0,1);
	if ( m_mLatex2Elim.find ( sLatex ) == m_mLatex2Elim.end() )
		return false;
	return true;
	}



std::string CLatexConv::Latex2Utf ( std::string sLatex )
	{
	sLatex.erase(0,1);
	
	MLatex2Utf::iterator mIt = m_mLatex2Utf.find ( sLatex );
	if ( mIt == m_mLatex2Utf.end() )
		{
		return ("\\"+sLatex); 
		}
	
	return mIt->second;
	}

bool CLatexConv::IsEnclosing ( std::string sLatex )
	{
	sLatex.erase(0,1);
	if ( m_mLatex2Pair.find ( sLatex ) == m_mLatex2Pair.end() )
		return false;
	return true;
	}

POpenClose CLatexConv::GetEnclosing ( std::string sLatex )
	{
	sLatex.erase(0,1);

	MLatex2Pair::iterator mIt = m_mLatex2Pair.find ( sLatex );
	if ( mIt == m_mLatex2Pair.end() ) //THIS _CANNOT_ HAPPEN!
		{
		return POpenClose ( enclosings_nothing, enclosings_nothing );
		}
		
	return mIt->second;
	}

