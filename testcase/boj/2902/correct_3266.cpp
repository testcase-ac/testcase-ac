#include <iostream>

using namespace std;

int main() {
	string str;
	cin >> str;
	cout << str[0];
	for(int i=0; i<str.size(); i++) {
		if(str[i] == '-')
			cout << str[i+1];
	}
}
