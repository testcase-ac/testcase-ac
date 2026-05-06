#include <bits/stdc++.h>
using namespace std;
int main() {
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> xd(-1000,1000);
	uniform_int_distribution<int> yd(1,1000);
	int T=rand()%10;
	cout<<T<<'\n';
	for(int i=0;i<T;i++) {
		int x1=xd(rng),y1=yd(rng);
		int x2=xd(rng),y2=yd(rng);
		cout<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<'\n';
	}
}
