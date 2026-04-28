#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define x first
#define y second

#define SEG_SIZE 524288

using T_node = int;

using T_lazy = int;

int N;
int a[SEG_SIZE];

long long fct[800000];
long long ifct[800000];
const long long MOD = 1'000'000'007LL;
long long pp(long long x, long long n){
	if(n==1) return x;
	if(n&1) return x*pp(x,n-1)%MOD;
	long long h=pp(x,n/2);
	return h*h%MOD;
}
long long combi(int x, int y){
	if(y<0||y>x) return 0;
	return fct[x]*ifct[y]%MOD*ifct[x-y]%MOD;
}

typedef struct{
    T_node val;
    T_lazy lazy;
} node;
node segtree[SEG_SIZE*2];

// composite of lazy - MODIFICATION WOULD BE NEEDED
T_lazy lazy_lazy(T_lazy a, T_lazy b){
    return a+b;
}

// apply lazy to node - FILL HERE
T_node node_lazy(T_node a, T_lazy b, int len){
	return a+b;
}

// make a parent node - FILL HERE
T_node node_node(T_node a, T_node b){
	return min(a,b);
}

// MODIFICATION WOULD BE NEEDED
T_lazy identity_lazy(){
    return 0;
}

// MODIFICATION WOULD BE NEEDED
T_node identity_node(){
    return 1'000'000'000;
}

// no modification needed
void update_node(int node, int nl, int nr){
    if(node >= SEG_SIZE*2) return;
    if(segtree[node].lazy == identity_lazy()) return;
    segtree[node].val = node_lazy(segtree[node].val, segtree[node].lazy, nr - nl + 1);
    if(node < SEG_SIZE){
        segtree[node*2].lazy = lazy_lazy(segtree[node*2].lazy, segtree[node].lazy);
        segtree[node*2+1].lazy = lazy_lazy(segtree[node*2+1].lazy, segtree[node].lazy);
    }
    segtree[node].lazy = identity_lazy();
}

// no modification needed
void update_range(int l, int r, int node, int nl, int nr, T_lazy val){
    if(node >= SEG_SIZE*2) return;
    update_node(node, nl, nr);
	if(r < nl || nr < l) return;
    if(l <= nl && nr <= r){
        segtree[node].lazy = lazy_lazy(segtree[node].lazy, val);
        update_node(node, nl, nr);
    }
    else{
        int mid = (nl+nr)/2;
        update_range(l, r, node*2, nl, mid, val);
        update_range(l, r, node*2+1, mid+1, nr, val);
        segtree[node].val = node_node(segtree[node*2].val, segtree[node*2+1].val);
    }
}

// no modification needed
T_node eval(int l, int r, int node, int nl, int nr){
    update_node(node, nl, nr);
    if(r < nl || nr < l) return identity_node();
    if(l <= nl && nr <= r) return segtree[node].val;
    int mid = (nl+nr)/2;
    return node_node(eval(l, r, node*2, nl, mid), eval(l, r, node*2+1, mid+1, nr));
}

// FILL HERE: including input process
void init(){
	string s;
	cin >> s;
	for(int i=1;i<=N;i++){
		a[i]=(s[i-1]=='('?1:-1);
		segtree[SEG_SIZE+i].val = segtree[SEG_SIZE+i-1].val+a[i];
	}
	for(int i=N+1;i<SEG_SIZE;i++) segtree[SEG_SIZE+i].val=segtree[SEG_SIZE+i-1].val;
    for(int i=SEG_SIZE-1;i>0;i--){
        segtree[i].val = node_node(segtree[i*2].val, segtree[i*2+1].val);
    }
    for(int i=1;i<SEG_SIZE*2;i++) segtree[i].lazy = identity_lazy();
	fct[0]=1;
	for(int i=1;i<800000;i++) fct[i]=fct[i-1]*i%MOD;
	ifct[799999]=pp(fct[799999],MOD-2);
	for(int i=799998;i>=0;i--) ifct[i]=ifct[i+1]*(i+1)%MOD;
}

// FILL HERE: including input process
// TIP: eval(x, y, 1, 0, SEG_SIZE-1)
void query(){
	int q;
	cin >> q;
	if(q==1){
		int x;
		cin >> x;
		if(a[x]==1){
			a[x]=-1;
			update_range(x, SEG_SIZE-1, 1, 0, SEG_SIZE-1, -2);
		}
		else{
			a[x]=1;
			update_range(x, SEG_SIZE-1, 1, 0, SEG_SIZE-1, 2);
		}
	}
	else{
		int x,y;
		cin >> x >> y;
		x--;
		if(eval(0,x,1,0,SEG_SIZE-1)<0){
			cout << "0\n";
			return;
		}
		int ppap = eval(x,x,1,0,SEG_SIZE-1);
		int ppbp = eval(N,N,1,0,SEG_SIZE-1);
		int ppcp = eval(y,y,1,0,SEG_SIZE-1);
		if(eval(y,N,1,0,SEG_SIZE-1)<ppbp){
			cout << "0\n";
			return;
		}
		ppcp-=ppbp;
		int ppdp = ((y-x)+(ppcp-ppap))/2, ppep = ((y-x)-(ppcp-ppap))/2;
		// cout << ppdp << " " << ppep << " " << ppap << "\n";
		cout << (combi(ppdp+ppep,ppdp)+MOD-combi(ppdp+ppep,ppdp+ppap+1))%MOD << "\n";
	}
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    init();
    int M;
    cin >> M;
    for(int i=0;i<M;i++){
        query();
    }
}
