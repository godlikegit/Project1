#pragma once

 class ByteHapper
 {
 public:
     //原始数组
     vector<byte> bytes;
     //记录当前写入到多少位
     int index;

     ByteHapper(int capacity) {
         bytes.resize(capacity);
         index = 0;
     }

     //向数组中追加内容
     ByteHapper& AppendNumber(long val) {
         return AppendBytes(Number2byte(val));
     }
     ByteHapper& AppendNumber(int val) {
         return AppendBytes(Number2byte(val));
     }
     ByteHapper& AppendNumber(short val) {
         return AppendBytes(Number2byte(val));
     }
     ByteHapper& AppendNumber(byte val) {
         return AppendBytes({ val });
     }

     //追加byte数组
     ByteHapper& AppendBytes(vector<byte> arr) {

         for (size_t i = 0; i < arr.size(); i++) {
             bytes[index + i] = arr[i];
         }

         index += arr.size();
         return *this;
     }


     /**
      * 获取数据的总和
      * @return
      */
     int GetSum() {
         int ret = 0;
         for (size_t i = 0; i < bytes.size(); i++) {
             ret += (int)(bytes[i]);
         }
         return ret;
     }

     /**
      * 将数字转换为byte数组
      */
     vector<byte> Number2byte(long val) {

         vector<byte> arr = {
                 (byte)((val >> 56) & 0xFF),
                 (byte)((val >> 48) & 0xFF),
                 (byte)((val >> 40) & 0xFF),
                 (byte)((val >> 32) & 0xFF),
                 (byte)((val >> 24) & 0xFF),
                 (byte)((val >> 16) & 0xFF),
                 (byte)((val >> 8) & 0xFF),
                 (byte)(val & 0xFF)
         };

         return arr;
     }

     vector<byte> Number2byte(int val) {

         vector<byte> arr = {
                 (byte)((val >> 24) & 0xFF),
                 (byte)((val >> 16) & 0xFF),
                 (byte)((val >> 8) & 0xFF),
                 (byte)(val & 0xFF)
         };

         return arr;
     }

     vector<byte> Number2byte(short val) {

         vector<byte> arr = {
                 (byte)((val >> 8) & 0xFF),
                 (byte)(val & 0xFF)
         };

         return arr;
     }
 };