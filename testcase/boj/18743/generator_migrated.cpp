#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	cout<<uniform_int_distribution<int>(2,1000000)(rd)<<' '<<uniform_int_distribution<int>(0,100)(rd);
}
