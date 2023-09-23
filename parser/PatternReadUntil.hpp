#ifndef PatternReadUntil_HPP
#define PatternReadUntil_HPP

#include "APattern.hpp"

class PatternReadUntil: public APattern
{
public:
    PatternReadUntil(const std::string suffix);
    PatternReadUntil(const std::string suffix, const std::string tag);
    PatternReadUntil(const std::string suffix, const std::string stop, const std::string tag);
    ~PatternReadUntil();

    virtual ParseStream::CompileResult compile(ParseStream &ps) const;
    PatternReadUntil *setUseSuffix(bool useSuffix);

    struct Data : IData
    {
        Data();
        std::streampos start;
        std::string buffer;
        size_t strMatchIdx;
        size_t stopMatchIdx;
    };

private:
    PatternReadUntil();
    PatternReadUntil(const PatternReadUntil &rhs);
    PatternReadUntil &operator=(const PatternReadUntil &rhs);

    std::string str;
    std::string stop;
    bool useSuffix;
    
};

#endif
