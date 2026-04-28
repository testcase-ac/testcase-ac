#include <cstdio>
#include <algorithm>
using namespace std;
 
struct data {
    int l, r, d, f; bool h;
    bool operator== (const data& b) const { return l == b.l; }
    bool operator< (const data& b) const { return l < b.l; }
};
 
const int inf = 987654321;
int n, k, w;
data a[2504], h[2504];
 
int main()
{
    int _;
 
    scanf("%d", &n); n = n/2-1;
 
    scanf("%d%d", &_, &_);
    for (int i=0; i<n; i++) scanf("%d%d%d%d", &a[i].l, &_, &a[i].r, &a[i].d);
    scanf("%d%d", &w, &_);
 
    scanf("%d", &k);
    for (int i=0; i<k; i++) scanf("%d%d%d%d", &h[i].l, &_, &h[i].r, &h[i].d);
    sort(h, h+k);
 
    int j=0;
    for (int i=0; i<k; i++) {
        for (; j<n; j++) if (a[j] == h[i]) {
            a[j].h = 1;
            break;
        }
    }
 
    int md;
    md=inf;
    for (int i=0; i<n; i++) {
        if (a[i].h) md = a[i].d;
        if (a[i].h or md != inf) {
            md = min(md, a[i].d);
            a[i].f = max(a[i].f, md);
        }
    }
    md=inf;
    for (int i=n-1; i>=0; i--) {
        if (a[i].h) md = a[i].d;
        if (md != inf) {
            md = min(md, a[i].d);
            a[i].f = max(a[i].f, md);
        }
    }
    int r = 0;
    for (int i=0; i<n; i++) r += (a[i].r-a[i].l) * (a[i].d - a[i].f);
    printf("%d\n", r);
}
