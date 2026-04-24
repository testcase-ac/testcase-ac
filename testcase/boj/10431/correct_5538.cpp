#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for(int i=0; i<T; i++) {
        int t;
        cin >> t;
        assert(t == i+1);
        vector<int> v(20);
        for(int i=0; i<20; i++) {
            cin >> v[i];
        }
        int ans = 0;
        for(int i=0; i<20; i++) {
            for(int j=0; j<i; j++) {
                if(v[j] > v[i]) ans++;
            }
        }
        cout << t << ' ' << ans << '\n';
    }
    return 0;
}