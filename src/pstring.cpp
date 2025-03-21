#include <codecvt>
#include <locale>
#include <stdexcept>
#include <unordered_set>
#include <vector>
#include <string>
#include "pstring.h"




PString::PString() {}

PString::PString(const char *str){
    str_ = (std::string(str));
}

PString::PString(char ch){
    str_ = ch;
}

PString::PString(const std::string &str){
    str_ = str;
}


PString::~PString() {}

std::string PString::str() const {
    return str_;
}


size_t PString::length() const {
    return str_.size();
}

size_t PString::size() const {
    return str_.size();
}

bool PString::empty() const {
    return str_.empty();
}

PString PString::repr() const {
    PString result = "\'";

    const std::unordered_map<char, PString> c_map = {
        {'\t', "\\t"},
        {'\n', "\\n"},
        {'\r', "\\r"},
        {'\\', "\\\\"},
        {'\'', "\\\'"},
    };

    for (char c : *this){
        auto it = c_map.find(c);
        if (it != c_map.end()){
            result += it->second;
        }
        else if( (static_cast<unsigned char>(c) >= 0x00 && static_cast<unsigned char>(c) <= 0x08) ||
                 (static_cast<unsigned char>(c) >= 0x0b && static_cast<unsigned char>(c) <= 0x0c) ||
                 (static_cast<unsigned char>(c) >= 0x0e && static_cast<unsigned char>(c) <= 0x1f) ||

                 // In Python, there should be c <= 0xa0, however, we do not suppose to support it
                //  (static_cast<unsigned char>(c) >= 0x7f && static_cast<unsigned char>(c) <= 0xa0)
                 (static_cast<unsigned char>(c) >= 0x7f)
        ){
            result += "\\x";
            auto bit1 = static_cast<unsigned char>(c) / 16;
            auto bit2 = static_cast<unsigned char>(c) % 16;
            result += static_cast<char> (bit1 >= 10 ? (bit1-10 + 'a') : bit1 + '0');
            result += static_cast<char> (bit2 >= 10 ? (bit2-10 + 'a') : bit2 + '0');
        }
        else {
            result += c;
        }
    }
    result += "\'";
    return result;
}

PString PString::lstrip(const PString &__strp_str) const {
    size_t pos = str_.find_first_not_of(__strp_str.str_);
    if(pos == std::string::npos){
        return PString();
    }
    return PString(str_.substr(pos));
}

PString PString::rstrip(const PString &__strp_str) const {
    size_t pos = str_.find_last_not_of(__strp_str.str_);
    if(pos == std::string::npos){
        return PString ();
    }
    return PString(str_.substr(0, pos + 1));
}

PString PString::strip(const PString &__strp_str) const {
    return lstrip(__strp_str).rstrip(__strp_str);
}

bool PString::startswith(const PString &prefix) const {
    return str_.rfind(prefix.str_, 0) == 0;
}

bool PString::startswith(const std::vector<PString>& prefixs) const {
    for (auto &s : prefixs){
        if (startswith(s))
            return true;
    }
    return false;
}

bool PString::endswith(const PString &suffix) const {

    if (suffix.str_.size() > str_.size())
    {
        return false;
    }
    return str_.compare(str_.size() - suffix.str_.size(),
                            suffix.str_.size(),
                            suffix.str_) == 0;
}

bool PString::endswith(const std::vector<PString> &suffixes) const {
    for (auto &s : suffixes){
        if (endswith(s))
            return true;
    }
    return false;
}

PString PString::lower() const {
    std::string lowerStr;
    for (char c : str_)
    {
        lowerStr.push_back(static_cast<char>(std::towlower(static_cast<wint_t>(c))));
    }
    return PString(lowerStr);
}

PString PString::upper() const {
    std::string upperStr;
    for (char c : str_)
    {
        upperStr.push_back(static_cast<char>(std::towupper(static_cast<wint_t>(c))));
    }
    return PString(upperStr);
}

