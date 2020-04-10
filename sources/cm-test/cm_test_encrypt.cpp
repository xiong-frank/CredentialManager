﻿#include <fstream>

#include "../third/xf-test/xf_simple_test.h"
#include "../third/encrypt/sha256.h"
#include "../third/encrypt/rc4.h"

#include "../cm-core/cm_core.h"

inline std::string sha_256_signature(const std::string& str)
{
    unsigned char x[32]{ 0 };
    xf::encrypt::sha_256(x, str.c_str(), str.size());

    char text[64]{ 0 };
    xf::encrypt::signature_text(text, x);

    return std::string(text, 64);
}

inline bool read_file(const char* file, std::string& text)
{
    std::ifstream fin(file);
    if (fin.is_open()) {

        fin.seekg(0, std::ios::end);
        std::size_t len = (std::size_t)fin.tellg();
        fin.seekg(0, std::ios::beg);

        char* data = new char[len + 1];
        for (unsigned int i = 0; i < len + 1; data[i++] = 0);
        fin.read(data, len);

        text.assign(data, len);
        delete[] data;

        return true;
    }

    return false;
}

_xfTest(test_sha_256)
{
    // 以下用于比较的 sha256 签名由 https://xorbin.com/tools/sha256-hash-calculator 计算得出

    auto s1 = sha_256_signature("");
    _xfExpect(s1 == "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    
    auto s2 = sha_256_signature(" ");
    _xfExpect(s2 == "36a9e7f1c95b82ffb99743e0c5c4ce95d83c9a430aac59f84ef3cbfab6145068");

    auto s3 = sha_256_signature("x");
    _xfExpect(s3 == "2d711642b726b04401627ca9fbac32f5c8530fb1903cc4db02258717921a4881");

    auto s4 = sha_256_signature("X");
    _xfExpect(s4 == "4b68ab3847feda7d6c62c1fbcbeebfa35eab7351ed5e78f4ddadea5df64b8015");

    auto s5 = sha_256_signature("Frank");
    _xfExpect(s5 == "db605e8f71913d1f3966ad908d78b8a8084f5047122037b2b91a7192b598a9ad");

    auto s6 = sha_256_signature("Xiong");
    _xfExpect(s6 == "522eda9ae0455b4c3037c00b5a01503c4cf5203d2526ae41f90317ba55aeba61");

    auto s7 = sha_256_signature("FrankXiong");
    _xfExpect(s7 == "1bf256efaa765f921a9531d3fe0178be78399e872b2aca178b4bf28d278676f1");

    auto s8 = sha_256_signature("CredentialManager");
    _xfExpect(s8 == "56a77307d5e791304996db1e7d79a5136d64e07084320030d4ca4fbd90c359f3");

    std::string data;
    _xfAssert(read_file("../../resources/credential-demo.xml", data));
    auto s9 = sha_256_signature(data);
    _xfExpect(s9 == "af330205bb4e640dde9c3fde202c3f589a6f473dad7052e7ae844809f1152c82");
}

_xfTest(test_rc4_string)
{
    char str[0x400]{ 0 };

    std::string data("CredentialManager");
    auto s0 = sha_256_signature(data);

    _xfExpect(data.size() == xf::encrypt::rc4(str, data.c_str(), data.size(), nullptr, 0));
    std::string data1(str, data.size());
    auto s1 = sha_256_signature(data1);

    _xfExpect(s0 != s1);

    xf::encrypt::rc4(str, data1.c_str(), data1.size(), nullptr, 0);
    std::string data2(str, data.size());
    auto s2 = sha_256_signature(data2);

    _xfExpect(data == data2 && s0 == s2);

    _xfExpect(data.size() == xf::encrypt::rc4(str, data.c_str(), data.size(), "FrankXiong", 10));
    std::string data3(str, data.size());
    auto s3 = sha_256_signature(data3);

    _xfExpect(s0 != s3);

    xf::encrypt::rc4(str, data3.c_str(), data3.size(), "FrankXiong", 10);
    std::string data4(str, data.size());
    auto s4 = sha_256_signature(data4);

    _xfExpect(data == data4 && s0 == s4);
}

_xfTest(test_rc4_file)
{
    std::string data;
    _xfAssert(read_file("../../resources/credential-demo.xml", data));
    auto s0 = sha_256_signature(data);

    std::string key("CredentialManager");

    char* str = new char[data.size()];
    _xfExpect(data.size() == xf::encrypt::rc4(str, data.c_str(), data.size(), key.c_str(), key.size()));
    std::string data1(str, data.size());
    auto s1 = sha_256_signature(data1);

    _xfExpect(s0 != s1);

    xf::encrypt::rc4(str, data1.c_str(), data1.size(), key.c_str(), key.size());
    std::string data2(str, data.size());
    auto s2 = sha_256_signature(data2);

    _xfExpect(data == data2 && s0 == s2);
}
