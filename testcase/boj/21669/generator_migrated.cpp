#include <bits/stdc++.h>
using namespace std;
int main() {
    random_device rd;
	mt19937_64 g(rd());
	cout<<g()%9999999999995LL+6;
}
