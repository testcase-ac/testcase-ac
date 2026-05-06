#include <iostream>
#include <random>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	uniform_int_distribution<int> n(1,1000);
	uniform_int_distribution<int> m(1,80);
	uniform_int_distribution<int> f(0,11);
	string s="RUFLDBrufldb";
	int k=n(g);
	while(k--) {
	    int c=m(g);
	    string a="";
	    while(c--) a+=s[f(g)];
	    cout<<a<<'\n';
	}
}