std::vector<PString> PString::split(const PString &sep, size_t maxsplit) const {

    size_t pos = 0;
    size_t prevPos = 0;
    size_t cnt = 0;
    std::vector<PString> result;
    if (sep.length() == 0) {
        const std::unordered_set<char> chs= {' ', '\t', '\n', '\r', '\v', '\f'};
        while (cnt++ < maxsplit && pos < str_.size()) {
            while (pos < str_.size() && chs.find(str_[pos]) != chs.end()) {
                pos++;
            }
            prevPos = pos;

            while (pos < str_.size() && chs.find(str_[pos]) == chs.end()) {
                pos++;
            }

            if (prevPos < pos) {
                result.push_back(PString(str_.substr(prevPos, pos - prevPos)));
            }
        }

        while (pos < str_.size() && chs.find(str_[pos]) != chs.end()) {
            pos++;
        }
        if (pos < str_.size()) {
            result.push_back(PString(str_.substr(pos)));
        }

        return result;
        
    }


    while (cnt++ < maxsplit && (pos = str_.find(sep.str_, prevPos)) != std::string::npos)
    {
        result.push_back(PString(str_.substr(prevPos, pos - prevPos)));
        prevPos = pos + sep.str_.size();
    }
    if (prevPos <= str_.size())
    {
        result.push_back(PString(str_.substr(prevPos)));
    }
    return result;
}

PString PString::capitalize() const {
    if (str_.empty())
    {
        return PString();
    }
    return PString(static_cast<char>(std::toupper(str_[0]))) + PString(str_.substr(1)).lower();
}

PString PString::casefold() const {
    return lower(); // TODO
}

PString PString::center(size_t width, char fillchar) const {
    if (width <= str_.size())
    {
        return *this;
    }
    size_t padSize = width - str_.size();
    size_t padLeft = padSize / 2;
    size_t padRight = padSize - padLeft;
    return PString(std::string(padLeft, fillchar) + str_ + std::string(padRight, fillchar));
}

PString PString::substr(size_t _pos, size_t _n) const {
    return PString(str_.substr(_pos, _n));
}


PString PString::slice(int start, int stop, int step) const {
    const int size = str_.size();
    if (stop > size) stop = size;
    start = start < 0 ? size + start : start;
    stop = stop < 0 ? size + stop : stop;
    if (step == 0)
        throw std::invalid_argument("PString: slice step cannot be zero");

    if (size == 0 || (step > 0 ? start > stop : start < stop)) return PString(); 
    if (step == 1) return substr(start, stop - start);
    
    if (start < 0 || start > size || stop < 0 || stop > size)
    {
        throw std::out_of_range("PString: index out of range");
    }

    std::string result;
    result.reserve((stop - start) / step + 1);
    for(int i = start; (step > 0 ? i < stop : i > stop); i += step){
        result.push_back(str_[i]);
    }
    return PString(result);
}


size_t PString::count(const PString &sub, size_t start, size_t end) const {
    size_t count = 0;
    size_t pos = start;
    while ((pos = str_.substr(start, end - start).find(sub.str_, pos)) != std::string::npos)
    {
        if (pos >= end)
            break;
        count++;
        pos += sub.str_.length();
    }
    return count;
}

int PString::find(const PString &sub, size_t start, size_t end) const {
    size_t pos = str_.substr(start, end - start).find(sub.str_);
    if (pos == std::string::npos)
        return -1;
    return pos;
}

int PString::index(const PString &sub, size_t start, size_t end) const {
    size_t pos = find(sub, start, end);
    if (pos == -1){
        throw std::invalid_argument("substring not found");
    }   
    return pos;
}

bool PString::isalnum() const {
    if (str_.length() == 0)
        return false;
    for (auto c : str_)
    {
        if (!std::isalnum(c))
            return false;
    }
    return true;
}

bool PString::isalpha() const {
    if (str_.length() == 0)
        return false;
    for (auto c : str_)
    {
        if (!std::isalpha(c))
            return false;
    }
    return true;
}

bool PString::isascii() const {
    if (str_.length() == 0)
        return false;
    for (auto c : str_)
    {
        if (c > 0x7f)
            return false;
    }
    return true;
}

bool PString::isdecimal() const {
    if (str_.length() == 0)
        return false;
    for (auto c : str_)
    {
        if (!std::isdigit(c))
            return false; // TODO
    }
    return true;
}

