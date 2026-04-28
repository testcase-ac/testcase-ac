#include<stdio.h>
#include<algorithm>
#include<vector>
#include<math.h>
#include<cassert>
#include<stdlib.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long ll;

const int LIM = 1000000000;

ll operator ^(const pii &l, const pii &r){
	return (ll)l.first * r.second - (ll)l.second * r.first;
}

pii operator -(const pii &l, const pii &r){
	return pii(l.first - r.first, l.second - r.second);
}

ll sq(ll x){ return x*x; }
ll sz(pii x){ return sq(x.first) + sq(x.second); }

void convex_hull(vector<pii> &D, vector<pii> &C){
	sort(D.begin(), D.end());
	D.erase(unique(D.begin(), D.end()), D.end());
	for(int i = 1; i < D.size(); i++) D[i] = D[i] - D[0]; D[0] = pii(0, 0);
	sort(D.begin()+1, D.end(), [](const pii &l, const pii &r){
		if( l^r ) return (l^r) < 0;
		return sz(l) < sz(r);
	});
	for(pii c : D){
		while(C.size() >= 2 && ((C[C.size()-2]-C.back() ^ (c - C.back())) <= 0 )) C.pop_back();
		C.push_back(c);
	}
}

void convex_hull_wrong(vector<pii> &D, vector<pii> &C){
	sort(D.begin(), D.end());
	D.erase(unique(D.begin(), D.end()), D.end());
	for(int i = 1; i < D.size(); i++) D[i] = D[i] - D[0]; D[0] = pii(0, 0);
	sort(D.begin()+1, D.end(), [](const pii &l, const pii &r){
		long double x = atan2(l.second, l.first), y = atan2(r.second, r.first);
		if( x == y ) return sz(l) < sz(r);
		return x > y;
	});
	for(pii c : D){
		while(C.size() >= 2 && ((C[C.size()-2]-C.back() ^ (c - C.back())) <= 0 )) C.pop_back();
		C.push_back(c);
	}
}

int main()
{
	int N;
	assert(scanf("%d", &N) == 1);
	assert( 1 <= N && N <= 100);
	vector<pii> E, D, C;
	for(int i = 1; i <= N; i++){
		pii X;
		assert(scanf("%d%d", &X.first, &X.second) == 2);
		assert( -LIM <= X.first && X.first <= LIM && -LIM <= X.second && X.second <= LIM);
		D.push_back(X);
	}
	convex_hull(D, C);
	convex_hull_wrong(D, E);

	sort(C.begin(), C.end());
	sort(E.begin(), E.end());

	assert(C != E);
	return 0;
}

