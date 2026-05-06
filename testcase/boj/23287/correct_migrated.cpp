#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
ull mul(ull a,ull b,ull m) {return (ull)((__int128)a*b%m);}
ull pw(ull a,ull b,ull m) {
    a%=m;
	ull r=1;
	while(b) {
		if(b&1) r=mul(r,a,m);
		a=mul(a,a,m);
		b>>=1;
	} return r;
}
bool chk(ull n,ull a) {
    if(a%n==0) return 1;
    ull k=n-1;
    while(1) {
        ull t=pw(a,k,n);
        if(t==n-1) return 1;
        if(k%2) return (t==1||t==n-1);
        k/=2;
    }
}
bool isp(ull n) {
    if(n==2||n==3) return 1;
    if(n%2==0) return 0;
    ull a[]={2,3,5,7,11,13,17,19,23};
    for(int i=0;i<9;i++) if(!chk(n,a[i])) return 0;
    return 1;
}
ull gcd(ull a,ull b) {return b?gcd(b,a%b):a;}
ull dv(__int128 n) {
    if(n%2==0) return 2;
    if(isp(n)) return n;
    __int128 x=rand()%(n-2)+2,y=x,c=rand()%10+1,g=1;
    while(g==1) {
        x=(x*x%n+c)%n;
        y=(y*y%n+c)%n;
        y=(y*y%n+c)%n;
        g=gcd(abs(x-y),n);
        if(g==n) return dv(n);
    } return isp(g)?g:dv(g);
}
ull tonelli_shanks(ull n,ull p) {
    ull s=0,q=p-1;
    while((q&1)==0) {q/=2;s++;}
    if(s==1) {
        ull r=pw(n,(p+1)/4,p);
        if(mul(r,r,p)==n) return r;
        return 0;
    } ull z=1;
    while(pw(++z,(p-1)/2,p)!=p-1);
    ull c=pw(z,q,p);
    ull r=pw(n,(q+1)/2,p);
    ull t=pw(n,q,p);
    ull m=s;
    while(t!=1) {
        ull tt=t,i=0;
        while(tt!=1) {
            tt=mul(tt,tt,p);i++;
            if(i==m) return 0;
        } __int128 b=pw(c,pw(2,m-i-1,p-1),p);
        ull bb=(b*b)%p;
        r=mul(r,b,p);
        t=mul(t,bb,p);
        c=bb;
        m=i;
    } if(mul(r,r,p)==n) return r;
    return 0;
}
pair<ull,ull> cornacchia(ull n) {
	ull r1=n,r2;
	r2=tonelli_shanks(r1-1,r1);
	while((__int128)(r1)*r1>=n) {
		ull t=r1%r2;
		r1=r2;
		r2=t;
	} ull x=r1,y=sqrt(n-r1*r1);
	return {x,y};
}
void solve2(ull n,ull k,vector<ull> v) {
    for(int i=0;i<v.size()-1;i++) {
        if(v[i]==v[i+1]) {
            n/=(v[i]*v[i]);
            k*=v[i];
            i++;
        }
    } v.clear();
    while(n>1) {
        ull d=dv(n);
        v.push_back(d);
        n/=d;
    } sort(v.begin(),v.end());
    pair<ull,ull> r={1,0},rr;
    for(ull d:v) {
        rr=cornacchia(d);
        ull a=r.first*rr.first,b=r.second*rr.second;
        if(a<b) swap(a,b);
        r={r.first*rr.second+r.second*rr.first,a-b};
    } cout<<k*r.first<<' '<<k*r.second;
}
int main() {
    ull n,nn;
    cin>>n;
    nn=n;
    if(n==1) {
        cout<<"1 0 0 0";
        return 0;
    } vector<ull> v;
    while(n>1) {
        ull d=dv(n);
        v.push_back(d);
        n/=d;
    } sort(v.begin(),v.end());
    bool x=1;
    if(v.size()%2==0) {
        for(int i=0;i<v.size();i+=2) {
            if(v[i]!=v[i+1]) {
                x=0;
                break;
            }
        } if(x) {
            ull k=1;
            for(int i=0;i<v.size();i+=2) k*=v[i];
            cout<<k<<" 0 0 0";
            return 0;
        }
    } x=1;
    int k=1;
    for(int i=1;i<v.size();i++) {
        if(v[i]==v[i-1]) k++;
        else {
            if(v[i-1]%4==3&&k%2) {
                x=0;
                break;
            } k=1;
        }
    } if(v[v.size()-1]%4==3&&k%2) x=0;
    if(x) {
        solve2(nn,1,v);
        cout<<" 0 0";
        return 0;
    } n=nn;
    ull four=1;
    while(n%4==0) {
        four*=2;
        n/=4;
    } if(n%8==7) {
        cout<<four<<' ';
        n--;
    } else cout<<"0 ";
    for(ull t=1;;t++) {
        ull tst=n-t*t;
        ull tt=tst;
        vector<ull> vv;
        while(tst>1) {
            ull d=dv(tst);
            vv.push_back(d);
            tst/=d;
        } sort(vv.begin(),vv.end());
        x=1;k=1;
        for(int i=1;i<vv.size();i++) {
            if(vv[i]==vv[i-1]) k++;
            else {
                if(vv[i-1]%4==3&&k%2) {
                    x=0;
                    break;
                } k=1;
            }
        } if(vv[vv.size()-1]%4==3&&k%2) x=0;
        if(x) {
            cout<<t*four<<' ';
            n-=t*t;
            break;
        }
    } v.clear();
    nn=n;
    while(nn>1) {
        ull d=dv(nn);
        v.push_back(d);
        nn/=d;
    } sort(v.begin(),v.end());
    solve2(n,four,v);
}
