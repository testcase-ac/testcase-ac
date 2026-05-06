#include <bits/stdc++.h>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dis(1,1000000000000000000);
    cout<<dis(gen)<<' '<<dis(gen);
}
