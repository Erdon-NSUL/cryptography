# include<bits/stdc++.h>
using namespace std;

int p=11,q=13,e=7;
int n = p*q,m = (p-1)*(q-1);
int m1 = 85,m2 =91,c0 = 123;


int gcd(int a,int b){
	if(a<b){
		int tmp = b;
		b = a;
		a = b;
	}
	if(b!=0){
		a = gcd(b,a%b);
	}
	return a;
}

int expand_gcd(int a, int b, int *x, int *y) {
    int xp = 1, yp = 0;  
    int xc = 0, yc = 1;  
    int q; 
    int temp;

    while (b != 0) {
		
        q = a / b;  
        temp = a;
        a = b;      
        b = temp % b;

        temp = xp;
        xp = xc;          
        xc = temp - q * xc;

        temp = yp;
        yp = yc;          
        yc = temp - q * yc;
    }

    *x = xp;  
    *y = yp;  
    return a;  
}



int cal_pkey(int m,int e){
	int a = m,b = e;
	int xc = 1 ,xn = 0;
	int yc = 0,yn = 1;
	
	while(b != 0){
		int q = a/b;
		int r = a%b;
		// a = q*b+r
		a = b;
		b = r;
		
		//
		int tmpx = xc - q*xn;
		int tmpy = yc- q*yn;
		
		xc = xn;
		yc = yn;
		
		xn = tmpx;
		yn = tmpy;		
		
	}	
	int  inv = xc+e;
	return inv;
}
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

// 计算最大公约数
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// RSA密钥生成
void rsa_generate_keys(long long p, long long q, 
                      long long& e, long long& d, long long& n) {
    n = p * q;
    long long phi = (p - 1) * (q - 1);
    
    // 选择公钥e
    e = 7;
    while (gcd(e, phi) != 1) {
        e = rand() % (phi - 2) + 2; 
    }
    
    // 计算私钥d
    d = mod_inverse(e, phi);
}

// RSA加密
long long rsa_encrypt(long long m, long long e, long long n) {
    return mod_exp(m, e, n);
}

// RSA解密
long long rsa_decrypt(long long c, long long d, long long n) {
    return mod_exp(c, d, n);
}
int main(){
	int d = cal_pkey(m,e);
	cout << "私钥d为： "<< d<<endl;
	cout << "明文加密： "<<endl; 
	cout << m1%d<<endl;
	cout << m2%d<<endl;
	cout << "密文破解： " << c0%d<<endl;
	return 0;
}
