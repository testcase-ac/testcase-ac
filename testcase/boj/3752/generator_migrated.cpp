#include <bits/stdc++.h>
using namespace std;
int main() {
    random_device rd;
	mt19937_64 g(rd());
	int t=g()%10+1;
	cout<<t<<'\n';
	while(t--){
		int m=5+g()%5;
		vector<int> a;
		for(int i=0;i<m;i++){
			int x=g()%2000000000+1;
			a.push_back(x);
		} set<int> s;
		for(int x:a){
			for(int d=1;d*d<=x;d++) {
				if(x%d==0){
					s.insert(d);
					s.insert(x/d);
				}
			}
		} if(s.size()>1000) {t++;continue;}
		cout<<s.size()<<'\n';
		for(int x:s) cout<<x<<" ";
		cout<<'\n';
	}
}
