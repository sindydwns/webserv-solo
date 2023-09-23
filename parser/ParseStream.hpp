#ifndef ParseCoroutine_HPP
#define ParseCoroutine_HPP

#include <sstream>
#include <stack>
#include <algorithm>
#include "IData.hpp"
#include "ParseResult.hpp"

class APattern;
typedef enum e_state {
    INIT = 0,
    PENDING = 1,
    INVALID = 2,
    VALID = 3,
    VALID_NO_RES = 4,
} ParseState;
class ParseStream : public std::stringstream
{
public:
    ParseStream();
    ParseStream(const ParseStream &rhs);
    ParseStream(const APattern *pattern);
    ~ParseStream();
    ParseStream &operator=(const ParseStream &rhs);

    struct CompileResult
    {
        CompileResult(ParseState state);
        CompileResult(ParseState state, ParseResult result);
        ParseState state;
        ParseResult result;
    };

    bool isStreamEoF() const;
    bool isState(ParseState s) const;
    void turnOnStreamEoF();
    void init();
    IData *load();
    CompileResult yield(IData *data);
    CompileResult yield(IData *data, std::streampos &pos);
    CompileResult done(IData *deleteTarget);
    CompileResult done(ParseResult res, IData *deleteTarget);
    CompileResult drop(IData *deleteTarget);
    CompileResult drop(std::streampos &pos, IData *deleteTarget);

    bool next(std::string &str);
    ParseResult &getResult();

private:
    std::stack<IData*> indexer;
    const APattern *const pattern;
    ParseResult result;

    bool streamEoF;

    ParseState state;

};

#endif
