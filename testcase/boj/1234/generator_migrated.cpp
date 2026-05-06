#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	uniform_int_distribution<int> n(1,10),c(0,100);
	cout<<n(g)<<' '<<c(g)<<' '<<c(g)<<' '<<c(g);
}
