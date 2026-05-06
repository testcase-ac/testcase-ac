#include <bits/stdc++.h>
using namespace std;
const int M=1e9+7;
int t[12][100001];
void add(int k,int i,int v) {
	while(i<100001) {
		t[k][i]+=v;
		t[k][i]%=M;
		i+=i&-i;
	}
}
int sum(int k,int i) {
	int r=0;
	while(i) {
		r+=t[k][i];
		r%=M;
		i-=i&-i;
	} return r;
}
int main() {
	int n,x;
	cin>>n;
	for(int i=0;i<n;i++) { 
		cin>>x;
		add(1,x,1);
		for(int k=2;k<=11;k++) add(k,x,sum(k-1,x-1));
	} cout<<sum(11,100000);
}
