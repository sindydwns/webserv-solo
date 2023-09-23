#include "APattern.hpp"

APattern::APattern() { }
APattern::APattern(bool useTrim, bool useIgnoreCase)
    : useTrim(useTrim), useIgnoreCase(useIgnoreCase) { }
APattern::~APattern() { }
APattern::APattern(const APattern &rhs) { *this = rhs; }
APattern &APattern::operator=(const APattern &rhs) { (void)rhs; return *this; }

const std::string &APattern::getTag() const { return this->tag; }
APattern *APattern::setTag(const std::string &tag) { this->tag = tag; return this; }
APattern *APattern::setUseTrim(bool useTrim) { this->useTrim = useTrim; return this; }
APattern *APattern::setUseIgnoreCase(bool useIgnoreCase) { this->useIgnoreCase = useIgnoreCase; return this; }

std::string APattern::trim(const std::string &str, bool b)
{
    if (b == false) return str;
    std::string::const_iterator begin = str.begin();
    std::string::const_iterator end = str.end();
    for (; begin != str.end(); begin++) {
        if (std::isspace(*begin) == false) break;
    }
    if (begin == end) return std::string();
    for (; --end > begin;) {
        if (std::isspace(*end) == false) break;
    }
    return std::string(begin, end + 1);
}

std::string APattern::toupper(const std::string &str)
{
    std::string copy = str;
    for (std::string::iterator it = copy.begin(); it != copy.end(); it++) {
        *it = std::toupper(*it);
    }
    return copy;
}

std::string APattern::tolower(const std::string &str)
{
    std::string copy = str;
    for (std::string::iterator it = copy.begin(); it != copy.end(); it++) {
        *it = std::tolower(*it);
    }
    return copy;
}

bool APattern::equal(const std::string &str1, const std::string &str2) const
{
    if (this->useIgnoreCase == false) return str1 == str2;
    if (str1.size() != str2.size()) return false;
    for (size_t i = 0; i < str1.size(); i++) {
        if (equal(str1[i], str2[i]) == false) return false;
    }
    return true;
}

bool APattern::equal(const char c1, const char c2) const
{
    if (this->useIgnoreCase == false) return c1 == c2;
    return std::tolower(c1) == std::tolower(c2);
}
