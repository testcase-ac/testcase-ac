#include <iostream>
using namespace std;
int main() {
	int T;
	cin >> T;
	while(T--) {
		int c;
		cin >> c;
		for(int i: {25,10,5,1}){
			cout << c/i << ' ';
			c %= i;
		}
		cout << '\n';
	}
}
