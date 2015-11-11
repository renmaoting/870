#include <cstring>
#include <sstream>
#include "parseXML.h"

void ParseXML::parseXML() {
  parser = XML_ParserCreate(NULL);
  if (!parser) {
    throw string("Couldn't allocate memory for parser");
  }

  XML_SetUserData(parser, this);
  XML_SetElementHandler(parser, wrapper4Start, wrapper4End);
  XML_SetCharacterDataHandler(parser, wrapper4Chars);
  std::fstream in;
  in.open(filename.c_str(), std::ios::in);
  if (!in) { 
    throw string("Cannot open xml file: ")+filename;
  }

  int length = 0;
  in.getline(buff, BUFSIZE);
  while ( true ) {
    if (! XML_Parse(parser, buff, strlen(buff), length)) {
      std::cout << "Parse error at line "
	         << XML_GetCurrentLineNumber(parser)
	         << XML_ErrorString(XML_GetErrorCode(parser))
           << std::endl;
      throw string("Couldn't parse file: ") + filename;
    }

    if ( in.eof() ) break;
    else in.getline(buff, BUFSIZE);
  }
}

void ParseXML::displayData() const {
  std::map<string, string>::const_iterator ptr = xmlData.begin();
  while ( ptr != xmlData.end() ) {
    std::cout << '(' << ptr->first << ", " 
                     << ptr->second << ')' << std::endl;
    ++ptr;
  }
}

std::string ParseXML::makeTag(const std::string& name) const {
  std::string tagName;
  for (unsigned int i = 1; i < tagNames.size()-1; ++i) {
    tagName += tagNames[i]+'/';
  }
  tagName += tagNames[ tagNames.size()-1 ];
  tagName += std::string("/")+name;
  return tagName;
}

std::string ParseXML::makeTag() const {
  std::string tagName;
  for (unsigned int i = 1; i < tagNames.size()-1; ++i) {
    tagName += tagNames[i]+'/';
  }
  tagName += tagNames[ tagNames.size()-1 ];
  return tagName;
}

void ParseXML::start(const char *el, const char *attr[]) {
  tagNames.push_back(el);
  for (int i = 0; attr[i]; i += 2) {
    xmlData.insert(std::make_pair(makeTag(attr[i]), attr[i+1]));
  }
}

void ParseXML::end(const char *tagEnd) {
  if ( tagEnd != tagNames.back() ) { 
    throw std::string("Tags ") + tagEnd+" and "+tagNames.back()+
          std::string(" don't match");
  }
  tagNames.pop_back();
}

void ParseXML::stripTrailWhiteSpace(string& str) const {
  int length = str.size();   
  int i = length-1;
  while (i >= 0) { 
    if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t') {
      break;
    }
    else if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') {
      str.erase(i, 1);
    }
    --i;
  }
}

void ParseXML::chars(const char *text, int textlen) {
  // The text is not zero terminated; thus we need the  length:
  string str(text, textlen);
  // The text is likely to have trailing white space, e.g. newline, etc
  stripTrailWhiteSpace(str);
  if ( str.size() ) {
    xmlData.insert(std::pair<string,string>(makeTag(), str));
  }
}

void ParseXML::
wrapper4Start(void *data, const char *el, const char **attr) {
  ParseXML * parser = static_cast<ParseXML*>(data);
  parser->start(el, attr);
}

void ParseXML::wrapper4End(void *data, const char *el) {
  ParseXML * parser = static_cast<ParseXML*>(data);
  parser->end(el);
}

void ParseXML::wrapper4Chars(void *data, const char *text, int textlen) {
  ParseXML * parser = static_cast<ParseXML*>(data);
  parser->chars(text, textlen);
}

