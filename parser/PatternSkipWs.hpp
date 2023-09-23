#ifndef PatternSkipWs_HPP
#define PatternSkipWs_HPP

#include "APattern.hpp"

class PatternSkipWs: public APattern
{
public:
    PatternSkipWs();
    PatternSkipWs(const std::string tag);
    ~PatternSkipWs();

    virtual ParseStream::CompileResult compile(ParseStream &ps) const;

    struct Data : IData
    {
        Data();
        std::string buffer;
    };

private:
    PatternSkipWs(const PatternSkipWs &rhs);
    PatternSkipWs &operator=(const PatternSkipWs &rhs);

    std::string str;
    
};

#endif
