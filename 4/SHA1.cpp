#include<bits/stdc++.h>
using namespace std;

class SHA1 {
public:
    static string hash(const string& input) {
        // 初始化哈希值（5个32位常量）
        uint32_t h0 = 0x67452301;
        uint32_t h1 = 0xEFCDAB89;
        uint32_t h2 = 0x98BADCFE;
        uint32_t h3 = 0x10325476;
        uint32_t h4 = 0xC3D2E1F0;

        // 消息填充（添加1 + 0x00 + 长度）
        vector<uint8_t> bytes(input.begin(), input.end());
        bytes.push_back(0x80); // 添加1比特（0x80 = 10000000）

        // 填充0至长度 ≡ 448 mod 512
        while ((bytes.size() * 8) % 512 != 448) {
            bytes.push_back(0x00);
        }

        // 追加原始消息长度（64位大端序）表示原始信息长度
        uint64_t bitLength = input.size() * 8;
        for (int i = 7; i >= 0; --i) {
            bytes.push_back((bitLength >> (i * 8)) & 0xFF);
        }

        // 处理512位数据块
        for (size_t i = 0; i < bytes.size(); i += 64) {
            // 将块分解为16个32位字（大端序）
            uint32_t words[80] = {0};
            for (int j = 0; j < 16; ++j) {
                words[j] = (bytes[i+j*4] << 24) |
                           (bytes[i+j*4+1] << 16) |
                           (bytes[i+j*4+2] << 8) |
                           bytes[i+j*4+3];
            }

            // 扩展至80个字
            for (int j = 16; j < 80; ++j) {
                words[j] = leftRotate(words[j-3] ^ words[j-8] ^ words[j-14] ^ words[j-16], 1);
            }

            // 初始化工作变量
            uint32_t a = h0, b = h1, c = h2, d = h3, e = h4;

            // 主循环（80轮）
            for (int j = 0; j < 80; ++j) {
                uint32_t f, k;
                if (j < 20) {
                    f = (b & c) | ((~b) & d);
                    k = 0x5A827999;
                } else if (j < 40) {
                    f = b ^ c ^ d;
                    k = 0x6ED9EBA1;
                } else if (j < 60) {
                    f = (b & c) | (b & d) | (c & d);
                    k = 0x8F1BBCDC;
                } else {
                    f = b ^ c ^ d;
                    k = 0xCA62C1D6;
                }

                uint32_t temp = leftRotate(a, 5) + f + e + k + words[j];
                e = d;
                d = c;
                c = leftRotate(b, 30);
                b = a;
                a = temp;
            }

            // 更新哈希值
            h0 += a;
            h1 += b;
            h2 += c;
            h3 += d;
            h4 += e;
        }

        // 拼接最终哈希值
        return toHexString(h0) + toHexString(h1) + toHexString(h2) + toHexString(h3) + toHexString(h4);
    }

private:
    // 循环左移
    static uint32_t leftRotate(uint32_t x, int n) {
        return (x << n) | (x >> (32 - n));
    }

    // 32位整数转16进制字符串
    static string toHexString(uint32_t value) {
        stringstream ss;
        ss << hex << setfill('0') << setw(8) << value;
        return ss.str();
    }
};

int main() {
    vector<string>ciallo = {
		"iscbupt",
		"seven",
		"Hainan University",
		"This is a secret",
		"Symmetric Cryptosystem and Public Key Cryptosystem",
		"The proposed scheme is not only able to provide mutual authentication without communication with the trusted third party, but also fulfills various security features, such as user anonymity, forward secrecy, etc."
	};
	for(string i:ciallo){
		cout <<"原始输入： "<< i <<endl;
		cout <<"散列值： "<<SHA1::hash(i) <<endl;
		cout <<endl;
	}
	
    return 0;
}
