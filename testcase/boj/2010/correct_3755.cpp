#include <iostream>

using namespace std;

int main() {
	int n, ans, temp;
	cin >> n;
	ans = -n+1;
	for(int i=0; i<n; i++) {
		cin >> temp;
		ans += temp;
	}
	cout << ans;

}
