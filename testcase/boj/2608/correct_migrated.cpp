#include <bits/stdc++.h>
using namespace std;

map<char,int>r={{'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}};

int romToNum(string s){
	int n=s.length(),res=0;
	for(int i=0;i<n;i++)res+=r[s[i]]<(i+1<n?r[s[i+1]]:0)?-r[s[i]]:r[s[i]];
	return res;
}

string numToRom(int n){
	string res="";
	while(n){
		if(n>=1000)res+='M',n-=1000;
		else if(n>=900)res+="CM",n-=900;
		else if(n>=500)res+='D',n-=500;
		else if(n>=400)res+="CD",n-=400;
		else if(n>=100)res+='C',n-=100;
		else if(n>=90)res+="XC",n-=90;
		else if(n>=50)res+='L',n-=50;
		else if(n>=40)res+="XL",n-=40;
		else if(n>=10)res+='X',n-=10;
		else if(n>=9)res+="IX",n-=9;
		else if(n>=5)res+='V',n-=5;
		else if(n>=4)res+="IV",n-=4;
		else res+='I',n--;
    }
	return res;
}
int main(){
	string a,b;
	cin>>a>>b;
	int sum=romToNum(a)+romToNum(b);
	cout<<sum<<"\n"<<numToRom(sum)<<"\n";
}
