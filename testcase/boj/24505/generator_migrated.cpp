#include <iostream>
#include <random>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
    uniform_int_distribution<int> T(1,2);
	uniform_int_distribution<int> r(1,100000);
    uniform_int_distribution<int> R(1,100);
    int t=T(g);
    int n;
    if(t==1) n=r(g);
    else n=R(g);
	cout<<n<<'\n';
	vector<int> v(n);
	iota(v.begin(),v.end(),1);
	shuffle(v.begin(),v.end(),g);
	for(int i:v) cout<<i<<' ';
}
