#include <iostream>
using namespace std;
int main() {
    string s;
    int n,t;
    cin >> t;
    for(int i=0;i<t;i++) {
        cin >> s;
        n=s.size();
        cout << s[0] << s[n-1] << endl;
    }
    return 0;
}
