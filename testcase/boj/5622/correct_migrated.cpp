#include <iostream>
using namespace std;

int main() {
    string s;
    cin >> s;
    int a=0;
    for(int i=0;i<s.size();i++) {
        if(s[i]=='Z') {
            a=a+10;
        } else if(static_cast<int>(s[i])>82) {
            a=a+3+(static_cast<int>(s[i])-66)/3;
        } else {
            a=a+3+(static_cast<int>(s[i])-65)/3;
        }
    } cout << a;
}
