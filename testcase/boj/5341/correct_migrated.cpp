#include <iostream>
using namespace std;
int main() {
	int a;
	while(1) {
		cin>>a;
		if(a==0) break;
		cout<<a*(a+1)/2<<'\n';
	}
}
