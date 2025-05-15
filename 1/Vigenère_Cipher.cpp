#include<bits/stdc++.h>
using namespace std;

string encrypt(string M,string K){
	if(K.empty()){
		cout << "��ԿΪ��";
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
		cout << "���Ĵ�Ϊ�գ�";
	}
}

string decrypt(string M,string K){
	if(K.empty()){
		cout << "��ԿΪ��";
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
		cout << "���Ĵ�Ϊ�գ�";
	}
}

int main(){
	string C,M,key;
	cout << "���������ģ�"<< endl;
	getline(cin,M);
	cout << "��������Կ��"<< endl;
	getline(cin,key);
	C = encrypt(M,key);
	cout << "���ܺ��������£�"<< endl << C <<endl;
	cout << "���ܺ��������£�"<< endl << decrypt(C,key);
	return 0;
}
