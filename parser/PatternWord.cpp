#include "PatternWord.hpp"

PatternWord::PatternWord()
    : APattern(true, false) { }
PatternWord::PatternWord(const std::string tag)
    : APattern(true, false) { setTag(tag); }
PatternWord::PatternWord(const PatternWord &rhs)
    : APattern(true, false) { *this = rhs; }
PatternWord::~PatternWord() { }
PatternWord &PatternWord::operator=(const PatternWord &rhs)
{
    if (this == &rhs) return *this;
    return *this;
}

ParseStream::CompileResult PatternWord::compile(ParseStream &ps) const
{
    Data *data = dynamic_cast<Data*>(ps.load());
    if (data == NULL) data = new Data();

    if (data->start == std::streampos(-1)) {
        data->start = ps.tellg();
        if (ps.fail() && ps.isStreamEoF()) return ps.drop(data);
        if (ps.fail()) return ps.yield(data);
    }

    char c;
    while (data->modeSkipWs) {
        ps >> c;
        if (ps.fail() && ps.isStreamEoF()) return ps.drop(data->start, data);
        if (ps.fail()) return ps.yield(data);
        if (std::isspace(c)) data->ws.push_back(c);
        else {
            ps.unget();
            data->modeSkipWs = false;
        }
    }

    while (true) {
        ps >> c;
        if (ps.fail() && ps.isStreamEoF()) return ps.drop(data->start, data);
        if (ps.fail()) return ps.yield(data);
        if (std::isspace(c) == false) data->buffer.push_back(c);
        else {
            ps.unget();
            break;
        }
    }

    if (data->buffer.empty()) return ps.drop(data->start, data);
    if (this->useTrim) return ps.done(ParseResult(data->buffer, tag), data);
    return ps.done(ParseResult(data->ws + data->buffer, tag), data);
}

PatternWord::Data::Data() : start(std::streampos(-1)), modeSkipWs(true) { }
