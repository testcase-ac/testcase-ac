#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
    uniform_int_distribution<int> n(1,1000000);
    uniform_int_distribution<int> k(1,10);
    cout<<n(g)<<' '<<k(g);
}
