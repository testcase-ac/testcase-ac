#include <iostream>
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	rep(i, n) {
		if(i % 2 == 1) cout << ' ';
		cout << '*';
		rep(j, n-1) cout << " *";
		cout << '\n';
	}
}
