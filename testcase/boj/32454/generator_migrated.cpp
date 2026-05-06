#include <iostream>
#include <random>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	uniform_int_distribution<int> T(1,20);
	uniform_int_distribution<int> n(1,1000000000);
	int t=T(g);
	cout<<t;
	while(t--) {
	    cout<<'\n'<<n(g);
	}
}
