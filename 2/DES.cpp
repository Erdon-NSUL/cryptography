#include<bits/stdc++.h>
using namespace std;

//声明
string key64 = "0001001100110100010101110111001100110111011110011011111111100010";
string M64 = "1011101111000101000101011111101100101101111000100110011011011100";

//置换选择1
int pc1[56] = {56,48,40,32,24,16,8,
0,57,49,41,33,25,17,
9,1,58,50,42,34,26,
18,10,2,59,51,43,35,
62,54,46,38,30,22,14,
6,61,53,45,37,29,21,
13,5,60,52,44,36,28,
20,12,4,27,19,11,3};

//置换选择2
int pc2[48] = {13,16,10,23,0,4,2,27,
14,5,20,9,22,18,11,3,
25,7,15,6,26,19,12,1,
40,51,30,36,46,54,29,39,
50,44,32,46,43,48,38,55,
33,52,45,41,49,35,28,31 };

//初始置换表IP
int iptable[64] = { 57,49,41,33,25,17,9,1,
59,51,43,35,27,19,11,3,
61,53,45,37,29,21,13,5,
63,55,47,39,31,23,15,7,
56,48,40,32,24,16,8,0,
58,50,42,34,26,18,10,2,
60,52,44,36,28,20,12,4,
62,54,46,38,30,22,14,6 };

//扩展变换表E
int etable[48] = { 31, 0, 1, 2, 3, 4,
3, 4, 5, 6, 7, 8,
7, 8,9,10,11,12,
11,12,13,14,15,16,
15,16,17,18,19,20,
19,20,21,22,23,24,
23,24,25,26,27,28,
27,28,29,30,31, 0 };

//置换函数P
int ptable[32] = { 15,6,19,20,28,11,27,16,
0,14,22,25,4,17,30,9,
1,7,23,13,31,26,2,8,
18,12,29,5,21,10,3,24 };

