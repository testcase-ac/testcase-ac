#include<bits/stdc++.h>
using namespace std;

#define va(x) x.begin(),x.end()
#define mxt 1048576
vector<int> st[mxt];
int a[mxt/2], b[mxt];

void upt( int x, int l, int r, int n ){
    if( n<l ) return;
    if( l==r ){
        st[x].push_back(a[l]);
        b[x] = a[l];
        return;
    }
    upt( x*2, l, (l+r)/2, n );
    upt( x*2+1, (l+r)/2+1, r, n );
    for( auto i : st[x*2] ) st[x].push_back(i);
    for( auto i : st[x*2+1] ) st[x].push_back(i);
    sort( va(st[x]) );
    int cnt = 0;
    for( int i=0, l = int(st[x].size()); i<l; i++ ){
        int j = i;
        while( j<l && st[x][i]==st[x][j] ) j++;
        if( cnt < j-i ){
            cnt = j-i;
            b[x] = st[x][i];
        }
        i = j-1;
    }
}
void candi( set<int> &di, int x, int l, int r, int l2, int r2 ){
    if( r<l2 || r2<l ) return;
    if( l2<=l && r<=r2 ){
        di.insert(b[x]);
        return;
    }
    candi( di, x*2, l, (l+r)/2, l2, r2 );
    candi( di, x*2+1, (l+r)/2+1, r, l2, r2 );
}
int sum( int x, int l, int r, int l2, int r2, int k ){
    if( r<l2 || r2<l ) return 0;
    if( l2<=l && r<=r2 ){
        return upper_bound( va(st[x]), k ) - lower_bound( va(st[x]), k );
    }
    return sum(x*2,l,(l+r)/2,l2,r2,k) + sum(x*2+1,(l+r)/2+1,r,l2,r2,k);
}
int main(){
    int n, m, q, leaf=1;
    scanf("%d%d",&n,&m);
    for( int i=1; i<=n; i++ ) scanf("%d",&a[i]);
    while( leaf<n ) leaf*=2;
    upt( 1, 1, leaf, n );
    scanf("%d",&q);
    while( q-- ){
        int l, r, ans=-1;
        scanf("%d%d",&l,&r);
        set<int> di;
        candi( di, 1, 1, leaf, l, r );
        for( auto i : di ){
            if( (r-l+1)/2 < sum(1,1,leaf,l,r,i) ){
                ans = i;
                break;
            }
        }
        if( ans<0 ) printf("no\n");
        else printf("yes %d\n",ans);
    }
    return 0;
}
