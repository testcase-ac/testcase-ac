#include <bits/stdc++.h>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1,100);
    uniform_int_distribution<int> disn(1,100001);
    int t=dist(gen);
    cout<<t<<'\n';
    while(t--) {
        cout<<disn(gen)<<'\n';
    }
}
