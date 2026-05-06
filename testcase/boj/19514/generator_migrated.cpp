#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937 g(rd());
	int t=rand()%10;
	cout<<t<<'\n';
	for(int i=0;i<t;i++) {
		int n=uniform_int_distribution<int>(1,100000)(g);
		int k=uniform_int_distribution<int>(1,min(100,n))(g);
		cout<<n<<' '<<k<<'\n';
		set<int> s;
		while(s.size()<k) s.insert(uniform_int_distribution<int>(1,n)(g));
		vector<int> a(s.begin(),s.end());
		for(int j=0;j<k;j++) cout<<a[j]<<(j+1<k?' ':'\n');
		s.clear();
		while(s.size()<k) s.insert(uniform_int_distribution<int>(1,n)(g));
		vector<int> b(s.begin(),s.end());
		for(int j=0;j<k;j++) cout<<b[j]<<(j+1<k?' ':'\n');
	}
}
