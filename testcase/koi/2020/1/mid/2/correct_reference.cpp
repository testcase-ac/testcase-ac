#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int mod = 1e9 + 7;
const int MAXC = 2000005;

struct Daps{
	int weight;
	vector<int> sln;
	Daps(){
		weight = 0;
		sln = vector<int>();
	}
	bool operator<(const Daps &d)const{
		if(weight != d.weight) return weight < d.weight;
		return sln < d.sln;
	}
}dap;

int n;
int req[5];
int a[20][5];

void bktk(vector<int> v, Daps d, int depth){
	if(depth == n){
		for(int i=0; i<4; i++){
			if(v[i] < req[i]) return;
		}
		dap = min(dap, d);
		return;
	}
	bktk(v, d, depth + 1);
	for(int i=0; i<4; i++) v[i] += a[depth][i];
	d.weight += a[depth][4];
	d.sln.push_back(depth + 1);
	bktk(v, d, depth + 1);
}

int main(){
	dap.weight = 1e9;
	cin >> n;
	for(int i=0; i<4; i++) cin >> req[i];
	for(int i=0; i<n; i++){
		for(int j=0; j<5; j++){
			cin >> a[i][j];
		}
	}
	vector<int> foo(4);
	bktk(foo, Daps(), 0);
	if(dap.weight > 1e8) puts("-1");
	else{
		printf("%d\n", dap.weight);
		for(int i=0; i<sz(dap.sln); i++){
			printf("%d",dap.sln[i]);
			if(i + 1< sz(dap.sln)) printf(" ");
			else printf("\n");
		}
	}
}
