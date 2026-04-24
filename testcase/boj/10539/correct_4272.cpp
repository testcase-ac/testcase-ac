#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int sum = 0, avg;
	for(int i=0; i<n; i++) {
		cin >> avg;
		cout << avg*(i+1)-sum << ' ';
		sum += avg*(i+1)-sum;
	}
}
