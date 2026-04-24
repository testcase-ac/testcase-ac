#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

bool ok(int l1, int l2, int r, int op) {
	switch(op) {
		case '+':
		return l1+l2==r;
		case '-':
		return l1-l2==r;
		case '/':
		return l1%l2==0 && l1/l2==r;
		case '*':
		return l1*l2==r;
	}
	return false;
}
char ops[] = {'+', '-', '/', '*'};
int main() {
	int a, b, c;
	cin >> a >> b >> c;
	for(char o: ops) {
		if(ok(a,b,c,o)) printf("%d%c%d=%d",a,o,b,c), exit(0);
		if(ok(b,c,a,o)) printf("%d=%d%c%d",a,b,o,c), exit(0);
	}
}
