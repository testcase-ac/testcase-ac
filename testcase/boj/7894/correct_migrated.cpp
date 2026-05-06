#include <bits/stdc++.h>
#define ll long long
#define pii pair<ll,ll>

using namespace std;

vector<double> lg(10001000);

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    for(int i = 1; i <= 10000000; i++) lg[i] = log10(i) + lg[i - 1];
    while(n--){
        int x; cin >> x;
        cout << int(lg[x]) + 1 << "\n";
    }
    return 0;
}
