#include <bits/stdc++.h>
using namespace std;
int main() {
    string a,b;
    int k=0;
    cin>>a>>b;
    if(a.length()!=b.length()) {
        cout<<0;
        return 0;
    } else {
        for(int i=0;i<a.length();i++) {
            if(a[i]=='8'&&b[i]=='8') {
                k++;
            } else if(a[i]!=b[i]) {
                break;
            }
        }
    } cout<<k;
}
