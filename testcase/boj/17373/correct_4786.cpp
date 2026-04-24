#include <bits/stdc++.h>
using namespace std;
const int MX = 1e6+3;
typedef long long ll;
int lsb(int i) {return i&(-i);}
struct BIT {
    vector<ll> bit;
    int n;
    BIT() {};
    BIT(int _n) { bit.resize(_n+1); n=_n;};
    void update(int i, ll v) {
        while(i <= n) {
            bit[i] += v;
            i += lsb(i);
        }
    };
    ll query(int i) {
        ll ret = 0;
        while(i) {
            ret += bit[i];
            i -= lsb(i);
        }
        return ret;
    };
};
int firstocc[MX], lastocc[MX], arr[MX], stcnt[MX];
ll acc[MX];
vector<pair<ll, int>> qry[MX];
pair<int, int> ans[MX];
bool seen[MX];
pair<int, int> conv(ll t) {
	if(t > acc[MX-1])
		return {-1, -1};
	int l = 1, r = MX-1;
	while(l < r) {
		int m = (l+r)/2;
		if(acc[m] >= t) {
			r = m;
		} else
			l = m+1;
		//printf("at l=%d, r=%d, m=%d, acc[m]=%lld\n", l, r, m, acc[m]);
	}
	return {l, t-acc[l-1]};
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, M, Q;
	cin >> n >> M >> Q;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
		if(!firstocc[arr[i]])
			firstocc[arr[i]] = i;
		lastocc[arr[i]] = max(lastocc[arr[i]], i);
	}
	int occ = 0;
	for(int i=n; i>=1; i--) {
		if(firstocc[arr[i]] == i)
			stcnt[arr[i]] = M-occ;
		if(!seen[arr[i]]) {
			seen[arr[i]] = 1;
			occ++;
		}
	}
	//for(int i=1; i<=M; i++) {
	//	printf("acc[%d]=%lld\n", i, acc[i]);
	//}
	for(int i=1; i<=M; i++) {
		if(!seen[i])
			stcnt[i] = M;
	}
	for(int i=1; i<MX; i++) {
		acc[i] = acc[i-1]+stcnt[i];
	}
	for(int i=0; i<Q; i++) {
		ll t;
		ll a, b;
		cin >> t;
		tie(a, b) = conv(t);
		if(a == -1 && b == -1) {
			ans[i] = {-1, -1};
			continue;
		}
		//printf("t=%lld as query %lld, %lld\n", t, a, b);
		qry[a].push_back({b, i});
		//printf("query %lld is now k=%lld, t=%lld\n", t, a, b);
	}
	BIT bit(M+1);
	for(int i=1; i<=M; i++)
		bit.update(i, 1);
	for(int i=1; i<=M; i++) {
		if(seen[i]) continue;
		for(auto q: qry[i])
			ans[q.second] = {i, q.first};

	}
	for(int i=n; i>=1; i--) {
		if(firstocc[arr[i]] == i) {
			for(auto q: qry[arr[i]]) {
				ll k = arr[i], t = q.first, qryi = q.second;
				int l = 1, r = M;
				while(l < r) {
					int m = (l+r)/2;
					if(bit.query(m) >= t) {
						r = m;
					} else {
						l = m+1;
					}
				}
				ans[qryi] = {k, l};
			}
			//printf("at i=%lld, firstocc of %lld\n", i, arr[i]);
		}
		if(lastocc[arr[i]] == i) {
			//printf("at i=%lld, lastocc of %lld\n", i, arr[i]);
			bit.update(arr[i], -1);
		}
	}
	for(int i=0; i<Q; i++) {
		cout << ans[i].first << ' ' << ans[i].second << '\n';		
	}
}
