#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int t,r;
    string s;
    vector<string> w;
    cin >> t;
    for(int i=0;i<t;i++) {
        cin >> r >> s;
        for(int j=0;j<s.size();j++) {
            w.push_back(string(r,s[j]));
        }
        for(int i=0;i<s.size();i++) {
            cout << w[i];
        }
        cout << endl;
        w.clear();
    }
}
