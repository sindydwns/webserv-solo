#include "PatternReadUntil.hpp"
#include <iostream>

PatternReadUntil::PatternReadUntil()
    : APattern(true, false), useSuffix(false) { throw std::logic_error("must string has value"); }
PatternReadUntil::PatternReadUntil(const std::string str)
    : APattern(true, false), str(str), useSuffix(false)  { if (str.empty()) throw std::logic_error("must string has value"); }
PatternReadUntil::PatternReadUntil(const std::string suffix, const std::string tag)
    : APattern(true, false), str(suffix), useSuffix(false) { setTag(tag); }
PatternReadUntil::PatternReadUntil(const std::string suffix, const std::string stop, const std::string tag)
    : APattern(true, false), str(suffix), stop(stop), useSuffix(false) { setTag(tag); }
PatternReadUntil::PatternReadUntil(const PatternReadUntil &rhs) { *this = rhs; }
PatternReadUntil::~PatternReadUntil() {}
PatternReadUntil &PatternReadUntil::operator=(const PatternReadUntil &rhs) { (void)rhs; return *this; }

ParseStream::CompileResult PatternReadUntil::compile(ParseStream &ps) const
{
    Data *data = dynamic_cast<Data*>(ps.load());
    if (data == NULL) data = new Data();

    if (data->start == std::streampos(-1)) {
        data->start = ps.tellg();
        if (ps.fail() && ps.isStreamEoF()) return ps.drop(data);
        if (ps.fail()) return ps.yield(data);
    }

    char c;
    while (true) {
        ps >> c;
        if (ps.fail() && ps.isStreamEoF()) return ps.drop(data->start, data);
        if (ps.fail()) return ps.yield(data);

        data->buffer.push_back(c);

        if (this->str[data->strMatchIdx] == c) data->strMatchIdx++;
        else data->strMatchIdx = 0;

        if (data->strMatchIdx >= this->str.size()) break;

        if (this->stop.size() > 0) {
            if (this->stop[data->stopMatchIdx] == c) data->stopMatchIdx++;
            else data->stopMatchIdx = 0;

            if (data->stopMatchIdx >= this->stop.size()) break;
        }
    }

    if (data->strMatchIdx < this->str.size()) return ps.drop(data->start, data);

    data->buffer = std::string(data->buffer.begin(), data->buffer.end() - this->str.size());
    std::string buffer = APattern::trim(data->buffer, this->useTrim);
    return ps.done(ParseResult(buffer, tag), data);
}

PatternReadUntil *PatternReadUntil::setUseSuffix(bool useSuffix) { this->useSuffix = useSuffix; return this; }

PatternReadUntil::Data::Data() : start(std::streampos(-1)), strMatchIdx(0), stopMatchIdx(0) { }
