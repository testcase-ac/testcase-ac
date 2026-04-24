#include <bits/stdc++.h>
using namespace std;

pair<int, int> pos(int i) {
	i--;
	return {i%4, i/4};
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int a, b;
	cin >> a >> b;
	auto p1 = pos(a), p2 = pos(b);
	cout << abs(p1.first-p2.first) + abs(p1.second-p2.second); 
}
