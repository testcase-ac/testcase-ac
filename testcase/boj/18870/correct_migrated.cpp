#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct Point {
	int o;
	int n;
	int index;
};

int main() {	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	vector<Point> arr(N);
	for (int i = 0; i < N; i++) {
		cin >> arr[i].o;
		arr[i].index = i;
	}

	sort(arr.begin(), arr.end(), [](const Point& a, const Point& b) 
		{
			return a.o < b.o;
		});

	int count = 0;
	arr[0].n = 0;
	for (int i = 1; i < N; i++) {
		if (arr[i].o == arr[i - 1].o) {
			arr[i].n = arr[i - 1].n;
		} else {
			arr[i].n = ++count;
		}
	}
	sort(arr.begin(), arr.end(), [](const Point& a, const Point& b)
		{
			return a.index < b.index;
		});
	for (int i = 0; i < N; i++) {
		cout << arr[i].n << " ";
	} return 0;
}