bool PString::isdigit() const {
    if (str_.length() == 0)
        return false;
    for (auto c : str_)
    {
        if (!std::isdigit(c))
            return false;
    }
    return true;
}

bool PString::isidentifier() const {
    if (str_.length() == 0)
        return false;
    if (std::isdigit(str_[0]))
        return false;
    for (auto c : str_.substr(1))
    {
        if (!std::isalnum(c) && c != '_')
            return false;
    }
    return true;
}

bool PString::islower() const {
    if (str_.length() == 0)
        return false;
    bool cased = false;
    for (auto c : str_)
    {
        if (std::isalpha(c))
        {
            if (!std::islower(c))
                return false;
            cased = true;
        }
    }
    return cased;
}

bool PString::isnumeric() const {
    if (str_.length() == 0)
        return false;
    for (auto c : str_)
    {
        if (!std::isdigit(c))
            return false; // TODO
    }
    return true;
}

bool PString::isprintable() const {
    if (str_.length() == 0)
        return true;
    for (auto c : str_)
    {
        if (!std::isprint(c))
            return false;
    }
    return true;
}

bool PString::isspace() const
{
    if (str_.length() == 0)
        return false;
    for (auto c : str_)
    {
        if (!std::isspace(c))
            return false;
    }
    return true;
}

bool PString::istitle() const
{
    bool cased = false;
    for (size_t i = 0; i < str_.size(); i++)
    {
        if (!std::isalpha(str_[i]))
        {
            cased = false;
            continue;
        }
        if (std::isupper(str_[i]))
        {
            if (cased)
                return false;
            cased = true;
        }
        else if (std::islower(str_[i]))
        {
            if (!cased)
                return false;
        }
    }
    return cased;
}

bool PString::isupper() const
{
    if (str_.length() == 0)
        return false;
    bool cased = false;
    for (auto c : str_)
    {
        if (std::isalpha(c))
        {
            if (!std::isupper(c))
                return false;
            cased = true;
        }
    }
    return cased;
}

PString PString::ljust(size_t width, char fillchar) const
{
    if (width <= str_.size())
    {
        return *this;
    }
    size_t padSize = width - str_.size();
    return PString(str_ + std::string(padSize, fillchar));
}

PString PString::rjust(size_t width, char fillchar) const
{
    if (width <= str_.size())
    {
        return *this;
    }
    size_t padSize = width - str_.size();
    return PString(std::string(padSize, fillchar) + str_);
}

std::unordered_map<char,char> PString::maketrans(const std::unordered_map<char,char> &x)
{
    return x; // TODO
}

std::unordered_map<char,char> PString::maketrans(const PString &x, const PString &y)
{
    std::unordered_map<char,char> result;
    if (x.length() != y.length())
    {
        throw std::runtime_error("the first two maketrans arguments must have equal length");
    }
    for (size_t i = 0; i < x.length(); i++)
    {
        result[x[i]] = y[i];
    }
    return result;
}

std::unordered_map<char,char> PString::maketrans(const PString &x, const PString &y, const PString &z)
{
    std::unordered_map<char,char> result;
    if (x.length() != y.length() || x.length() != z.length())
    {
        throw std::runtime_error("the first two maketrans arguments must have equal length");
    }
    for (size_t i = 0; i < x.length(); i++)
    {
        result[x[i]] = y[i];
    }
    for (size_t i = 0; i < z.length(); i++)
    {
        result[z[i]] = '\0';
    }
    return result;
}


std::vector<PString> PString::partition(const PString &sep) const
{
    std::vector<PString> result;
    size_t pos = find(sep);
    if (pos == -1)
    {
        result.push_back(*this);
        result.push_back(PString());
        result.push_back(PString());
        return result;
    }
    result.push_back(substr(0, pos));
    result.push_back(sep);
    result.push_back(substr(pos + sep.length()));
    return result;
}

PString PString::removeprefix(const PString &prefix) const
{
    if (startswith(prefix))
    {
        return substr(prefix.length());
    }
    return *this;
}

PString PString::removesuffix(const PString &suffix) const
{
    if (endswith(suffix))
    {
        return substr(0, length() - suffix.length());
    }
    return *this;
}

