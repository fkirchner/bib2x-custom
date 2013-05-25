#ifndef __UTFCONV_H
#define __UTFCONV_H

#include <string>

static const int utf_char_uppercase = 1;
static const int utf_char_lowercase = 2;


std::string TexToUtfCode ( std::string sContent, int nCase = 0 );




#endif

