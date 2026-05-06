#include <bits/stdc++.h>
using namespace std;
const double PI=acos(-1);
struct pt {
	double x,y,z;
	pt():x(0),y(0),z(0){}
	pt(double x,double y,double z):x(x),y(y),z(z){}
	pt operator+(const pt&p)const{return pt(x+p.x,y+p.y,z+p.z);}
	pt operator-(const pt&p)const{return pt(x-p.x,y-p.y,z-p.z);}
	pt operator*(const double&v)const{return pt(x*v,y*v,z*v);}
	bool operator==(const pt&p)const{return x==p.x&&y==p.y&&z==p.z;}
	pt cross(const pt&p)const{return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
	double dot(const pt&p)const{return x*p.x+y*p.y+z*p.z;}
};
struct face {
	int a,b,c;
	pt q;
	bool operator==(const face&f)const{return a==f.a&&b==f.b&&c==f.c&&q==f.q;}
};
const double eps=1e-9;
vector<face> hull(const vector<pt> &p) {
	int n=p.size();
	vector<face> f;
	vector<vector<bool>> dead(n,vector<bool>(n,1));
	auto add=[&](int a,int b,int c){
		f.push_back({a,b,c,(p[b]-p[a]).cross(p[c]-p[a])});
		dead[a][b]=dead[b][c]=dead[c][a]=0;
	};int a=-1,b=-1,c=-1;
	for(int i=0;i<n;i++) {
		for(int j=i+1;j<n;j++) {
			for(int k=j+1;k<n;k++) {
				pt u=p[j]-p[i],v=p[k]-p[i];
				pt n=u.cross(v);
				if(n.x*n.x+n.y*n.y+n.z*n.z>eps) {
					a=i;b=j;c=k;
					goto found;
				}
			}
		}
	} found:
	if(a==-1) return f;
	add(a,b,c);
	add(a,c,b);
	for(int i=3;i<n;i++) {
		vector<face> f2;
		for(auto &F:f){
			if((p[i]-p[F.a]).dot(F.q)>eps) dead[F.a][F.b]=dead[F.b][F.c]=dead[F.c][F.a]=1;
			else f2.push_back(F);
		} f.clear();
		for(auto &F:f2) {
			int a[3]={F.a,F.b,F.c};
			for(int j=0;j<3;j++){
				int u=a[j],v=a[(j+1)%3];
				if(dead[v][u]) add(v,u,i);
			}
		} f.insert(f.end(),f2.begin(),f2.end());
	} return f;
}
double dst(const pt&a,const pt&b) {return hypot(a.x-b.x,a.y-b.y,a.z-b.z);}
void sphere2(const pt&a,const pt&b,pt&c,double&r) {
	c=(a+b)*0.5;
	r=dst(a,c);
}
bool sphere3(const pt&a,const pt&b,const pt&c,pt&o,double&r) {
	pt ab=b-a,ac=c-a;
	pt u=ab.cross(ac);
	double det=u.dot(u);
	if(det<eps) return 0;
	double ab2=ab.dot(ab),ac2=ac.dot(ac);
	pt t=(u.cross(ab)*ac2+ac.cross(u)*ab2)*(0.5/det);
	o=a+t;
	r=dst(a,o);
	return 1;
}
bool sphere4(const pt&a,const pt&b,const pt&c,const pt&d,pt&o,double&r) {
	pt ba=b-a,ca=c-a,da=d-a;
	pt n1=ca.cross(da),n2=da.cross(ba),n3=ba.cross(ca);
	double det=ba.dot(n1);
	if(abs(det)<eps) return 0;
	o=a+(n1*ba.dot(ba)+n2*ca.dot(ca)+n3*da.dot(da))*(0.5/det);
	r=dst(a,o);
	return 1;
}
double mec3(vector<pt> p) {
	random_shuffle(p.begin(),p.end());
	pt c;
	double r=-1;
	for(int i=0;i<p.size();i++) {
		if(r>=0&&dst(p[i],c)<=r+eps) continue;
		c=p[i];r=0;
		for(int j=0;j<i;j++) {
			if(dst(p[j],c)<=r+eps) continue;
			sphere2(p[i],p[j],c,r);
			for(int k=0;k<j;k++) {
				if(dst(p[k],c)<=r+eps) continue;
				if(!sphere3(p[i],p[j],p[k],c,r)) continue;
				for(int l=0;l<k;l++) {
					if(dst(p[l],c)<=r+eps) continue;
					sphere4(p[i],p[j],p[k],p[l],c,r);
				}
			}
		}
	} return r;
}
int main() {
	int n;
	cin>>n;
	vector<pt> v;
	for(int i=0;i<n;i++) {
		double x,y,z;
		cin>>x>>y>>z;
		pt c(x,y,z);
		v.push_back(c);
	} n=v.size();
	auto ch=hull(v);
	double ans=1e18;
	for(auto f:ch) {
		pt a=v[f.a],b=v[f.b],c=v[f.c],t=(a-b).cross(b-c);
		double r=hypot(t.x,t.y,t.z);
		t=t*(1.0/r);
		vector<pt> p;
		double h=0;
		for(auto u:v) {
			double d=t.dot(u-a);
			u=u-t*d;
			h=max(h,abs(d));
			p.push_back(u);
		} double R=mec3(p);
		ans=min(ans,R*R*h*PI);
	} cout<<fixed<<setprecision(12)<<ans;
}
