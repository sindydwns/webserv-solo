#include "ParseResult.hpp"

ParseResult::ParseResult() {}
ParseResult::ParseResult(std::string match)
    : match(match) {}
ParseResult::ParseResult(std::string match, const std::string tag)
    : tag(tag), match(match) {}
ParseResult::ParseResult(std::vector<ParseResult> children)
    : children(children) {}
ParseResult::ParseResult(std::vector<ParseResult> children, const std::string tag)
    : tag(tag), children(children) {}
ParseResult::ParseResult(std::string match, std::vector<ParseResult> children)
    : match(match), children(children) {}
ParseResult::ParseResult(std::string match, std::vector<ParseResult> children, const std::string tag)
    : tag(tag), match(match), children(children) {}
ParseResult::ParseResult(const ParseResult &rhs)
    : tag(rhs.tag), match(rhs.match), children(rhs.children) {}
ParseResult::~ParseResult() { }
ParseResult &ParseResult::operator=(const ParseResult &rhs)
{
    if (this == &rhs) return *this;
    this->~ParseResult();
    new (this) ParseResult(rhs);
    return *this;
}

std::string ParseResult::toString() const
{
    return toString(0);
}
std::string ParseResult::toString(int depth) const
{
    if (getChildren().size() == 0) {
        std::string res = "[ ";
        if (this->tag.empty() == false) {
            res += "tag: \"" + this->tag + "\", ";
        }
        res += "match: \"" + this->match + "\" ]";
        return std::string(depth * 2, ' ') + res;
    }
    std::string res = std::string(depth * 2, ' ') + "[\n";
    res += std::string(depth * 2 + 2, ' ') + "tag: \"" + this->tag + "\"\n";
    for (size_t i = 0; i < getChildren().size(); i++) {
        res += getChildren().at(i).toString(depth + 1) + "\n";
    }
    res += std::string(depth * 2, ' ') + "]\n";
    return res;
}
const std::vector<ParseResult> &ParseResult::getChildren() const { return this->children; }

