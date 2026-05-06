#include <iostream>
#include <set>
using namespace std;
int main() {
    string s;
    cin >> s;
    set<string> c;
    for (int i = 0; i < s.length(); ++i) {
        for (int j = i + 1; j <= s.length(); ++j) {
            c.insert(s.substr(i, j - i));
        }
    } cout << c.size();
}
