#include <cstdio>
int main(void){
    int n;
    scanf("%d", &n);
    
    auto a = 1, b = 2;
    auto c = b;

    while(n > 2){
    	c = a % 10007 + b % 10007;
    	c %= 10007;
    	a = b;
    	b = c;
    	n--;
    }

    int k;

    (n==1)?k=a:(n==2)?k=b:k=c;
    printf("%d", k);
    
    return 0;
}