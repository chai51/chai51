// utf8中文
#include <chai51/utility/string.h>
#include <regex>
#include <boost/locale.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>

namespace chai51
{

std::string convertUTF8(const char * gbk)
{
	return boost::locale::conv::between(gbk, "utf8", "gbk");
}

std::string convertGBK(const char * utf8)
{
	return boost::locale::conv::between(utf8, "gbk", "utf8");
}

void replace(std::string& str, const std::string& oldVal, const std::string& newVal, bool all /*= false*/)
{
	std::string::size_type pos = 0;
	while ((pos = str.find(oldVal, pos)) != std::string::npos)
	{
		str.replace(pos, oldVal.length(), newVal);
		if (!all) return;
		pos += newVal.length();
	}
}

void replaceRE(std::string& str, const std::string& re, const std::string& newVal)
{
	str = std::regex_replace(str, std::regex(re), newVal);
}

void trim(std::string& str, char ch /*= ' '*/)
{
	if (str.empty())
	{
		return;
	}
	str.erase(0, str.find_first_not_of(ch));
	str.erase(str.find_last_not_of(ch) + 1);
}

std::string base64Encode(const std::string& str)
{
	std::string encode;

	typedef boost::archive::iterators::base64_from_binary<boost::archive::iterators::transform_width<std::string::const_iterator, 6, 8> > base64EncodeIterator;
	copy(base64EncodeIterator(str.begin()), base64EncodeIterator(str.end()), std::back_inserter(encode));
	size_t equal_count = (3 - str.length() % 3) % 3;
	for (size_t i = 0; i < equal_count; ++i)
	{
		encode.push_back('=');
	}
	return encode;
}

std::string base64Decode(const std::string& str)
{
	std::string decode;

	typedef boost::archive::iterators::transform_width<boost::archive::iterators::binary_from_base64<std::string::const_iterator>, 8, 6> base64DecodeIterator;
	try
	{
		copy(base64DecodeIterator(str.begin()), base64DecodeIterator(str.end()), std::back_inserter(decode));
	}
	catch (std::exception &e)
	{
		return e.what();
	}
	return "";
}

void split(const std::string & str, const std::string & separator, std::vector<std::string>& vec)
{
	if (str.empty())
	{
		return;
	}

	std::string::size_type nStartPos = 0;
	std::string::size_type nEndPos = 0;
	while ((nEndPos = str.find(separator, nStartPos)) != std::string::npos)
	{
		vec.push_back(str.substr(nStartPos, nEndPos - nStartPos));
		nStartPos = nEndPos + separator.length();
	}
	vec.push_back(str.substr(nStartPos));
}

}
