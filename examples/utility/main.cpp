#include <iostream>
#include <assert.h>

#include <chai51/utility/string.h>
#include <chai51/utility/task.h>

int main(int argc, char* argv[])
{
    // // string.h
    // {
    //     std::string str = "你好，中国";
    //     std::string gbk = chai51::convertGBK(str.c_str());
    //     std::string utf8 = chai51::convertUTF8(gbk.c_str());
    //     assert(utf8 == str);
    // }
    // {
    //     std::string str = "addr:192.168.0.101, type:udp, session:3554916745, port:9";
    //     chai51::replace(str, "udp", "tcp");
    //     assert(str.find("tcp") != std::string::npos);
    // }
    // {
    //     std::string str = "addr->192.168.0.101, type->udp, session->3554916745, port:9";
    //     chai51::replace(str, "->", ":", true);
    //     assert(str.find(":") != std::string::npos);
    // }
    // {
    //     std::string str = "addr:192.168.0.101, type:udp, session:3554916745, port:9";
    //     chai51::replaceRE(str, R"(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})", "127.0.0.1");
    //     assert(str.find("127.0.0.1") != std::string::npos);
    // }
    // {
    //     std::string str = "addr:192.168.0.101, type:udp, session:3554916745, port:9";
    //     std::string encode = chai51::base64Encode(str);
    //     std::string decode = chai51::base64Decode(encode);
    //     std::cout << decode.length() << "," << str.length() << std::endl;
    //     std::cout << (decode.c_str() == str) << std::endl;
    //     assert(decode.c_str() == str);
    // }
    // {
    //     std::string str = "addr:192.168.0.101,; type:udp,; session:3554916745,;,; port:9";
    //     std::vector<std::string> vec;
    //     chai51::split(str, ",;", vec);
    //     assert(vec.size() == 5u);
    // }

    // task.h
    {
        // worldID 0、1被保留，0处理定时函数对象，1为主线程暂未实现，最终处理依旧在用户workID中处理
        chai51::CTask::init();
        
        // 创建工作线程，队列式处理函数对象
        chai51::CTask::createWork(2);
        chai51::CTask::createWork(3);
        for (size_t i = 0; i < 100; i++)
        {
            auto func = [i](){
                std::cout << "func number:" << i << std::endl;
            };
            if (i % 3 == 0)
            {
                chai51::CTask::put(2, func);
            }
            else if (i % 3 == 1)
            {
                chai51::CTask::put(3, func);
            }
            else if (i % 3 == 2)
            {
                chai51::CTask::put(2, func, std::chrono::seconds(i));
            }
        }
        
    }
    getchar();
    return 0;
}
