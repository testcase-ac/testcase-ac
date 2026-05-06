#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	long long n=g()%1000000000000000000LL+1;
    uniform_int_distribution<long long> k(1,n);
    cout<<n<<' '<<k(g);
}
