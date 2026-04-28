#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

int main(void){
    long long int a, b;
    
    scanf("%lld %lld", &a, &b);
    vector<long long int> prime_v;
    prime_v.push_back(2LL);
    long long sqrt_max = (long long)sqrt(b);
    long long specimen = 3LL;
    while(specimen <= sqrt_max){
        bool prime = true;
        for(auto &x : prime_v){
            if(!specimen%x){
            	prime = false;
            	break;
            }
        }
        if(prime) prime_v.push_back(specimen);
        specimen++;
    }
    
    long long ans = b-a+1LL;
    for(auto &x : prime_v){
    	long long square = x*x;
    	ans -= (b / square - (a-1LL) / square);
    }

    printf("%lld", ans);

    return 0;
}