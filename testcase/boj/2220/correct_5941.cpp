#include <bits/stdc++.h>
using namespace std;
int arr[100001], i;
void f(int t) {
	if(t == i) {
		arr[i+1] = arr[t];
		return;
	}
	int child = i;
	while(child/2 != t)
		child /= 2;
	f(child);
	arr[child] = arr[t];
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
