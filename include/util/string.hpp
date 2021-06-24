#pragma once

#include <string>
#include <vector>
#include <sstream>  //for tokenizer
#include <algorithm>
#include <string_view>

#define stringify(name) #name

namespace util
{

    void trim(std::string &);                                   //@returns trimmed std::string, but doesnt modify original string
    std::string trim_copy(const std::string &);                 //@returns trimmed std::string, but doesnt modify original string
    void trimChar(std::string &s, char ch); //Trims out `ch` from both ends
    void replace_all(std::string& str, const std::string& _old, const std::string& _new); //can use boost::algorithm::replace_all also
    void strip(std::string &, char toRemove);                   /*Returns a string without the passed character*/
    std::string strip_copy(const std::string &, char toRemove); /*Returns a string without the passed character*/
    bool icompare(const std::string &s1, const std::string &s2) noexcept;

    bool starts_with(const std::string& s, std::string_view start_str);
    std::vector< std::string > tokenizeIt(const std::string& dir, char sep);
	std::vector<std::string> split(const std::string& s, char delim = ','); //similar to tokenizeIt(), but this is meant to consider double quotes too

} // namespace util

    //DEFINITIONS
inline void util::trim(std::string &s)
{
    auto i = s.end() - 1;
    for (; i != s.begin(); --i)
    {
        if (!isspace(static_cast<unsigned char>(*i)))
        {
            ++i;
            break;
        }
    }
    s.erase(i, s.end());

    i = s.begin();
    for (; i != s.end(); ++i)
    {
        if (!isspace(static_cast<unsigned char>(*i)))
        {
            break;
        }
    }
    s.erase(s.begin(), i);

        //earlier one, but has bug
    // s.erase(std::find_if(s.begin(), s.end(), isspace), s.rend().base());
    // s.erase(std::find_if(s.rbegin(), s.rend(), isspace).base(), s.end());
}

inline std::string util::trim_copy(const std::string &s)
{
    std::string str_out(s);
    util::trim(str_out);
    return str_out;
}

inline void util::trimChar(std::string &s, char ch){
    while (s.back() == ch)
    {
        s.pop_back();
    }
    if(s.back() == ch){
        s.pop_back();
    }
}

inline void util::replace_all(std::string& s, const std::string& _old, const std::string& _new){
        //replace all occurences of `old` with `new` in str
    size_t start = s.find(_old);

    while (start != std::string::npos)
    {
        s.replace(start, _old.size(), _new);
        start = s.find(_old, start);
    }
}


inline void util::strip(std::string &s, char toRemove)
{
    s.erase(
        std::remove(s.begin(), s.end(), toRemove),
        s.end());
}

inline std::string util::strip_copy(const std::string &s, char toRemove)
{
    std::string str_out(s);
    util::strip(str_out, toRemove);

    return str_out;
}

inline bool util::icompare(const std::string &s1, const std::string &s2) noexcept
{
    for (size_t i = 0; i < s1.size(); ++i)
    {
        if (std::tolower(s1[i]) != tolower(s2[i]))
            return false;
    }
    return true;
}

inline bool util::starts_with(const std::string& s, std::string_view start_str) {
    return s.find(start_str.data()) == 0;
}

inline std::vector< std::string > util::tokenizeIt(const std::string& str, char sep){
    std::istringstream stream(str);
    std::vector< std::string > tokens;
    std::string token;

    // while ( !stream.eof() )
    // {
    //     std::string x;               // empty string
    //     getline( stream, x, sep );  // try to read the next field into it
    //     tokens.push_back(x);
    // }

    while (std::getline(stream, token, sep))
    {
        tokens.push_back(token);
    }

    return tokens;
}

    //@todo - Debug it
inline auto util::split(const std::string &s, char delim) -> std::vector<std::string>{

	std::vector<std::string> retVec;

	auto start = s.begin(), end = std::find(s.begin(),s.end(), delim);
	while( end != s.end() ){

		//this while loops while there is an unclosed quote present
		while( std::count(start, end, '"')%2 != 0 ){	//ie. odd number of quotes
			if(end == s.end()){
				throw std::logic_error("Parsing Error: Odd number of quotes in passed string, end of input");
			}
				//++end so that it includes the last found returned by std::find
			end = ++std::find(++end, s.end(), '"');
		}
		retVec.push_back( s.substr(start - s.begin(), end -  start) );

		//incremented just to ignore the delim
		start = end;
		if(end != s.end()){
			start = ++end;
		}
		end = std::find( start , s.end(), delim);
	}
	if(start != s.end()){
		retVec.push_back( s.substr(start - s.begin()) );
	}

	return retVec;
}
