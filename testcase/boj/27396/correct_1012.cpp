#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    int n;
    cin >> s >> n;
    
    char map[256];
    for (int i = 0; i < 256; ++i) {
        map[i] = static_cast<char>(i);
    }
    
    while (n--) {
        int type;
        cin >> type;
        if (type == 1) {
            char i1, i2;
            cin >> i1 >> i2;
            for (int c = 0; c < 256; ++c) {
                if (map[c] == i1) {
                    map[c] = i2;
                }
            }
        } else {
            string res;
            res.reserve(s.size());
            for (unsigned char c : s) {
                res += map[c];
            }
            cout << res << '\n';
        }
    }
    
    return 0;
}
