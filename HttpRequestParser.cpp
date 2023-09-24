#include "HttpRequestParser.hpp"
#include "parser/PatternSequenceGroup.hpp"
#include "parser/PatternWord.hpp"
#include "parser/PatternReadUntil.hpp"
#include "parser/PatternOptionGroup.hpp"
#include "parser/PatternReadAll.hpp"
#include "parser/PatternEqual.hpp"
#include "parser/Parser.hpp"

HttpRequestParser::HttpRequestParser()
{
	this->parser = createParser();
}

HttpRequestParser::~HttpRequestParser()
{
	delete this->parser;
}

ParseStream HttpRequestParser::makeStream()
{
    return this->parser->makeStream();
}

Parser *HttpRequestParser::createParser()
{
	PatternSequenceGroup *startline = new PatternSequenceGroup("startline");
    startline->addPattern(new PatternWord("method"));
    startline->addPattern(new PatternWord("route"));
    startline->addPattern(new PatternWord("http-version"));
    PatternSequenceGroup *header = new PatternSequenceGroup("header");
    header->addPattern(new PatternReadUntil(":", "\n", "key"));
    header->addPattern(new PatternReadUntil("\n", "value"));
    PatternOptionGroup *headers = new PatternOptionGroup(0, 999, "headers");
    headers->addPattern(header);
    PatternSequenceGroup *req = new PatternSequenceGroup("req");
    req->addPattern(startline);
    req->addPattern(new PatternReadUntil("\n", "nextline"));
    req->addPattern(headers);
    req->addPattern(new PatternReadUntil("\n", "nextline"));
	return new Parser(req);
}
