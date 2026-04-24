#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
char s[1024];
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
    while(1) {
        cin.getline(s, 1000);
        if(!strcmp(s, "END")) return 0;
        int l = strlen(s);
        reverse(s, s+l);
        cout << s << '\n';
    }
}
