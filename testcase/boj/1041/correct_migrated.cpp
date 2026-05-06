#include <bits/stdc++.h>
using namespace std;
int main() {
	long long x,a,b,c,d,e,f,y,z,w,o;
	vector<long long> s,t,u;
	cin>>x>>a>>b>>c>>d>>e>>f;
	s={a,b,c,d,e,f};
	sort(s.begin(),s.end());
	y=s[0];
	o=s[5];
	u={a+b,a+c,a+d,a+e,b+c,b+d,b+f,c+e,c+f,d+e,d+f,e+f};
	sort(u.begin(),u.end());
	z=u[0];
	t={a+b+c,a+b+d,a+c+e,b+c+f,b+d+f,c+e+f,d+e+f,a+d+e};
	sort(t.begin(),t.end());
	w=t[0];
	if(x==1) cout<<a+b+c+d+e+f-o;
	else cout<<4*w+(8*x-12)*z+4*(x-2)*y+5*(x-2)*(x-2)*y;
}
