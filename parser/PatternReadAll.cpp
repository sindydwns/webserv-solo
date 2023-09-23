#include "PatternReadAll.hpp"

PatternReadAll::PatternReadAll()
    : APattern(false, false) { }
PatternReadAll::PatternReadAll(const std::string tag)
    : APattern(false, false) { setTag(tag); }
PatternReadAll::PatternReadAll(const PatternReadAll &rhs)
    : APattern(false, false) { *this = rhs; }
PatternReadAll::~PatternReadAll() { }
PatternReadAll &PatternReadAll::operator=(const PatternReadAll &rhs)
{
    if (this == &rhs) return *this;
    return *this;
}

ParseStream::CompileResult PatternReadAll::compile(ParseStream &ps) const
{
    Data *data = dynamic_cast<Data*>(ps.load());
    if (data == NULL) data = new Data();

    char c;
    while (true) {
        ps >> c;
        if (ps.fail() && ps.isStreamEoF() == false) return ps.yield(data);
        if (ps.fail()) return ps.done(ParseResult(data->buffer, tag), data);
        data->buffer.push_back(c);
    }
    std::string buffer = APattern::trim(data->buffer, this->useTrim);
    return ps.done(ParseResult(buffer, tag), data);
}

PatternReadAll::Data::Data() { }
