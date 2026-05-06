#include <iostream>
#include <random>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> d(1,1000000);
	uniform_int_distribution<int> x(1,50);
	cout<<d(gen)<<'\n';
	for(int i=0;i<5;i++) cout<<x(gen)<<' ';
	cout<<x(gen);
}
