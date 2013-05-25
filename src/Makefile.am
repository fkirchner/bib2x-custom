lib_LTLIBRARIES = libodb.la
bin_PROGRAMS = bib2x

AM_CXXFLAGS = -Wall -g -O2
INCLUDES = -I../include -I$(includedir)
AM_CFLAGS   = -D_REENTRANT 
EXTRA_DIST = bib.tab.h template.tab.h template.l template.y bib.l bib.y yacc_makefile


libodb_la_SOURCES = atomdatabinary.cxx keyname.cxx rope.cxx transaction.cxx stream.cxx root.cxx reason.cxx object.cxx class.cxx atomdata.cxx atom.cxx atomdatastring.cxx atomdatareal.cxx atomdatainteger.cxx atomdata3dpoint.cxx atomdatafilelink.cxx atomdatafile.cxx odb.cxx  
libodb_la_LDFLAGS = -lstdc++ 

bib2x_SOURCES = main.cxx template.yy.cxx template.tab.cxx template.cxx entries.cxx bib.tab.cxx lex.yy.cxx bib.cxx output.cxx outputhtml.cxx latexconv.cxx utfconv.cxx
bib2x_LDADD = libodb.la


