#ifndef PatternSequenceGroup_HPP
#define PatternSequenceGroup_HPP

#include <iostream>
#include <vector>
#include "APattern.hpp"

class PatternSequenceGroup: public APattern
{
public:
    PatternSequenceGroup();
    PatternSequenceGroup(const std::string tag);
    ~PatternSequenceGroup();

    virtual ParseStream::CompileResult compile(ParseStream &ps) const;
    PatternSequenceGroup *addPattern(APattern *pattern);

    struct Data : IData
    {
        Data();
        std::streampos start;
        size_t searchIdx;
        std::vector<ParseResult> children;
    };

private:
    PatternSequenceGroup(const PatternSequenceGroup &rhs);
    PatternSequenceGroup &operator=(const PatternSequenceGroup &rhs);
    std::vector<APattern*> patterns;
};

#endif
