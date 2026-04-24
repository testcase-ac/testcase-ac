#include <iostream>
#include <algorithm>
#include <vector>

#define rep(i, n) for(int i=0; i<(n); i++)
using namespace std;

int main() {
	vector<int> arr(3);
	rep(i, 3) cin >> arr[i];
	cout << (max(arr[1] - arr[0], arr[2] - arr[1]) - 1);
}
