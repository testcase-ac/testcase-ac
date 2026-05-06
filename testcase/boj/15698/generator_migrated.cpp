#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	if(rand()%2) cout<<uniform_int_distribution<int>(1,8)(rd)<<' '<<uniform_int_distribution<int>(1,10000)(rd);
	else cout<<uniform_int_distribution<int>(1,8)(rd)<<' '<<uniform_int_distribution<long long>(1,1000000000000000LL)(rd);
}
