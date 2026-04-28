#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

int calcr(int sz, int r, int e);
int calccd(int sz, int c, int e);
int calccu(int sz, int c, int e);
int calcr2(int sz, int r);
int calcc2(int sz, int c);
int calc(int sz, int x1, int x2, int y);
int calc2(int sz, int y1, int y2, int x);

int calcr(int sz, int r, int e){
    if (!e) return 0;
    if (r==(1<<(sz-1))){
        if (e==(1<<sz)) return 2;
        return 1;
    }

    int ret = 0;
    if (r>(1<<(sz-1))){
        r -= (1<<(sz-1));
        if (e>=(1<<(sz-1))){
            ret += calcr2(sz-1, r);
            e -= (1<<(sz-1));
        }
        return ret + calcr(sz-1, r, e);
    }
    else{
        if (e>=(1<<(sz-1))) return calcc2(sz-1, r) + calccu(sz-1, r, e-(1<<(sz-1)));
        return calccd(sz-1, r, e);
    }
}

int calccd(int sz, int c, int e){
    if (!e) return 0;
    if (c==(1<<(sz-1))){
        if (e<=(1<<(sz-1))) return 0;
        return 1;
    }

    int ret = 0;
    if (c>(1<<(sz-1))) c = (1<<sz) - c;
    if (e>=(1<<(sz-1))) return calcr2(sz-1, c) + calccd(sz-1, c, e-(1<<(sz-1)));
    return calcr(sz-1, c, e);
}

int calccu(int sz, int c, int e){
    if (!e) return 0;
    if (c==(1<<(sz-1))){
        if (e<(1<<(sz-1))) return 0;
        return 1;
    }

    int ret = 0;
    if (c>(1<<(sz-1))) c = (1<<sz) - c;
    if (e>=(1<<(sz-1))) return calcc2(sz-1, c) + calcr(sz-1, c, e-(1<<(sz-1)));
    return calccu(sz-1, c, e);
}

int dpr2[16][40040];
int calcr2(int sz, int r){
    //if (sz<=15 && dpr2[sz][r]!=-1) return dpr2[sz][r];
    if (sz==1) return dpr2[1][1] = 2;
    if (sz<=15){
        if (r<(1<<(sz-1))) return dpr2[sz][r] = calcc2(sz-1, r)*2;
        if (r==(1<<(sz-1))) return dpr2[sz][r] = 2;
        return dpr2[sz][r] = calcr2(sz-1, r-(1<<(sz-1)))*2;
    }

    if (r<(1<<(sz-1))) return calcc2(sz-1, r)*2;
    if (r==(1<<(sz-1))) return 2;
    return calcr2(sz-1, r-(1<<(sz-1)))*2;
}

int dpc2[16][40040];
int calcc2(int sz, int c){
    if (c>=(1<<(sz-1))) c = (1<<sz) - c;
    //if (sz<=15 && dpc2[sz][c]!=-1) return dpc2[sz][c];
    if (sz==1) return dpc2[1][1] = 1;
    if (c==(1<<(sz-1))){
        if (sz<=15) return dpc2[sz][c] = 1;
        return 1;
    }

    if (sz<=15) return dpc2[sz][c] = calcr2(sz-1, c) + calcc2(sz-1, c);
    return calcr2(sz-1, c) + calcc2(sz-1, c);
}

void init(){
    for (int i=0;i<16;i++){
        fill(dpr2[i], dpr2[i]+(1<<i)+1, -1);
        fill(dpc2[i], dpc2[i]+(1<<i)+1, -1);
    }
}

int calc(int sz, int x1, int x2, int y){
    if (x1==x2) return 0;
    if (y==(1<<(sz-1))){
        int ret = 0;
        if (x1==0) ret++;
        if (x2==(1<<sz)) ret++;
        return ret;
    }

    if (y<(1<<(sz-1))){
        if (x2<(1<<(sz-1))) return calc2(sz-1, x1, x2, y);
        if (x1>(1<<(sz-1))) return calc2(sz-1, (1<<sz)-x2, (1<<sz)-x1, y);
        return calccu(sz-1, y, (1<<(sz-1))-x1) + calccu(sz-1, y, x2-(1<<(sz-1)));
    }
    else{
        if (x2<(1<<(sz-1))) return calc(sz-1, x1, x2, y-(1<<(sz-1)));
        if (x1>(1<<(sz-1))) return calc(sz-1, (1<<sz)-x2, (1<<sz)-x1, y-(1<<(sz-1)));
        return calcr(sz-1, y-(1<<(sz-1)), (1<<(sz-1))-x1) + calcr(sz-1, y-(1<<(sz-1)), x2-(1<<(sz-1)));
    }
}

int calc2(int sz, int y1, int y2, int x){
    if (y1==y2) return 0;
    if (x==(1<<(sz-1))){
        if (y1<=(1<<(sz-1)) && y2>(1<<(sz-1))) return 1;
        return 0;
    }

    if (x>(1<<(sz-1))) x = (1<<sz) - x;

    if (y2<(1<<(sz-1))) return calc(sz-1, y1, y2, x);
    if (y1>(1<<(sz-1))) return calc2(sz-1, y1-(1<<(sz-1)), y2-(1<<(sz-1)), x);
    return calcr(sz-1, x, (1<<(sz-1))-y1) + calccd(sz-1, x, y2-(1<<(sz-1)));
}

bool solve(){
    int n;
    scanf("%d", &n);
    if (!n) return 0;
    int x1, x2, y;
    scanf("%d %d %d", &x1, &x2, &y);
    y = (1<<n) - y;
    if (y==0 || y==(1<<n)) printf("0\n");
    else printf("%d\n", calc(n, x1, x2, y));
    return 1;
}

int main(){
    init();
    while(solve());
    return 0;
}
