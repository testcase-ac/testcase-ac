#include <cstdio>
// #include <vector>
   
int main(){
    int n;
    scanf("%d", &n);

    int a[n], primes=0;
    
    for(auto &x : a){
        scanf("%d", &x);
        
        if(x == 1) continue;
        if(x == 2){
            primes++;
            continue;
        }
        if(!(x % 2)) continue;
        bool prime = true;
        for(int i = 3; i <= x / 2; i+=2){
            if(!(x % i)){
                prime = !prime;
                break;
            }
        }
        if(prime) primes++;
    }
        
    printf("%d", primes);
}