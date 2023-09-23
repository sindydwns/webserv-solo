#ifndef PatternReadAll_HPP
#define PatternReadAll_HPP

#include "APattern.hpp"

class PatternReadAll: public APattern
{
public:
    PatternReadAll();
    PatternReadAll(const std::string tag);
    ~PatternReadAll();

    virtual ParseStream::CompileResult compile(ParseStream &ps) const;

    struct Data : IData
    {
        Data();
        std::string buffer;
    };

private:
    PatternReadAll(const PatternReadAll &rhs);
    PatternReadAll &operator=(const PatternReadAll &rhs);

    std::string str;
    
};

#endif
