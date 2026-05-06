#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	for(int i=0;i<5;i++) cout<<g()%101<<'\n';
}
