#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

// 扩展欧几里得算法计算模逆元
long long mod_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

// 快速幂模运算
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// ElGamal公钥生成
long long elgamal_public_key(long long g, long long x, long long p) {
    return mod_exp(g, x, p);
}

// ElGamal加密
void elgamal_encrypt(long long m, long long p, long long g, long long y, 
                    long long& c1, long long& c2, long long r) {
    c1 = mod_exp(g, r, p);
    c2 = (m * mod_exp(y, r, p)) % p;
}

// ElGamal解密
long long elgamal_decrypt(long long c1, long long c2, long long x, long long p) {
    long long s = mod_exp(c1, x, p);
    long long s_inv = mod_inverse(s, p);
    return (c2 * s_inv) % p;
}

int main() {
    
    cout << "============= ElGamal 密码体制 ============\n";
    
    // 2. 选择素数p和生成元g
    long long p = 509;
    long long g = 449; 
    cout << "素数 p = " << p << ", 生成元 g = " << g << endl;
    
    // 2.1 设置私钥并计算公钥
    long long x = 12; // 私钥
    long long y = elgamal_public_key(g, x, p);
    cout << "公钥 (p, g, y): (" << p << ", " << g << ", " << y << ")" << endl;
    cout << "    私钥 x: " << x << endl;
    
    // 2.2 加密明文
    long long m1 = 123, m2 = 407;
    long long r = 18; // 随机数
    
    long long c1_1, c1_2, c2_1, c2_2;
    elgamal_encrypt(m1, p, g, y, c1_1, c1_2, r);
    elgamal_encrypt(m2, p, g, y, c2_1, c2_2, r);
    
    cout << "    明文 " << m1 << " 的密文: (" << c1_1 << ", " << c1_2 << ")" << endl;
    cout << "    明文 " << m2 << " 的密文: (" << c2_1 << ", " << c2_2 << ")" << endl;
    cout <<endl;
    // 2.3 解密密文
    long long decrypted1 = elgamal_decrypt(c1_1, c1_2, x, p);
    long long decrypted2 = elgamal_decrypt(c2_1, c2_2, x, p);
    long long decrypted3 = elgamal_decrypt(231, 492, x, p);
    
    cout << "    密文 (" << c1_1 << ", " << c1_2 << ") 解密结果: " << decrypted1 << endl;
    cout << "    密文 (" << c2_1 << ", " << c2_2 << ") 解密结果: " << decrypted2 << endl;
    cout << "    密文 (231,492) 解密结果: " << decrypted3 << endl;
    
    
    
    return 0;
}
