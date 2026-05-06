#include <iostream>
#include <string>
using namespace std;
int main() {
    int a,b,n;
    a=1;
    b=0;
    string s;
    cin >> n;
    for(int j=0;j<n;j++) {
        cin >> s;
        for(int i=0;i<s.size();i++) {
            if(s[i]=='O') {
                if(s[i+1]=='X') {
                   b+=a;
                   a=1;
                } else {
                    b+=a;
                    a+=1;
                }
            }
        } cout << b << endl;
        b=0;
        a=1;
    }
}
