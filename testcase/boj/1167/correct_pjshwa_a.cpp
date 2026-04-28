#include <cstdio>
#include <vector>
#include <utility>
#include <unistd.h>
#define f(x) {x=0;if(ptr==buf+sz)syscall(0,0,ptr=buf,sz);if(*ptr=='-'){ptr++;while(1){if(ptr==buf+sz)syscall(0,0,ptr=buf,sz);if(*ptr<48)break;x=x*10-*ptr+++48;}}else{while(1){if(ptr==buf+sz)syscall(0,0,ptr=buf,sz);if(*ptr<48)break;x=x*10+*ptr++-48;}}ptr++;}
#define sz (1<<16)

long m;
int n, k;
std::vector<std::pair<int, int>> g[100001];
void dfs(int s, int p, int x) {
	for(auto[e, w] : g[s])
		if(e!=p)
			dfs(e, s, x+w);
	if(m<x)
		m=x, k=s;
}
int main() {
	char buf[sz],*ptr=buf+sz;
	f(n);
	for(int i=0; i<n; i++) {
		int s, e, w; f(s);
		while(1) {
			f(e); if(e==-1) break; f(w);
			g[s].push_back({e, w});
		}
	}
	dfs(1, 1, 0);
	dfs(k, k, 0);
	printf("%ld", m);
}
