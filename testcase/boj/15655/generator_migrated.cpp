#include <iostream>
#include <algorithm>
#include <random>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distn(1,8);
    int n=distn(gen);
    uniform_int_distribution<int> distm(1,n);
    cout<<n<<' '<<distm(gen)<<'\n';
    uniform_int_distribution<int> dist(1,10000);
    vector<int> v;
    while(n--) {
        while(1) {
            int k=dist(gen);
            if(find(v.begin(),v.end(),k)==v.end()) {
                v.push_back(k);
                break;
            }
        }
    } for(int i=0;i<v.size()-1;i++) cout<<v[i]<<' ';
    cout<<v[n-1];
}
