#include <iostream>
#include <algorithm>
using namespace std;

struct p {
	int x;
	int y;
};
bool compare(p a, p b) {
	if (a.x == b.x) {
		return a.y < b.y;
	} else {
		return a.x < b.x;
	}
}
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int n, tmp;
	cin >> n;
	p arr[100001];
	for (int i = 0; i < n; i++) {
		cin >> arr[i].x >> arr[i].y;
	} sort(arr, arr + n, compare);
    for (int i = 0; i < n; i++) {
		cout << arr[i].x << " " << arr[i].y << "\n";
	}
}
