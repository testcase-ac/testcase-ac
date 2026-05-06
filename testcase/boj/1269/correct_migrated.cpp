#include <iostream>
#include <set>
using namespace std;
int main() {
    int a,b,c,d,e=0;
    cin >> a >> b;
    set<int> x,y;
    for(int i=0;i<a;i++) {
        cin >> c;
        x.insert(c);
    } for(int i=0;i<b;i++) {
        cin >> d;
        if(x.count(d)==1) {
            e+=2;
        }
        y.insert(d);
    } cout << x.size()+y.size()-e;
}
