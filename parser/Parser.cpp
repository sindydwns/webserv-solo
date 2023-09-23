#include "Parser.hpp"

Parser::Parser(): pattern(NULL) { }
Parser::Parser(const APattern *pattern): pattern(pattern) { }
Parser::~Parser()
{
    delete this->pattern;
}
Parser::Parser(const Parser &rhs)
{
    *this = rhs;
}

Parser &Parser::operator=(const Parser &rhs)
{
    if (this == &rhs) return *this;
    return *this;
}

void Parser::setPattern(const APattern *pattern)
{
    if (this->pattern != NULL) delete this->pattern;
    this->pattern = pattern;
}

ParseStream Parser::makeStream()
{
    if (this->pattern == NULL) return ParseStream();
    return ParseStream(this->pattern);
}
