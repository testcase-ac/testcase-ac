#include <iostream>
#include <algorithm>
using namespace std;
int main() {
	int n;
	string s;
	cin >> n;
	for(int i=0;i<n;i++) {
		cin >> s;
		cout << s[0]+s[2]-'0'-'0' << endl;
	}
}