/*========================S盒=================================*/
int sbox[8][4][16] =
{
//S1
{
	{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
	{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
	{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
	{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
},
//S2
{
	{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
	{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
	{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
	{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
},
//S3
{
	{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
	{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
	{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
	{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
},
//S4
{
	{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
	{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
	{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
	{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
},
//S5
{
	{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
	{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
	{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
	{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
},
//S6
{
	{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
	{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
	{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
	{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
},
//S7
{
	{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
	{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
	{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
	{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
},
//S8
{
	{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
	{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
	{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
	{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
}
};

//逆初始置换表IP^-1
int iptable_r[64] = { 39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,
37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,
35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,
33,1,41,9,49,17,57,25,
32,0,40,8,48,16,56,24 };


bool check(string s, int bit){
	if(s.length() != bit){
		return false;
	}
	return true;
}

string xor_operation(string x,string y,int bit){
	string r = "";
	for(int i = 0;i<bit;++i){
		if(x[i] == y[i]){
			r += '0';
		}else r += '1';
	}
	return r;
}

//以下三个函数是对密钥的处理
string replace_selection(string key64, int* Ppc1){
	string key56 = "";
	for(int i = 0;i<56;++i){
		key56 += key64[*(Ppc1+i)];
	}
	return key56;
}

void rotate_left_1(string &key56){
	string l = "";
	for(int i = 1;i<28;++i){
		l += key56[i];
	}
	l+=key56[0];
	for(int i = 29;i<56;++i){
			l += key56[i];
		}
	l+=key56[28];
	
	key56 = l;
}

void rotate_left_2(string &key56){
	string l = "";
	for(int i = 2;i<28;++i){
		l += key56[i];
	}
	l+=key56[0];
	l+=key56[1];
	for(int i = 30;i<56;++i){
			l += key56[i];
		}
	l+=key56[28];
	l+=key56[29];
	
	key56 = l;
}

string compress_replacement(string key56,int *Ppc2){
	string key48 = "";
		for(int i = 0;i<48;++i){
			key48 += key56[*(Ppc2+i)];
		}
		return key48;
}

//以下函数是对明文的处理
vector<string> ori_M64_RS(string M64, int *Piptable){
	string l = "",r = "";
	vector<string>group;
	
	for(int i = 0;i<32;++i){
		l += M64[*(Piptable+i)];
	}
	for(int i = 32;i<64;++i){
		r += M64[*(Piptable+i)];
	}
		
	group.push_back(l);
	group.push_back(r);
	
	return group;
}

string expand_replacement(string r32, int *Petable){
	string r48 = "";
	for(int i = 0;i<48;++i){
		r48 += r32[*(Petable+i)];
	}
	return r48;
}

void p_replacement(string &r32,int*Pptable){
	string rr32 = "";
	for(int i = 0;i<32;++i){
		rr32 += r32[*(Pptable+i)];
	}
	r32 = rr32;
}

string sbox_operation(string r48,int (*Psbox)[4][16]){
	string r32 = "";
	int row = 0,col = 0;
	for(int i = 0;i<8;++i){
		row = 2*(int(r48[i*6])-48)+(int(r48[i*6+5]-48));
		col = 8*(int(r48[i*6+1])-48)+4*(int(r48[i*6+2])-48)+2*(int(r48[i*6+3])-48)+(int(r48[i*6+4]))-48;
		
		string s4 = bitset<4>(Psbox[i][row][col]).to_string();
		r32+=s4;
	}
	return r32;
}

string reverse_replacement(vector<string>group,int *iptable_r ){
	string m64 = group[0]+group[1],c64="";
	for(int i =0;i<64;++i){
		c64 += m64[*(iptable_r+i)];
	}
	return c64;
}

void round_operation(int round,string key64,vector<string> &group,deque<string> &subkeys){
	string l = group[0],r = group[1];
	string key56 = replace_selection(key64,pc1);

	for(int i = 0;i<round;++i){
		//得到此轮subkey
		if(i == 0||i == 1||i == 8||i==15){
			rotate_left_1(key56);
		}else rotate_left_2(key56);
		
		
		string subkey48 = compress_replacement(key56,pc2);
		subkeys.push_front(subkey48);

		string _r = expand_replacement(r,etable);
		_r = xor_operation(_r,subkey48,48);
		_r = sbox_operation(_r,sbox);
		p_replacement(_r,ptable);
		_r = xor_operation(l,_r,32);
		l = r;
		r = _r;
	}

	group[0] = r;
	group[1] = l;
}

void de_round_operation(int round,string key64,vector<string> &group,deque<string> subkeys){
	string l = group[0],r = group[1];

	for(int i = 0;i<round;++i){
		//得到此轮subkey
		string subkey48 = subkeys[i];

		string _r = expand_replacement(r,etable);
		_r = xor_operation(_r,subkey48,48);
		_r = sbox_operation(_r,sbox);
		p_replacement(_r,ptable);
		_r = xor_operation(l,_r,32);
		l = r;
		r = _r;
	}

	group[0] = r;
	group[1] = l;
}

string DES_encryption(string M64,int *iptable,int *iptable_r,deque<string> &subkeys){
	vector<string>ciallo = ori_M64_RS(M64,iptable);
	round_operation(16,key64,ciallo,subkeys);
	return reverse_replacement(ciallo,iptable_r);
}

string DES_decryption(string M64,int *iptable,int *iptable_r,deque<string> subkeys){
	vector<string>ciallo = ori_M64_RS(M64,iptable);
	de_round_operation(16,key64,ciallo,subkeys);
	return reverse_replacement(ciallo,iptable_r);
}

int main(){
	cout << "start!"<<endl;
	//输入明文M与密钥key
//	cout <<"输入明文M与密钥key:"<<endl;
//	cin >> M64 >> key64;

	
	/*验证输入合法性
	if(!check(M64,64) || !check(key64,64)){
		cout <<M64.length() <<","<<key64.length()<<endl;
		cout<<"Error:输入不合法!"<<endl;
	}*/
	
	//加密过程
	deque<string> subkeys;
	string C64 = DES_encryption(M64,iptable,iptable_r,subkeys);
	cout <<"密文为："<< C64 <<","<<C64.length()<<endl;
	

	//解密过程
	string dC64 = DES_decryption(C64,iptable,iptable_r,subkeys);
	cout <<"解密后明文为："<< dC64 <<","<< dC64.length()<<endl;



	return 0;
}
