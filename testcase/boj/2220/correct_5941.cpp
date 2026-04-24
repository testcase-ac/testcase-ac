#include <bits/stdc++.h>
using namespace std;
int arr[100001], i;
void f(int t) {
	if(2*t > i) {
		arr[i+1] = arr[t];
		return;
	}
	f(2*t);
	arr[2*t] = arr[t];
}
int main() {
	int n;
	cin >> n;
	arr[1] = 1;
	for(i=1; i<n; i++) {
		f(1);
		arr[1] = i+1;
	}
	for(int t=1; t<=n; t++)
		cout << arr[t] << ' ';
}
