#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;
int main() {
	random_device r;
	mt19937_64 g(r());
	uniform_int_distribution<int> d(4,2147483647);
	int k=0;
	while(1) {
		int n=d(g);
		vector<int> v;
		bool ok=1;
		for(int i=2;i*i<=n;i++) {
			if(n%i==0) {
				if(i>1000000||n/i>1000000) {
					ok=0;
					break;
				} v.push_back(i);
				if(i!=n/i) v.push_back(n/i);
			}
		} if(ok&&v.size()&&(k>10||v.size()>2)) {
			cout<<v.size()<<'\n';
			random_shuffle(v.begin(),v.end());
			for(int i=0;i<v.size()-1;i++) cout<<v[i]<<' ';
			cout<<v[v.size()-1];
			return 0;
		} if(v.size()==2) k++;
	}
}
