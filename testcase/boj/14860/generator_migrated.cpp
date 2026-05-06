#include <bits/stdc++.h>
using namespace std;
int main() {
    random_device rd;
	mt19937_64 g(rd());
	cout<<g()%15000000+1<<' '<<g()%15000000+1;
}
