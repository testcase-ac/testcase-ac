#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;

    int ans = 0;
    int a = 0, b = 0, c = 0;
    for (char h : s) {
        if (h == 'A') a++;
        if (h == 'B' && a) {
            a--;
            ans++;
        }
    }
    reverse(s.begin(), s.end());
    for (char h : s) {
        if (h == 'C') c++;
        if (h == 'B' && c) {
            c--;
            ans++;
        }
    }

    for (char h : s) if (h == 'B') b++;
    cout << min(ans, b);
    
    return 0;
}