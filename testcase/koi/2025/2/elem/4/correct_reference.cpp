#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct segTree{
    int tree[1<<20], lazy[1<<20];

    void propagate(int i, int l, int r){
        tree[i] += lazy[i];
        if(l!=r){
            lazy[i*2] += lazy[i];
            lazy[i*2+1] += lazy[i];
        }
        lazy[i] = 0;
    }

    void update(int i, int l, int r, int s, int e, int v){
        propagate(i, l, r);
        if(r<s || e<l) return;
        if(s<=l && r<=e){
            lazy[i] = v;
            propagate(i, l, r);
            return;
        }
        int m = (l+r)>>1;
        update(i*2, l, m, s, e, v);
        update(i*2+1, m+1, r, s, e, v);
        tree[i] = max(tree[i*2], tree[i*2+1]);
    }

    int query(int i, int l, int r, int s, int e){
        propagate(i, l, r);
        if(r<s || e<l) return 0;
        if(s<=l && r<=e) return tree[i];
        int m = (l+r)>>1;
        return max(query(i*2, l, m, s, e), query(i*2+1, m+1, r, s, e));
    }
} tree;

int n;
int L[200005], R[200005];

int main(){
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        scanf("%d %d", &R[i], &L[i]);
    }
    vector<int> v;
    for(int i=1; i<=n; i++){
        v.push_back(L[i]);
        v.push_back(R[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    int k = (int)v.size();
    for(int i=1; i<=n; i++){
        L[i] = lower_bound(v.begin(), v.end(), L[i]) - v.begin();
        R[i] = lower_bound(v.begin(), v.end(), R[i]) - v.begin();

        tree.update(1, 0, k-1, L[i], R[i]-1, 1);
        printf("%d\n", tree.query(1, 0, k-1, 0, k-1));
    }
}
