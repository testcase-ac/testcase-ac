#include <iostream>
#include <random>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	uniform_int_distribution<int> n(2,1000);
	uniform_int_distribution<int> f(-30000,30000);
	int k=n(g);
	cout<<k<<'\n';
	while(k--) {
	    cout<<f(g)<<' '<<f(g)<<'\n';
	}
}
