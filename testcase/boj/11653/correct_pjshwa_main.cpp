#include <cstdio>
#include <vector>
using namespace std;
int main(){
    long long int n;
    vector<long long int> a_vector;
    scanf("%lld", &n);
    
    for(long long int i = 2; i <= n; i++){
        while(!(n % i)){
            a_vector.push_back(i);
            n /= i;
        }
    }
    
    for(auto &x : a_vector){
        printf("%lld\n", x);
    }
}