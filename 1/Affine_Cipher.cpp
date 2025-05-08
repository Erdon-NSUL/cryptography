#include<bits/stdc++.h>
using namespace std;
/*e(x)≡9x+6 (mod 26)*/

int A = 0,B = 0,mod = 1,inv = 0;

int extendedEuclid(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int gcd = extendedEuclid(b, a % b, x, y);
    int temp = y;
    y = x - (a / b) * y; 
    x = temp;            
    return gcd;
}

bool modInverse(int a, int n, int &inv) {
    if (n <= 1){
		cout << "mod > 1"<< endl;
		return false; 
	}

 
    a = a % n;
    if (a < 0) a += n;
    
    int x, y;
    int gcd = extendedEuclid(a, n, x, y); 
    
    if (gcd != 1) {
		cout << "inv dose not exist"<< endl;
		return false; 
	}

    inv = (x % n + n) % n;
    return true;
}


string encrypt(string M){
	string C;
	int x,y;
	for(char i:M){
		if(isalpha(i)){
			char base = isupper(i)?'A':'a';
			x = i-base;
			y = (A*x+B)%26;
			C += base +y;
		}else{
			C += i;
		}
	}
	if(!C.empty()){
		return C;	
	}
	else{
		cout << "error_encrypt!";
		return "0x000000";
	}
}

string decrypt(string C){
	string M;
	int x,y;
	for(char i : C){
		if(isalpha(i)){
			char base = isupper(i)? 'A':'a';
			x = i -base;
			y = inv*(x-B+26)%26;
			M += base + y;
		}else{
			M+=i;
		}
	}
	if(!M.empty()){
		return M;
	}else{
		cout << "error_decrypt!";
		return "0x000000";
	}
}

int main(){
	string C,M;
	cout << "A,B,mod:"<< endl;
	cin >> A >> B >> mod;
	cin.ignore();
	if(modInverse(A,mod,inv)){
		cout << "M:"<< endl;
		getline(cin,M);
		C = encrypt(M);
		cout << "C:"<< endl << C <<endl;;
		cout << "M:"<< endl << decrypt(C);
	}
	return 0;
}
