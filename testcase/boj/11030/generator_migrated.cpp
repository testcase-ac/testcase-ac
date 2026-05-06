#include <iostream>
#include <random>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	uniform_int_distribution<int> n(1,20000);
	cout<<n(g)<<' '<<n(g);
}
