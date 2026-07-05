#include <iostream>
#include <vector>
#include <string.h>
#include <queue>
#include <algorithm>
#include <string>
#define inf 2000000000
using namespace std;

typedef pair<int, int> P;
typedef long long ll;
int n, k,cnt;
vector<P> v;
int kind[100001];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> k >> n;
	
	
	for (int i = 0; i < n; i++) {
		int q, w;
		cin >> q >> w;
		v.push_back({ q,w });
	}
	sort(v.begin(), v.end());

	int l = 0,r=0;
	
	P res = make_pair(inf, inf); // 길이, 위치
	while (r < n) {
		if (!kind[v[r].second]) cnt++;

		kind[v[r].second]++;
		
		if (cnt == k) {
			while (1) {
				ll dist = v[r].first + v[l].first;
				if (res.first > v[r].first - v[l].first) {
					ll t = dist / 2;
					if (dist % 2 != 0 && dist < 0) {
						t -= 1;
					}
					res = make_pair(v[r].first - v[l].first, t);
				}
				cnt--;
				kind[v[l].second]--;
				l++;
				if (kind[v[l-1].second] == 0 || l>=r) break;
				else cnt++;
				
			}
			
		}
		r++;
	}

	cout << res.second << '\n';
	return 0;
}
