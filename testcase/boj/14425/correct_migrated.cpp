#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
   
	int n,m;
	cin >> n;
	cin >> m;

	unordered_set<string> nStr;
	for (int i = 0; i < n; ++i) {
		string a;
		cin >> a;
		nStr.insert(a);
	}
	
	int count = 0;
	for (int i = 0; i < m; ++i) {
		string b;
		cin >> b;
		if (nStr.find(b) != nStr.end())
			++count;
	}
	cout << count;
}
