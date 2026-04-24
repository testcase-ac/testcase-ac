#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;
	string s;
	do {
		if(n % -2 == 0)
			s = '0' + s;
		else if(n % -2 == 1)
			s = '1' + s;
		else
			s = '1' + s, n -= 2;
		n /= -2;
	} while(n);
	cout << s << '\n';

}
