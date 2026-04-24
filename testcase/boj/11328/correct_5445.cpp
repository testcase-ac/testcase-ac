#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    cin >> N;
    while(N--) {
        string a, b;
        cin >> a >> b;
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        if(a == b) cout << "Possible\n";
        else cout << "Impossible\n";
    }
}
