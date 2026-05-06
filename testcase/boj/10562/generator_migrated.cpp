#include <iostream>
#include <random>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	uniform_int_distribution<int> T(1,10);
	uniform_int_distribution<int> M(1,4);
	uniform_int_distribution<int> N(1,1000000000);
	int t=T(g);
	cout<<t;
	while(t--) {
	    int m=M(g),n=N(g);
	    cout<<'\n'<<m<<' '<<n;
	}
}
