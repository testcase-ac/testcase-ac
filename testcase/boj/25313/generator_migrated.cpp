//GPT 코드에서 랜덤 범위만 50으로 수정 (더 크면 testcase.ac에서 짤리는 경우가 많음)
#include <bits/stdc++.h>
using namespace std;

int main(){
	random_device rd;
	mt19937 g(rd());
	uniform_int_distribution<int> d1(3,50);
	
	int R=d1(g),C=d1(g);
	uniform_int_distribution<int> d2(3,C);
	int N=d2(g);
	
	int mx=(R-2)*C;
	uniform_int_distribution<int> d3(0,min(50,mx));
	int M=d3(g);
	
	uniform_int_distribution<int> d4(1,R-1);
	int S=d4(g);
	
	vector<int>a(C),b(C),t(C);
	iota(a.begin(),a.end(),1);
	iota(b.begin(),b.end(),1);
	iota(t.begin(),t.end(),1);
	
	shuffle(a.begin(),a.end(),g);
	shuffle(b.begin(),b.end(),g);
	shuffle(t.begin(),t.end(),g);
	
	a.resize(N);
	b.resize(N);
	t.resize(N);
	
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	sort(t.begin(),t.end());
	
	cout<<R<<" "<<C<<" "<<N<<" "<<M<<" "<<S<<"\n";
	for(int i=0;i<N;i++) cout<<a[i]<<(i+1<N?' ':'\n');
	for(int i=0;i<N;i++) cout<<b[i]<<(i+1<N?' ':'\n');
	for(int i=0;i<N;i++) cout<<t[i]<<(i+1<N?' ':'\n');
	
	vector<pair<int,int>>v;
	for(int i=2;i<=R-1;i++)
		for(int j=1;j<=C;j++)
			v.push_back({i,j});
	
	shuffle(v.begin(),v.end(),g);
	for(int i=0;i<M;i++)
		cout<<v[i].first<<" "<<v[i].second<<"\n";
}
