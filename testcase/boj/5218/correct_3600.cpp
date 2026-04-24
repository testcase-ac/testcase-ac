#include <iostream>
using namespace std;
int main() {
	int T;
	cin >> T;
	while(T--) {
		string s1, s2;
		cin >> s1 >> s2;
		cout << "Distances: ";
		int n = s1.size();
		for(int i=0; i<n; i++) {
			if(s1[i] <= s2[i])
				cout << s2[i]-s1[i] << ' ';
			else
				cout << s2[i]+26-s1[i] << ' ';
		}
		cout << '\n';
	}
}
