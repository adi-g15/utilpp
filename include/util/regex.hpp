#pragma once

namespace util{
	bool matched_any(const std::string& s, const std::vector<std::regex>& reg_vec){	//whether if s matches any regex
		for( auto&& reg : reg_vec ){
			if( regex_match(s, reg) )	return true;
		}
		return false;
	}
}
