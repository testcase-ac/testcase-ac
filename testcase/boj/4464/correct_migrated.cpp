#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
ull pw(__int128 x,__int128 y,__int128 m) {
    x%=m;
    __int128 r=1;
    while(y) {
        if(y%2) r=(r*x)%m;
        x=(x*x)%m;
        y/=2;
    } return (ull)r;
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
bool isprime(ull n) {
    if(n==2||n==3) return 1;
    if(n%2==0) return 0;
    ull a[]={2,3,5,7,11,13,17,19,23};
    for(int i=0;i<9;i++) if(!chk(n,a[i])) return 0;
    return 1;
}
ull gcd(ull a,ull b) {return b?gcd(b,a%b):a;}
ull dv(__int128 n) {
    if(n%2==0) return 2;
    if(isprime(n)) return n;
    __int128 x=rand()%(n-2)+2,y=x,c=rand()%10+1,g=1;
    while(g==1) {
        x=(x*x%n+c)%n;
        y=(y*y%n+c)%n;
        y=(y*y%n+c)%n;
        g=gcd(abs(x-y),n);
        if(g==n) return dv(n);
    } return isprime(g)?g:dv(g);
}
vector<pair<ull,int>> factor(ull n) {
	unordered_map<ull,int> m;
	vector<ull> v;
	while(n>1) {
		ull d=dv(n);
		m[d]=0;
		while(n%d==0) {
			n/=d;
			m[d]++;
		} v.push_back(d);
	} vector<pair<ull,int>> r;
	for(auto i:v) r.push_back({i,m[i]});
	return r;
}
int main() {
    ull n;
    while(1) {
        cin>>n;
        if(!n) return 0;
        cout<<n<<": ";
        int l=(to_string(n)).length();
        if(l%2) {
            cout<<"no\n";
            continue;
        } vector<ull> d;
        auto v=factor(n);
        d.push_back(1);
        for(int i=0;i<v.size();i++) {
            vector<ull> t;
            for(int j=0;j<d.size();j++) {
                ull x=1;
                for(int k=0;k<=v[i].second;k++) {
                    t.push_back(d[j]*x);
                    x*=v[i].first;
                }
            } d=t;
        } bool f=0;
        string s=to_string(n);
        sort(s.begin(),s.end());
        for(int i=0;i<d.size();i++) {
            ull a=d[i],b=n/a;
            string p=to_string(a),q=to_string(b),r=p+q;
            sort(r.begin(),r.end());
            if(s==r&&(a%10||b%10)) {
                int x=p.length(),y=q.length();
                if(x==y&&x+y==l) {
                    if(p.find("00")==string::npos&&q.find("00")==string::npos) f=1;
                }
            }
        } if(f) cout<<"yes\n";
        else cout<<"no\n";
    }
}
