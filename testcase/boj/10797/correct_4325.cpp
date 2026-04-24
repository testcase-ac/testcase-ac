#include <iostream>
#define rep(i, n) for(int i=0; i<(n); i++)
using namespace std;

int main() {
	int n, arr[5];
	cin >> n;
	rep(i, 5) cin >> arr[i];
	int ans = 0;
	rep(i, 5) if(arr[i] == n) ans++;
	cout << ans;
}
