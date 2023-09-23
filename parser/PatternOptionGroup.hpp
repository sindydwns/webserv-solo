#ifndef PatternOptionGroup_HPP
#define PatternOptionGroup_HPP

#include <iostream>
#include <vector>
#include "APattern.hpp"

class PatternOptionGroup: public APattern
{
public:
    PatternOptionGroup();
    PatternOptionGroup(size_t minMatch);
    PatternOptionGroup(size_t minMatch, const std::string tag);
    PatternOptionGroup(size_t minMatch, size_t maxMatch);
    PatternOptionGroup(size_t minMatch, size_t maxMatch, const std::string tag);
    ~PatternOptionGroup();

    virtual ParseStream::CompileResult compile(ParseStream &ps) const;
    PatternOptionGroup *addPattern(APattern *pattern);

    struct Data : IData
    {
        Data();
        std::streampos start;
        std::streampos cursor;
        size_t searchIdx;
        std::vector<ParseResult> children;
    };

private:
    PatternOptionGroup(const PatternOptionGroup &rhs);
    PatternOptionGroup &operator=(const PatternOptionGroup &rhs);

    std::vector<APattern*> patterns;
    size_t minMatch;
    size_t maxMatch;
};

#endif
