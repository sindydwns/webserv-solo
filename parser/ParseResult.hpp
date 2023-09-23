#ifndef ParseResult_HPP
#define ParseResult_HPP

#include <exception>
#include <iostream>
#include <vector>

class ParseResult
{
public:
    ParseResult();
    ParseResult(std::string match);
    ParseResult(std::string match, const std::string tag);
    ParseResult(std::vector<ParseResult> children);
    ParseResult(std::vector<ParseResult> children, const std::string tag);
    ParseResult(std::string match, std::vector<ParseResult> children);
    ParseResult(std::string match, std::vector<ParseResult> children, const std::string tag);
    ParseResult(const ParseResult &rhs);
    virtual ~ParseResult();
    ParseResult &operator=(const ParseResult &rhs);

    std::string toString() const;
    const std::vector<ParseResult> &getChildren() const;

private:
    std::string tag;
    std::string match;
    std::vector<ParseResult> children;

    std::string toString(int depth) const;

};

#endif
