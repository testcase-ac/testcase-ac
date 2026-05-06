#include <iostream>
#include <random>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	uniform_int_distribution<long long> r(1,1000000000000000000);
	long long n=r(g);
	long double x=log10l(2.0)*n;
	long long k=x+1;
	x-=floor(x);
	x=pow(10,x);
	int t=x/pow(10,floor(log10(x)));
	cout<<n<<' '<<k<<' '<<t;
}
