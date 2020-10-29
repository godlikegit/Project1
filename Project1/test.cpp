// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "inc.h"
#include <optional>
#include <bitset>
#include "helper.hpp"

namespace t1
{

    struct MMap
    {
        multimap<int, int> mm;
        map<int, int> m;

        void add(int k, const vector<int>& v)
        {
            for (const auto& _v : v)
            {
                mm.insert({ k, _v });
                m.emplace(_v, k);
            }
        }

        void del(int k)
        {
            auto itr = mm.find(k);
            if (itr == mm.end()) return;

            for (auto beg = mm.lower_bound(k),
                end = mm.upper_bound(k);
                beg != end; ++beg)
            {
                m.erase(beg->second);
            }

            mm.erase(k);
        }

        std::optional<int> getKey(int v)
        {
            auto itr = m.find(v);
            if (itr == m.end())
            {
                return std::nullopt;
            }

            return itr->second;
        }

        vector<int> getVal(int k)
        {
            vector<int> ret;
            for (auto itr = mm.lower_bound(k); itr != mm.upper_bound(k); ++itr)
            {
                ret.push_back(itr->second);
            }

            return ret;
        }
    };

    void test1()
    {
        MMap o;
        o.add(1, { 12,34,56 });
        o.add(2, { 110,34,112 });
        o.del(1);

        auto k1 = o.getKey(2);
        auto k2 = o.getKey(12);
        auto k3 = o.getKey(110);

        if (k1) cout << *k1;
        if (k2) cout << *k2;
        if (k3) cout << *k3;

        auto v2 = o.getVal(2);
        auto v1 = o.getVal(1);
    }

}

namespace t2
{
    void test2()
    {
        map<int, string> pn;
        pn.insert({ 1,"n1" });
        pn.insert({ 2,"n2" });
        pn.insert({ 3,"n1" });
        pn.insert({ 4,"n4" });
        pn.insert({ 5,"n1" });

        for (auto it = pn.begin(); it != pn.end();)
        {
            if (it->second == "n1")
            {
                it = pn.erase(it);
                continue;
            }
            ++it;
        }
    }
}

class ByteHapper;

namespace t3
{
    string stringtable = "abcdefghijkmnpqrstuvwxyz23456789";
    string password = "dak3le2";

    //从byte转为字符表索引所需要的位数
    int convertByteCount = 5;


    /**
     * 生成兑换码
     * 这里每一次生成兑换码的最大数量为int的最大值即2147483647
     * @param time
     * @param id
     * @param count
     * @return
     */
    void create(byte groupid, int codecount, int codelength, string password)
    {
        //8位的数据总长度
        int fullcodelength = codelength * convertByteCount / 8;
        //随机码对时间和id同时做异或处理
        //类型1，id4，随机码n,校验码1
        int randcount = fullcodelength - 6;//随机码有多少个

        //如果随机码小于0 不生成
        if (randcount <= 0) {
            return;
        }
        for (int i = 0; i < codecount; i++) {
            //这里使用i作为code的id
            //生成n位随机码
            vector<byte> randbytes(randcount);
            for (int j = 0; j < randcount; j++) {
                randbytes[j] = (byte)(Random::get(0, 255));
            }

            //存储所有数据
            ByteHapper byteHapper = ByteHapper(fullcodelength);
            byteHapper.AppendNumber(groupid).AppendNumber(i).AppendBytes(randbytes);

            //计算校验码 这里使用所有数据相加的总和与byte.max 取余
            byte verify = (byte)(byteHapper.GetSum() % 255);
            byteHapper.AppendNumber(verify);

            //使用随机码与时间和ID进行异或
            for (int j = 0; j < 5; j++) {
                byteHapper.bytes[j] =
                    (byte)(byteHapper.bytes[j] ^ (byteHapper.bytes[5 + j % randcount]));
            }

            //使用密码与所有数据进行异或来加密数据
          //  byte[] passwordbytes = password.getBytes();
          //  for (int j = 0; j < byteHapper.bytes.length; j++) {
          //      byteHapper.bytes[j] = (byte)(byteHapper.bytes[j] ^ passwordbytes[j % passwordbytes.length]);
          //  }

            //这里存储最终的数据
            vector<byte> bytes(codelength);

            //按6位一组复制给最终数组
            for (size_t j = 0; j < byteHapper.bytes.size(); j++) {
                for (size_t k = 0; k < 8; k++) {
                    int sourceindex = j * 8 + k;
                    int targetindex_x = sourceindex / convertByteCount;
                    int targetindex_y = sourceindex % convertByteCount;
                    byte placeval = (byte)pow(2, k);
                    byte val = (byte)((byteHapper.bytes[j] & placeval) == placeval ? 1 : 0);
                    //复制每一个bit
                    bytes[targetindex_x] = (byte)(bytes[targetindex_x] | (val << targetindex_y));
                }
            }

            string result;
            //编辑最终数组生成字符串
            for (size_t j = 0; j < bytes.size(); j++) {
                result.append(1, stringtable.at((size_t)(bytes[j])));
            }
            cout << "out string : " + result << endl;
        }

        return;
    }


