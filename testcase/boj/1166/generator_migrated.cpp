#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	for(int i=0;i<4;i++) cout<<g()%1000000000+1<<' ';
}
