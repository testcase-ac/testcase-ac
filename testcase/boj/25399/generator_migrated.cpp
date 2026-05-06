#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	cout<<uniform_int_distribution<long long>(-1000000000000,1000000000000)(rd);
}
