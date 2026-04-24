#include <bits/stdc++.h>
using namespace std;

long long arr[1000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	sort(arr, arr+n);
	if(arr[0] != 1)
		return !(cout << 1);
	int sum = arr[0];
	for(int i=1; i<n; i++){
		if(arr[i] > sum + 1)
		       return !(cout << sum+1);
		sum += arr[i];	
	}
	cout << sum+1;
}
