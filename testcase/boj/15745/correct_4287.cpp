#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
int ans[MX], par[MX], sz[MX], mxsz;
pair<int, int> arr[MX];
tuple<int,int,int> qry[MX];
int f(int i) {return par[i] == i ? i : par[i] = f(par[i]);}
void join(int i, int j) {
	//printf("join %d and %d\n", i, j);
	i = f(i), j = f(j);
	par[i] = j;
	sz[j] += sz[i];
	mxsz = max(mxsz, sz[j]);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, b;
	cin >> n >> b;
	for(int i=0; i<n; i++) {
		cin >> arr[i].first;
		arr[i].second = i;
	}
	for(int i=0; i<b; i++) {
		int s, d;
		cin >> s >> d;
		qry[i] = {s, d, i};
	}
	sort(arr, arr+n);
	reverse(arr, arr+n);
	sort(qry, qry+b);
	reverse(qry, qry+b);
	memset(par, -1, sizeof par);
	int i = 0, j = 0;
	while(j < b) {
		//printf("at j=%d. s=%d\n", j, get<0>(qry[j]));
		while(i < n && arr[i].first > get<0>(qry[j])) {
			par[arr[i].second] = arr[i].second;
			sz[arr[i].second] = 1;
			mxsz = max(mxsz, 1);
			//printf("open at %d\n", arr[i].second);
			if(arr[i].second && par[arr[i].second-1] != -1) {
				join(arr[i].second, arr[i].second-1);
			}
			if(par[arr[i].second+1] != -1) {
				join(arr[i].second, arr[i].second+1);
			}
			i++;
		}
		int s, d, ind;
		tie(s, d, ind) = qry[j];
		//printf("mxsz is %d, d is %d\n", mxsz, d);
		ans[ind] = mxsz < d;
		j++;
	}
	for(i=0; i<b; i++)
		cout << ans[i] << '\n';
}
