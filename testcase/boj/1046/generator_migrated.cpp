//GPT 코드
#include <bits/stdc++.h>
using namespace std;

int main() {
	random_device rd;
	mt19937 g(rd());
	uniform_int_distribution<int> dn(1,50),dm(1,50),dp(0,99);
	int n=dn(g),m=dm(g);
	cout<<n<<' '<<m<<'\n';
	int x=g()%n,y=g()%m;
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			if(i==x&&j==y) {
				cout<<'*';
				continue;
			}
			int p=dp(g);
			if(p<25) cout<<'#';
			else cout<<'.';
		}
		cout<<'\n';
	}
}
