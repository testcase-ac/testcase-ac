#include <bits/stdc++.h>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1,100);
    uniform_int_distribution<int> disn(0,1000000001);
    uniform_int_distribution<int> dism(1,1001); // fixed by admin: originally (0, 1001)
    int t=dist(gen);
    cout<<t<<'\n';
    for(int i=0;i<t/2;i++) {
        t--;
        cout<<dism(gen)<<' '<<dism(gen)<<'\n';
    } while(t--) {
        cout<<disn(gen)<<' '<<disn(gen)<<'\n';
    }
}
