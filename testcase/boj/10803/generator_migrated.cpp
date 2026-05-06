#include <iostream>
#include <random>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	uniform_int_distribution<int> n(1,10000),m(1,100);
	cout<<n(g)<<' '<<m(g);
}
