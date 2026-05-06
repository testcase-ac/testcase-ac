#include <iostream>
#include <random>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	uniform_int_distribution<long long> n(0,100000000000000000);
	cout<<n(g);
}
