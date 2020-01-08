// boost version 1.73.0
#pragma once

#include <string>
#include <vector>

namespace chai51
{
std::string convertUTF8(const char* gbk);
std::string convertGBK(const char* utf8);

void replace(std::string& str, const std::string& oldVal, const std::string& newVal, bool all = false);

void replaceRE(std::string& str, const std::string& re, const std::string& newVal);

void trim(std::string& str, char ch = ' ');

std::string base64Encode(const std::string& str);
std::string base64Decode(const std::string& str);

void split(const std::string& str, const std::string& separator, std::vector<std::string>& vec);
}