    /**
     * 验证兑换码
     * @param code
     */
    void VerifyCode(string code) {

        vector<byte> bytes(code.size());

        //首先遍历字符串从字符表中获取相应的二进制数据
        for (size_t i = 0; i < code.size(); i++) {
            byte index = (byte)(stringtable.find(code[i]));
            bytes[i] = index;
        }

        //还原数组
        int fullcodelength = code.size() * convertByteCount / 8;
        int randcount = fullcodelength - 6;//随机码有多少个

        vector<byte> fullbytes(fullcodelength);
        for (size_t j = 0; j < fullbytes.size(); j++) {
            for (size_t k = 0; k < 8; k++) {
                size_t sourceindex = j * 8 + k;
                size_t targetindex_x = sourceindex / convertByteCount;
                size_t targetindex_y = sourceindex % convertByteCount;

                byte placeval = (byte)pow(2, targetindex_y);
                byte val = (byte)((bytes[targetindex_x] & placeval) == placeval ? 1 : 0);

                fullbytes[j] = (byte)(fullbytes[j] | (val << k));
            }
        }

        //解密，使用密码与所有数据进行异或来加密数据
       // byte[] passwordbytes = password.getBytes();
       // for (int j = 0; j < fullbytes.length; j++) {
       //     fullbytes[j] = (byte)(fullbytes[j] ^ passwordbytes[j % passwordbytes.length]);
       // }

        //使用随机码与时间和ID进行异或
        for (int j = 0; j < 5; j++) {
            fullbytes[j] = (byte)(fullbytes[j] ^ (fullbytes[5 + j % randcount]));
        }

        //获取校验码 计算除校验码位以外所有位的总和
        int sum = 0;
        for (size_t i = 0; i < fullbytes.size() - 1; i++) {
            sum += (int)(fullbytes[i]);
        }
        byte verify = (byte)(sum % SCHAR_MAX);

        //校验
        if (verify == fullbytes[fullbytes.size() - 1]) {
            cout << code + " : verify success!" << endl;
        }
        else {
            cout << code + " : verify failed!" << endl;
        }
    }


    void test()
    {
        cout << "=======================";
        create((byte)3, 100, 12, password);

        VerifyCode("c8dksqjamaba");
        VerifyCode("4a36g5npamna");
        VerifyCode("mscwafibk2ca");
        VerifyCode("skwcxifktuwa");
        VerifyCode("taeabiacsiea");
    }
}

//unordered_map<string, FunMap::func_type> FunMap::m;
int main(int argn, char** args)
{
    //t3::test();

    if (argn > 1)
    {
        FunMap::Inst().run(args[1]);
    }

    system("pause");
}