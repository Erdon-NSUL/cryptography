#include<bits/stdc++.h>
using namespace std;

class SHA1 {
public:
    static string hash(const string& input) {
        // ��ʼ����ϣֵ��5��32λ������
        uint32_t h0 = 0x67452301;
        uint32_t h1 = 0xEFCDAB89;
        uint32_t h2 = 0x98BADCFE;
        uint32_t h3 = 0x10325476;
        uint32_t h4 = 0xC3D2E1F0;

        // ��Ϣ��䣨���1 + 0x00 + ���ȣ�
        vector<uint8_t> bytes(input.begin(), input.end());
        bytes.push_back(0x80); // ���1���أ�0x80 = 10000000��

        // ���0������ �� 448 mod 512
        while ((bytes.size() * 8) % 512 != 448) {
            bytes.push_back(0x00);
        }

        // ׷��ԭʼ��Ϣ���ȣ�64λ����򣩱�ʾԭʼ��Ϣ����
        uint64_t bitLength = input.size() * 8;
        for (int i = 7; i >= 0; --i) {
            bytes.push_back((bitLength >> (i * 8)) & 0xFF);
        }

        // ����512λ���ݿ�
        for (size_t i = 0; i < bytes.size(); i += 64) {
            // ����ֽ�Ϊ16��32λ�֣������
            uint32_t words[80] = {0};
            for (int j = 0; j < 16; ++j) {
                words[j] = (bytes[i+j*4] << 24) |
                           (bytes[i+j*4+1] << 16) |
                           (bytes[i+j*4+2] << 8) |
                           bytes[i+j*4+3];
            }

            // ��չ��80����
            for (int j = 16; j < 80; ++j) {
                words[j] = leftRotate(words[j-3] ^ words[j-8] ^ words[j-14] ^ words[j-16], 1);
            }

            // ��ʼ����������
            uint32_t a = h0, b = h1, c = h2, d = h3, e = h4;

            // ��ѭ����80�֣�
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

            // ���¹�ϣֵ
            h0 += a;
            h1 += b;
            h2 += c;
            h3 += d;
            h4 += e;
        }

        // ƴ�����չ�ϣֵ
        return toHexString(h0) + toHexString(h1) + toHexString(h2) + toHexString(h3) + toHexString(h4);
    }

private:
    // ѭ������
    static uint32_t leftRotate(uint32_t x, int n) {
        return (x << n) | (x >> (32 - n));
    }

    // 32λ����ת16�����ַ���
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
		cout <<"ԭʼ���룺 "<< i <<endl;
		cout <<"ɢ��ֵ�� "<<SHA1::hash(i) <<endl;
		cout <<endl;
	}
	
    return 0;
}
