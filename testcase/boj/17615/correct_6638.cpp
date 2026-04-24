#include <iostream>
#include <string>
using namespace std;

int main() {
    int N;
    string s;
    cin >> N >> s;
    int b = 0, r = 0;
    for(char c: s) {
        if(c == 'B') {
            b++;
        } else {
            r++;
        }
    }
    if(!b || !r) {
        return !(cout << 0);
    }
    int ans = min(b, r);
    for(int i=0; i<N; i++) {
        if(s[i] != s[0]) {
            if(s[0] == 'B') {
                ans = min(ans, b - i);
            } else {
                ans = min(ans, r - i);
            }
            break;
        }
    }
    for(int i=N-1; i>=0; i--) {
        if(s[i] != s[N-1]) {
            if(s[N-1] == 'B') {
                ans = min(ans, b - (N - 1 - i));
            } else {
                ans = min(ans, r - (N - 1 - i));
            }
            break;
        }
    }
    cout << ans;
}
