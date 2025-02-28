#pragma once 

#include <vector>
#include <cstdint>
#include <string>
#include <codecvt>
#include <locale>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#if __cplusplus >= 202002L
#include <format>
#endif

class PString {
public:
    PString();                           
    PString(const PString&) = default;   
    PString(const char* str);
    PString(char ch);
    PString(const std::string& str);                
    virtual ~PString();

    std::string str() const;

#ifdef PSTRING_TEST
    inline PString toString() const { return "\"" + this->str_ + "\""; }
#endif
    
    size_t length() const;
    size_t size() const;
    bool empty() const;

    // C++-style substr() function: like std::string::substr()
    PString substr(size_t start, size_t end=std::string::npos) const;
    
    // Python-style slice
    PString slice(int start = 0, int stop=-1, int step = 1) const;

    PString capitalize() const;
    PString casefold() const;
    PString center(size_t width, char fillchar=' ') const;
    size_t count(const PString& sub, size_t start=0, size_t end=std::string::npos) const;
    std::vector<uint8_t> encode(const PString& encoding="utf-8", const PString& errors="strict") const;
    bool endswith(const PString& other) const;
    PString expandtabs(size_t tabsize=8) const;
    int find(const PString& sub, size_t start=0, size_t end=std::string::npos) const;
    
#if __cplusplus >= 202002L
    template <typename... Args>
    inline PString format(Args&&... args) const{
        return PString(std::vformat(std::string_view(this->str_), std::make_format_args(args...)));
    }
#endif

    int index(const PString& sub, size_t start=0, size_t end=std::string::npos) const;
    bool isalnum() const;
    bool isalpha() const;
    bool isascii() const;
    bool isdecimal() const;
    bool isdigit() const;
    bool isidentifier() const;
    bool islower() const;
    bool isnumeric() const;
    bool isprintable() const;
    bool isspace() const;
    bool istitle() const;
    bool isupper() const;

    template <typename Iterable>
    inline PString join(const Iterable& it) const{
        PString result;
        for (auto iter = it.cbegin(); iter != it.cend(); iter++) {
            result += *iter;
            if (iter + 1 != it.cend()) {
                result += *this;
            }
        }
        return result;
    }

    PString ljust(size_t width, char fillchar=' ') const;
    PString lower() const;
    PString lstrip(const PString& __strp_str = "\r\n\t ") const;
    static std::unordered_map<char,char> maketrans(const std::unordered_map<char,char> & x);
    static std::unordered_map<char,char>  maketrans(const PString& x, const PString& y);
    static std::unordered_map<char,char>  maketrans(const PString& x, const PString& y, const PString &z);
    std::vector<PString> partition(const PString& sep) const;
    PString remoteprefix(const PString& prefix) const;
    PString removesuffix(const PString& suffix) const;
    PString replace(const PString& old, const PString& new_, size_t count=-1) const;
    int rfind(const PString& sub, size_t start=0, size_t end=std::string::npos) const;
    int rindex(const PString& sub, size_t start=0, size_t end=std::string::npos) const;
    PString rjust(size_t width, char fillchar=' ') const;
    std::vector<PString> rpartition(const PString& sep) const;
    std::vector<PString> rsplit(const PString& sep = "", size_t maxsplit = -1) const;
    PString rstrip(const PString& __strp_str = "\r\n\t ") const;
    std::vector<PString> split(const PString &sep = "", size_t maxsplit = -1) const;
    std::vector<PString> splitlines(bool keepends=false) const;
    bool startswith(const PString& other) const;
    PString strip(const PString& __strp_str = "\r\n\t ") const;
    PString swapcase() const;
    PString title() const;
    PString translate (const std::unordered_map<char,char> & table) const; 
    PString upper() const;
    PString zfill(size_t width) const;

    static std::u32string fromUTF8ToUTF32(const std::string& utf8Str);
    static std::string fromUTF32ToUTF8(const std::u32string& utf32Str);


    inline operator std::string() const {
        return std::move(this->str_);
    }

    bool operator==(const PString& other) const;
    bool operator!=(const PString& other) const;
    bool operator<(const PString& other) const;
    inline bool operator>=(const PString& other) const {
        return !(*this < other);
    }
    bool operator>(const PString& other) const;
    inline bool operator<=(const PString& other) const {
        return !(*this > other);
    }
    
    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    // Python-style slice
    PString operator()(int start = 0, int stop = -1, int step = 1) const;
    
    PString operator+(const PString& other) const;
    PString operator+(char32_t other) const;
    PString operator+(const char* other) const;
    PString operator+(const std::string& other) const;
    PString operator+(char other) const;

    
    PString operator*(size_t n) const;
    PString& operator*=(size_t n);

    // +=
    PString& operator+=(const PString& other);
    PString& operator+=(char32_t other);
    PString& operator+=(const char* other);
    PString& operator+=(char other);
    // PString& operator+=(const PAnyWrapper& other);
    PString& operator+=(const std::string& other);
    
    explicit operator bool() const;

    using iterator = std::string::iterator;
    using const_iterator = std::string::const_iterator;
    using reverse_iterator = std::string::reverse_iterator;
    using const_reverse_iterator = std::string::const_reverse_iterator;


    inline iterator begin() noexcept { return str_.begin(); }
    inline iterator end() noexcept { return str_.end(); }

    inline const_iterator begin() const noexcept { return str_.begin(); }
    inline const_iterator end() const noexcept { return str_.end(); }

    inline reverse_iterator rbegin() noexcept { return str_.rbegin(); }
    inline reverse_iterator rend() noexcept { return str_.rend(); }

    inline const_reverse_iterator rbegin() const noexcept { return str_.rbegin(); }
    inline const_reverse_iterator rend() const noexcept { return str_.rend(); }

    inline const_iterator cbegin() const noexcept { return str_.cbegin(); }
    inline const_iterator cend() const noexcept { return str_.cend(); }
    
    size_t hash() const;
    std::string str_;


private:
    friend std::ostream& operator<<(std::ostream& os, const PString& obj) {
        os << obj.str_;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, PString& obj) {
        std::string str;
        is >> str;
        obj = PString(str);
        return is;
    }

};


PString operator+(const char* lhs, const PString& rhs);
PString operator+(const std::string& lhs, const PString& rhs);

namespace std {
    template <>
    struct hash<PString> {
        std::size_t operator()(const PString& k) const {
            return hash<std::string>()(k.str_);
        }
    };
}

#if __cplusplus >= 202002L
template <>
struct std::formatter<PString> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }
    auto format(const PString& pstr, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "{}", static_cast<std::string>(pstr));
    }
};
#endif




#ifdef PSTRING_TEST

inline std::ostream& operator<<(std::ostream& os, const std::vector<PString>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i].toString();
        if (i != vec.size() - 1) os << ", ";
    }
    os << "]";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const std::unordered_map<char, char>& map) {
    os << "{";
    for (auto it = map.begin(); it != map.end(); ++it) {
        os << '\'' << it->first << ": " << '\'' << it->second;
        if (std::next(it) != map.end()) os << ", ";
    }
    os << "}";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const std::vector<uint8_t>& vec) {
    std::ios::fmtflags old_flags = os.flags();
    char old_fill = os.fill();
    std::streamsize old_width = os.width();

    os << "b\"";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << "\\x" 
           << std::hex
           << std::setw(2) << std::setfill('0') 
           << static_cast<int>(vec[i]);
    }
    os << "\"";

    os.flags(old_flags);
    os.fill(old_fill);
    os.width(old_width);

    return os;
}
#endif 


