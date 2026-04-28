#include<bits/stdc++.h>
using namespace std;
using bs = unsigned long long;
using pi = pair<int, int>;
const int MAXN = 100005;
 
int chk[MAXN];
bs msk[2000];
 
void upload(int s, int l){
	auto get_slowa = [&](int s, int l){
		bs ret = 0;
		ret |= (msk[s >> 6] >> (s & 63));
		if(s & 63){
			auto fu = msk[(s >> 6) + 1] & ((1ull << (s & 63)) - 1ull);
			ret |= (fu << (64 - (s & 63)));
		}
		if(l < 64) ret &= (1ull << l) - 1ull;
		return ret;
	};
	for(int i=0; i<l; i+=64){
		auto slowa = get_slowa(s + i, min(64, l - i));
		msk[i >> 6] |= slowa;
	}
}
 
int main(){
	int n; scanf("%d",&n);
	int minv = 1e9;
	for(int i=0; i<n; i++){
		int x; scanf("%d",&x);
		minv = min(minv, x);
		chk[x]++;
	}
	if(chk[minv] == 1){
		cout << minv << endl;
		return 0;
	}
	for(int i=100000; i>minv; i--){
		if(chk[i] == 0) continue;
		for(int j=i; j<=100000; j+=i){
			upload(j, min(i, 100001 - j));
		}
		msk[i >> 6] |= (1ull << (i & 63)); 
	}
	int ret = 0;
	for(int i=100000; i>=0; i--){
		if((msk[i >> 6] >> (i & 63)) & 1){
			ret = max(ret, i % minv);
		}
	}
	cout << ret << endl;
}
