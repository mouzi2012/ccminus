#ifndef _UTILS_H
#define _UTILS_H

#include<string>
#include<vector>

class Utils
{
public:
	static void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);
};
#endif