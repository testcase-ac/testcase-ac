#include <cstdio>
#define N 1000001
int a[N], n, m;
char s[N], r[N], p[37];
int main() {
	scanf("%s%s", s, p);
	for(int i=0; s[i]; i++) {
		r[n++]=s[i];
		if(s[i]==p[0]) a[++m]=0;
		if(s[i]==p[a[m]]) { if(!p[++a[m]]) n-=a[m--]; }
		else m=0;
	}
	r[n]=0;
	puts(n ? r : "FRULA");
}
