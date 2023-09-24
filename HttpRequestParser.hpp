#ifndef HttpRequestParser_HPP
#define HttpRequestParser_HPP

#include "parser/Parser.hpp"

class HttpRequestParser
{
public:
	HttpRequestParser();
	~HttpRequestParser();
	ParseStream makeStream();

private:
	Parser *createParser();
	Parser *parser;
};

#endif