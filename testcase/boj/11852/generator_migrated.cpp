#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
string gen(int len) {
	string s;
	for(int i=0;i<len;i++) s+='a'+rng()%26;
	return s;
}
int main() {
	int len1=rng()%1000+1,len2=rng()%1000+1;
	string a=gen(len1), b=gen(len2);
	cout<<a<<'\n'<<b<<'\n';
}
