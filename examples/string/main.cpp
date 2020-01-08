#include <chai51/utility/string.h>
#include <iostream>
#include <assert.h>
#include <algorithm>

int main(int argc, char* argv[])
{
    {
        std::string utf8 = "你好，中国";
        std::string gbk = chai51::convertGBK(utf8.c_str());
        assert(utf8 == chai51::convertGBK(gbk.c_str()));
    }

    {
        std::string str = "addr:192.168.0.101, type:udp, session:3554916745, port:9";
        chai51::replace(str, "udp", "tcp");
        assert(str.find("udp") != std::string::npos);
    }
    {
        std::string str = "addr->192.168.0.101, type->udp, session->3554916745, port:9";
        chai51::replace(str, "->", ":", true);
        assert(str.find(":") == std::string::npos);
    }
    {
        std::string str = "addr:192.168.0.101, type:udp, session:3554916745, port:9";
        chai51::replaceRE(str, R"(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})", "127.0.0.1");
        assert(str.find("127.0.0.1") != std::string::npos);
    }
    {
        std::string str = "addr:192.168.0.101, type:udp, session:3554916745, port:9";
        std::string encode = chai51::base64Encode(str);
        assert(chai51::base64Decode(encode) == str);
    }
    {
        std::string str = "addr:192.168.0.101,; type:udp,; session:3554916745,;,; port:9";
        std::vector<std::string> vec;
        chai51::split(str, ",;", vec);
        assert(vec.size() == 5u);
    }

    return 0;
}
