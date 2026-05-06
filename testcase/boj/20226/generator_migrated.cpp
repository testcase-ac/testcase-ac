#include <iostream>
#include <algorithm>
#include <random>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> cnt(1,300);
	uniform_int_distribution<long long> val(1,999999999999999);
	int n=cnt(gen);
	vector<long long> v(n);
	while(n--) v[n]=val(gen);
	sort(v.begin(),v.end());
	for(long long i:v) cout<<i<<'\n';
	cout<<0<<'\n';
}
