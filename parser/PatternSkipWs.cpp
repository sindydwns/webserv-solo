#include "PatternSkipWs.hpp"

PatternSkipWs::PatternSkipWs()
    : APattern(true, false) { }
PatternSkipWs::PatternSkipWs(const std::string tag)
    : APattern(true, false) { setTag(tag); }
PatternSkipWs::PatternSkipWs(const PatternSkipWs &rhs)
    : APattern(true, false) { *this = rhs; }
PatternSkipWs::~PatternSkipWs() { }
PatternSkipWs &PatternSkipWs::operator=(const PatternSkipWs &rhs)
{
    if (this == &rhs) return *this;
    return *this;
}

ParseStream::CompileResult PatternSkipWs::compile(ParseStream &ps) const
{
    ps.load();

    ps >> std::ws;

    if (ps.eof() == false) return ps.done(NULL);
    if (ps.isStreamEoF()) return ps.yield(NULL);
    return ps.done(NULL);
}

PatternSkipWs::Data::Data() { }
