#include <bits/stdc++.h>
using namespace std;
const int m[3][3][4]={
	{{0,14,20,4},{13,23,7,3},{19,18,17,16}},
	{{7,19,15,11},{18,14,10,6},{23,22,21,20}},
	{{0,9,22,19},{1,10,23,16},{15,14,13,12}}
};
const int mp[24]={
	0,1,3,2,4,5,8,9,12,13,16,17,
	7,6,11,10,15,14,19,18,20,21,23,22
};
const int f[7][3]={
	{1,9,12},{0,13,16},{3,17,4},{21,11,6},
	{22,15,10},{23,19,14},{20,7,18}
};
struct C {
	array<char,24> s;
	C()=default;
	C(const string&r){
		static const string c="GROBYW";
		for(int i=0;i<(int)r.size();i++) s[mp[i]]=(char)(c.find(r[i]));
	} C(const C&o):s(o.s){}
	C(const array<char,6>&f){
		for(int i=0;i<6;i++) s[4*i]=s[4*i+1]=s[4*i+2]=s[4*i+3]=f[i];
	} void rot(int a,int b,int c,int d) {
		char t=s[a];
		s[a]=s[b];s[b]=s[c];s[c]=s[d];s[d]=t;
	} void move(int mm) {
		auto&p=m[mm%3];
		if(mm<3) for(int i=0;i<3;i++) rot(p[i][0],p[i][1],p[i][2],p[i][3]);
		else for(int i=0;i<3;i++) rot(p[i][3],p[i][2],p[i][1],p[i][0]);
	} char find(char a,char b)const {
		for(int i=0;i<7;i++) {
			bool aa=(s[f[i][0]]==a||s[f[i][1]]==a||s[f[i][2]]==a);
			bool bb=(s[f[i][0]]==b||s[f[i][1]]==b||s[f[i][2]]==b);
			if(aa&&bb) for(int j=0;j<3;j++) if(s[f[i][j]]!=a&&s[f[i][j]]!=b) return s[f[i][j]];
		} return 255;
	} bool operator<(const C&o)const{return s<o.s;}
	bool operator==(const C&o)const{return s==o.s;}
};
struct R {
	bool nxt(const vector<C>&o,vector<C>&n,set<C>&seen,const set<C>&target){
		for(auto&p:o){
			for(int i=0;i<6;i++) {
				C c=p;
				c.move(i);
				if(target.count(c)) return 1;
				if(!seen.count(c)) {
					n.push_back(c);
					seen.insert(c);
				}
			}
		} return 0;
	} void asdf(vector<C>&l,const C&c) {
		array<char,6>f{};
		f[0]=c.s[2];
		f[1]=c.s[5];
		f[2]=c.s[8];
		f[3]=c.find(c.s[2],c.s[8]);
		f[4]=c.find(c.s[5],c.s[2]);
		f[5]=c.find(c.s[8],c.s[5]);
		l.push_back(C(f));
	} int solve(const C&c) {
		vector<C> s1,s2,e1,e2;
		set<C> st,en;
		s2.push_back(c);
		st.insert(c);
		asdf(e2,c);
		for(auto&x:e2) en.insert(x);
		if(en.count(c)) return 0;
		int g=0;
		while(1) {
			g++;
			s1=move(s2);
			s2.clear();
			if(nxt(s1,s2,st,en)) return g;
			g++;
			e1=move(e2);
			e2.clear();
			if(nxt(e1,e2,en,st)) return g;
		}
	} void run() {
		string r;
		for(int i=0;i<12;i++) {string t;cin>>t;r+=t;}
		cout<<solve(C(r))<<'\n';
	}
};
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	R r;
	while(t--) r.run();
}
