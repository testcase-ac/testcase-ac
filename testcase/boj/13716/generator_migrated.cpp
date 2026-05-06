#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	cout<<uniform_int_distribution<long long>(1,100000000000000000)(rd)<<' '<<uniform_int_distribution<int>(1,40)(rd);
}
