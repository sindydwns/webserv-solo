#include "PatternEqual.hpp"
#include <iostream>

PatternEqual::PatternEqual()
    : APattern(true, false) { throw std::logic_error("must string has value"); }
PatternEqual::PatternEqual(const std::string str)
    : APattern(true, false), str(str) { if (str.empty()) throw std::logic_error("must string has value"); }
PatternEqual::PatternEqual(const std::string str, const std::string tag)
    : APattern(true, false), str(str)
{
    if (str.empty()) throw std::logic_error("must string has value");
    setTag(tag);
}
PatternEqual::~PatternEqual() {}
PatternEqual::PatternEqual(const PatternEqual &rhs) { *this = rhs; }
PatternEqual &PatternEqual::operator=(const PatternEqual &rhs) { (void)rhs; return *this; }

ParseStream::CompileResult PatternEqual::compile(ParseStream &ps) const
{
    Data *data = dynamic_cast<Data*>(ps.load());
    if (data == NULL) data = new Data();

    if (data->start == std::streampos(-1)) {
        data->start = ps.tellg();
        if (ps.fail() && ps.isStreamEoF()) return ps.drop(data);
        if (ps.fail()) return ps.yield(data);
    }

    char c;
    while (data->buffer.size() < this->str.size()) {
        ps >> c;
        if (ps.fail() && ps.isStreamEoF()) return ps.drop(data->start, data);
        if (ps.fail()) return ps.yield(data);
        data->buffer.push_back(c);
    }

    if (APattern::equal(data->buffer, this->str)) {
        ParseResult res = ParseResult(APattern::trim(data->buffer, this->useTrim), tag);
        return ps.done(res, data);
    }
    return ps.drop(data->start, data);
}

PatternEqual::Data::Data()
    : start(std::streampos(-1)) { }