PString PString::replace(const PString &old, const PString &new_, size_t count) const
{
    PString result;
    size_t pos = 0;
    size_t prevPos = 0;
    while ((pos = str_.find(old.str_, prevPos)) != std::string::npos)
    {
        result += PString(str_.substr(prevPos, pos - prevPos));
        result += new_;
        prevPos = pos + old.str_.size();
        if (count != std::string::npos)
        {
            count--;
            if (count == 0)
            {
                break;
            }
        }
    }
    if (prevPos <= str_.size())
    {
        result += PString(str_.substr(prevPos));
    }
    return result;
}

int PString::rfind(const PString &sub, size_t start, size_t end) const
{
    size_t pos = str_.substr(start, end - start).rfind(sub.str_);
    if (pos == std::string::npos)
        return -1;
    return pos;
}

int PString::rindex(const PString &sub, size_t start, size_t end) const
{
    size_t pos = find(sub, start, end);
    if (pos == -1)
        throw std::runtime_error("substring not found");
    return pos;
}

std::vector<PString> PString::rpartition(const PString &sep) const
{
    std::vector<PString> result;
    size_t pos = rfind(sep);
    if (pos == -1)
    {
        result.push_back(PString());
        result.push_back(PString()),
        result.push_back(*this);
        return result;
    }
    result.push_back(substr(0, pos));
    result.push_back(sep);
    result.push_back(substr(pos + sep.length()));
    return result;
}

std::vector<PString> PString::rsplit(const PString &sep, size_t maxsplit) const {
    size_t pos = 0;
    size_t prevPos = str_.size();
    size_t cnt = 0;
    
    std::vector<PString> result;
    std::vector<PString> result_rev;
    const std::string whitespace = " \t\n\r\v\f";

    if(this->empty() && sep.empty()) return {};
    if(this->empty() && !sep.empty()) return {""};

    if (sep.empty()) {
        while (cnt < maxsplit && prevPos > 0) {
            size_t end = prevPos;
            while (prevPos > 0 && whitespace.find(str_[prevPos - 1]) != std::string::npos) {
                prevPos--;
            }
            if (prevPos == 0) break;

            pos = str_.find_last_of(whitespace, prevPos - 1);
            
            PString segment = this->substr(pos + 1, prevPos - pos - 1).rstrip();
            if (!segment.empty()) {
                result_rev.push_back(segment);
                cnt++;
            }
            prevPos = pos;
            if(prevPos == std::string::npos) break;
        }

        if (prevPos > 0 && prevPos != std::string::npos) {
            PString remaining = this->substr(0, prevPos).rstrip();
            if (!remaining.empty()) {
                result_rev.push_back(remaining);
            }
        }
    } else {
          while (cnt < maxsplit) {
            pos = str_.rfind(sep.str_, prevPos - 1);
            if (pos == std::string::npos) break;

            result_rev.emplace_back(str_.substr(pos + sep.length(), prevPos - pos - sep.length()));
            prevPos = pos;
            if(prevPos == 0) break;
            cnt++;
        }
        if(prevPos != std::string::npos) {
            result_rev.emplace_back(str_.substr(0, prevPos));
        }
    }

    for (auto it = result_rev.rbegin(); it != result_rev.rend(); ++it) {
        result.push_back(*it);
    }
    return result;
}
std::vector<PString> PString::splitlines(bool keepends) const
{
    std::vector<PString> result;
    size_t pos = 0;
    size_t prevPos = 0;
    if(str_.empty()){
        return result;
    }
    // support \r \n \r\n \v \f \x1c \x1d \x1e \x85
    while ((pos = str_.find_first_of("\r\n\v\f\x1c\x1d\x1e\x85", prevPos)) != std::string::npos)
    {
        if (str_[pos] == '\r' && pos + 1 < str_.size() && str_[pos + 1] == '\n')
        {
            if (keepends){
                result.push_back(PString(str_.substr(prevPos, pos - prevPos + 2)));
            }
            else{
                result.push_back(PString(str_.substr(prevPos, pos - prevPos)));
            }
            pos++;
        }
        else{
            if (keepends){
                result.push_back(PString(str_.substr(prevPos, pos - prevPos + 1)));
            }
            else{
                result.push_back(PString(str_.substr(prevPos, pos - prevPos)));
            }
        }
        prevPos = pos + 1;
    }
    if (prevPos < str_.size())
    {
        result.push_back(PString(str_.substr(prevPos)));
    }
    return result;
}

