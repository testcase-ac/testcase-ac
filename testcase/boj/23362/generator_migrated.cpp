#include <iostream>
#include <random>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	uniform_int_distribution<int> t(1,60);
	uniform_int_distribution<long long> n(1,100000000000000);
	int c=t(g);
	cout<<c;
	while(c--) {
	    cout<<"\n\n"<<n(g);
	}
}
