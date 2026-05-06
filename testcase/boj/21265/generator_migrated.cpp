#include <bits/stdc++.h>
using namespace std;
int main() {
    random_device rd;
	mt19937_64 g(rd());
	int n=g()%200+1,m=g()%200+1,k=g()%100+1;
	cout<<n<<' '<<m<<' '<<k<<' '<<g()%n+1<<' '<<g()%m+1<<' '<<g()%k+1;
}