PString PString::swapcase() const
{
    std::string swapcaseStr;
    for (char32_t c : str_)
    {
        if (std::islower(c))
        {
            swapcaseStr.push_back(std::towupper(c));
        }
        else if (std::isupper(c))
        {
            swapcaseStr.push_back(std::towlower(c));
        }
        else
        {
            swapcaseStr.push_back(c);
        }
    }
    return PString(swapcaseStr);
}

PString PString::title() const
{
    std::string titleStr;
    bool start = false;
    for (char32_t c : str_)
    {
        if(!std::isalpha(c)){
            titleStr.push_back(c);
            start = false;
            continue;
        }else{
            if(!start){
                titleStr.push_back(std::towupper(c));
                start = true;
            }else{
                titleStr.push_back(std::towlower(c));
            }
        }
    }
    return PString(titleStr);
}

PString PString::translate(const std::unordered_map<char, char> &table) const {
    PString result;
    for (auto c : str_)
    {
        if(table.count(c)){
            result += table.at(c);
        }else{
            result += c;
        }
    }
    return result;
}

PString PString::zfill(size_t width) const {
    if (width <= str_.size())
    {
        return *this;
    }
    size_t padSize = width - str_.size();
    if (str_[0] == '-' || str_[0] == '+')
    {
        return PString(str_.substr(0, 1) + std::string(padSize, '0') + str_.substr(1));
    }
    return PString(std::string(padSize, '0') + str_);
}

PString PString::expandtabs(size_t tabsize) const {
    PString result;
    size_t cnt = 0;
    if(tabsize == 0) {
        return this->replace("\t", "");
    }
    for (auto c : str_) {
        if (c == '\t') {
            size_t space_count = tabsize - (cnt % tabsize);
            result += PString(" ") * space_count;
            cnt += space_count;
        } else {
            result += c;
            if (c == '\n' || c == '\r') {
                cnt = 0;
            } else {
                cnt++;
            }
        }
    }
    return result;
    return result;
}

std::vector<uint8_t> PString::encode(const PString &encoding, const PString &errors) const {
    std::vector<uint8_t> result;

    // The string in `sapy` is processed in UTF32 format, so we convert it to UTF32
    std::u32string str_ = fromUTF8ToUTF32(this->str_);
    std::string encoding_str = encoding.str_;

    if (encoding_str == "utf-8") {
        // UTF-32 to UTF-8 conversion
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        try {
            std::string utf8_str = converter.to_bytes(str_);
            result.assign(utf8_str.begin(), utf8_str.end());
        } catch (const std::range_error &e) {
            if (errors == "strict") {
                throw std::runtime_error("Encoding error: " + std::string(e.what()));
            } else if (errors == "ignore") {
                // Ignore errors, return partial result
            } else {
                throw std::runtime_error("Unsupported error handling mode: " + errors);
            }
        }

    } else if (encoding_str == "utf-16") {
        // UTF-32 to UTF-16 conversion with BOM (Little Endian)
        std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> converter;
        try {
            // Add BOM for UTF-16 Little Endian
            result.push_back(0xFF);
            result.push_back(0xFE);

            for (char32_t ch : str_) {
                if (ch <= 0xFFFF) { // BMP character
                    result.push_back(static_cast<uint8_t>(ch & 0xFF));
                    result.push_back(static_cast<uint8_t>((ch >> 8) & 0xFF));
                } else { // Non-BMP character, encode as surrogate pair
                    char32_t surrogate = ch - 0x10000;
                    char16_t high = static_cast<char16_t>((surrogate >> 10) + 0xD800);
                    char16_t low = static_cast<char16_t>((surrogate & 0x3FF) + 0xDC00);

                    result.push_back(static_cast<uint8_t>(high & 0xFF));
                    result.push_back(static_cast<uint8_t>((high >> 8) & 0xFF));
                    result.push_back(static_cast<uint8_t>(low & 0xFF));
                    result.push_back(static_cast<uint8_t>((low >> 8) & 0xFF));
                }
            }
        } catch (const std::range_error &e) {
            if (errors == "strict") {
                throw std::runtime_error("Encoding error: " + std::string(e.what()));
            } else if (errors == "ignore") {
                // Ignore errors, return partial result
            } else {
                throw std::runtime_error("Unsupported error handling mode: " + errors);
            }
        }

    } else if (encoding_str == "utf-32") {
        // UTF-32 encoding with BOM (Little Endian)
        result.push_back(0xFF);
        result.push_back(0xFE);
        result.push_back(0x00);
        result.push_back(0x00);

        for (char32_t ch : str_) {
            uint8_t bytes[4];
            bytes[0] = static_cast<uint8_t>(ch & 0xFF);         // Lowest byte
            bytes[1] = static_cast<uint8_t>((ch >> 8) & 0xFF);
            bytes[2] = static_cast<uint8_t>((ch >> 16) & 0xFF);
            bytes[3] = static_cast<uint8_t>((ch >> 24) & 0xFF); // Highest byte
            result.insert(result.end(), bytes, bytes + 4);
        }
    } else {
        throw std::runtime_error("Unsupported encoding: " + encoding);
    }

    return result;
}


