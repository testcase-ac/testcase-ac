#include <iostream>
#include <random>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> n(100,2000000000);
	uniform_int_distribution<int> f(1,100);
	cout<<n(gen)<<'\n'<<f(gen);
}
