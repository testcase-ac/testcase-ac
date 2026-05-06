#include <iostream>
#include <string>
using namespace std;

int main() {
    int a;
    string s;
    cin >> a;
    for(int i=1;i<=1000000;i++) {
        s=to_string(i);
        for(int j=s.size()+1;j<7;j++) {
            s[j]='0';
        }
        if(s[0]+s[1]+s[2]+s[3]+s[4]+s[5]+s[6]-'0'-'0'-'0'-'0'-'0'-'0'+i==a) {
            cout << i;
            return 0;
        }
    } cout << "0";
}