std::u32string PString::fromUTF8ToUTF32(const std::string &utf8Str) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    return converter.from_bytes(utf8Str);
}

std::string PString::fromUTF32ToUTF8(const std::u32string &utf32Str) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    return converter.to_bytes(utf32Str);
}

bool PString::operator==(const PString &other) const {
    return str_ == other.str_;
}

bool PString::operator!=(const PString &other) const {
    return !(*this == other);
}

bool PString::operator<(const PString &other) const {
    return str_ < other.str_;
}

bool PString::operator>(const PString &other) const {
    return str_ > other.str_;
}

char& PString::operator[](size_t index) {
    if (index >= str_.size()){
        throw std::out_of_range("PString: index out of range");
    }
    return str_[index];
}

const char& PString::operator[](size_t index) const {
    if (index >= str_.size()){
        throw std::out_of_range("PString: index out of range");
    }
    return str_[index];
}

PString PString::operator()(int start, int stop, int step) const {
    return slice(start, stop, step);
}

PString PString::operator+(const PString &other) const {
    return PString(str_ + other.str_);
}

PString PString::operator+(char32_t other) const {
    return PString(str_ + std::string(1, other));
}

PString PString::operator+(const char *other) const {
    return *this + PString(other);
}

PString PString::operator+(const std::string &other) const {
    return *this + PString(other);
}

PString PString::operator+(char other) const {
    std::string tmp = str_ + std::string(1, other);
    return PString(tmp);
}

PString PString::operator*(size_t n) const
{
    std::string newStr;
    newStr.reserve(str_.size() * n);
    for (size_t i = 0; i < n; i++)
    {
        newStr += str_;
    }
    return PString(newStr);
}

PString &PString::operator*=(size_t n)
{
    std::string newStr;
    newStr.reserve(str_.size() * n);
    for (size_t i = 0; i < n; i++)
    {
        newStr += str_;
    }
    str_ = newStr;
    return *this;
}

// +=
PString &PString::operator+=(const PString &other)
{
    str_ += other.str_;
    return *this;
}

PString &PString::operator+=(char32_t other)
{
    str_ + fromUTF32ToUTF8(std::u32string(1, other));
    return *this;
}

PString &PString::operator+=(const char *other)
{
    *this = *this + PString(other);
    return *this;
}

PString &PString::operator+=(char other)
{
    str_.push_back(static_cast<char32_t>(other));
    return *this;
}


PString &PString::operator+=(const std::string &other)
{
    *this = *this + PString(other);
    return *this;
}

PString::operator bool() const{
    return str_.size() > 0;
}


size_t PString::hash() const
{
    std::hash<std::string> hasher;
    return hasher(str_);
}

PString operator+(const char *lhs, const PString &rhs)
{
    return PString(lhs) + rhs;
}

PString operator+(const std::string &lhs, const PString &rhs)
{
    return PString(lhs) + rhs;
}


PString operator+(char lhs, const PString& rhs)
{
    return PString(lhs) + rhs;
}