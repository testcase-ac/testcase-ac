#include <iostream>

using namespace std;
#define MAXN 30
long long arr[MAXN+1];
int main() {
	int n;
	cin >> n;
	if(n % 2) return !(cout << 0);
	arr[0] = 1;
	arr[2] = 3;
	for(int i=4; i<=30; i+=2) {
		arr[i] += (arr[i-2] * 3);
		for(int j=4; j<=i; j++) {
			arr[i] += (arr[i-j] * 2);
		}
	}
	cout << arr[n];
	
}
