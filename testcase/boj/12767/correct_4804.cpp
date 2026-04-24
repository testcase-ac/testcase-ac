#include <bits/stdc++.h>
using namespace std;
struct Node {
	int val, ind, child[2];
};
vector<vector<int>> ptnls;
vector<int> ptn;
Node tree[20];
int nextind;
void inorder(int i) {
	if(tree[i].child[0] != -1) inorder(tree[i].child[0]);
	tree[i].ind = nextind++;
	if(tree[i].child[1] != -1) inorder(tree[i].child[1]);
}
void preorder(int i) {
	ptn.push_back(tree[i].ind);
	for(int j=0; j<2; j++)
		if(tree[i].child[j] != -1) preorder(tree[i].child[j]);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k, ans=0;
	cin >> n >> k;
	while(n--) {
		memset(tree, -1, sizeof tree);
		int val;
		cin >> val;
		tree[0].val = val;
		for(int i=1; i<k; i++) {
			cin >> val;
			int at = 0;
			while(1) {
				int ch = val < tree[at].val;
				if(tree[at].child[ch] == -1) {
					tree[at].child[ch] = i;
					tree[i].val = val;
					break;
				} else {
					at = tree[at].child[ch];
				}
			}
		}
		nextind = 0;
		inorder(0);
		ptn.clear();
		preorder(0);
		bool ok = true;
		for(vector<int> &p: ptnls)
			if(p == ptn) {
				ok = false;
				break;
			}
		if(ok) {
			ptnls.push_back(ptn);
			ans++;			
		}
	}
	cout << ans;
}
