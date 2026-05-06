#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
    uniform_int_distribution<int> n(-1000000000,1000000000),b(2,10),r(0,1);
    int N=n(g),B=b(g);
    if(r(g)%2) B=-B;
    cout<<N<<' '<<B;
}
