#include <vector>
#include <functional>
#include <unistd.h>
#define SZ 196608
int main() {
	int a[1001]; std::vector<int> g[1001]; char I[SZ], O[1<<12], *c=I, *d=O; syscall(0,0,I,SZ);
	auto f=[&]{if(c>=I+SZ-10){char*p=I;while(c!=I+SZ)*p++=*c++;syscall(0,0,p,I+SZ-p);c=I;}int x=0;do{x=x*10+*c-'0';}while(*++c>='0');++c;return x;};

	int T=f();
	while(T--) {
		int n=f(), m=f();
		for(int i=1; i<=n; i++) a[i]=f(), g[i].clear();
		for(int i=1; i<=m; i++) {
			int x=f(), y=f();
			g[y].push_back(x);
		}

		std::function<int(int)> e=[&](int i) {
			int m=0;
			for(int k:g[i]) {
				int x=~(a[k]<0 ? a[k] : e(k));
				if(m<x) m=x;
			}
			return a[i]=~(a[i]+m);
		};

		int x=~e(f());
		char temp[8], *t=temp;
		do *t++=x%10|48; while(x/=10);
		do *d++=*--t; while(t!=temp);
		*d++=10;
	}
	syscall(1, 1, O, d-O);
}
