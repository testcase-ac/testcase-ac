#include <iostream>
#include <random>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> f(0,1);
	uniform_int_distribution<int> x(1,15);
	uniform_int_distribution<int> y(1,100000);
	uniform_int_distribution<int> n(2,500000);
	int t;
	if(f(gen)) t=x(gen);
	else t=y(gen);
	cout<<t<<'\n';
	while(t--) cout<<n(gen)*2<<'\n';
}
