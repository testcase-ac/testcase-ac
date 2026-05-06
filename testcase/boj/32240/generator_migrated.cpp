#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
    uniform_int_distribution<long long> n(1,100000000000);
    cout<<n(g);
}
