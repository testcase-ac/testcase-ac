#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<bool> handin(31);
	for(int i=1; i<=30; i++) {
		int inp;
		cin >> inp;
		handin[inp] = true;
	}
	for(int i=1; i<=30; i++) {
		if(!handin[i])
			cout << i << '\n';
	}
}
