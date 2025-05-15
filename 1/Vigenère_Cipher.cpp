#include<bits/stdc++.h>
using namespace std;

string encrypt(string M,string K){
	if(K.empty()){
		cout << "密钥为空";
		return "ERROR!";
	}
	string C;
	int x,y,k;
	for(int i = 0;i<M.length();++i){
		if(isalpha(M[i])){
			char base = isupper(M[i])?'A':'a';
			x = M[i]-base;
			k = K[i%(K.length())]-base;
			y = (x+k)%26;
			C += base +y;
		}else{
			C += M[i];
		}
	}
	if(!C.empty()){
		return C;	
	}
	else{
		cout << "明文串为空！";
	}
}

string decrypt(string M,string K){
	if(K.empty()){
		cout << "密钥为空";
		return "ERROR!";
	}
	string C;
	int x,y,k;
	for(int i = 0;i<M.length();++i){
		if(isalpha(M[i])){
			char base = isupper(M[i])?'A':'a';
			x = M[i]-base;
			k = K[i%(K.length())]-base;
			y = (x-k+26)%26;
			C += base +y;
		}else{
			C += M[i];
		}
	}
	if(!C.empty()){
		return C;	
	}
	else{
		cout << "明文串为空！";
	}
}

int main(){
	string C,M,key;
	cout << "请输入明文："<< endl;
	getline(cin,M);
	cout << "请输入密钥："<< endl;
	getline(cin,key);
	C = encrypt(M,key);
	cout << "加密后，密文如下："<< endl << C <<endl;
	cout << "解密后，明文如下："<< endl << decrypt(C,key);
	return 0;
}
