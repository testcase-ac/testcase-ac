#include <cstdio>
int main(void){
    int n;
    scanf("%d", &n);
    
    auto a = 3, b = 7;
    auto c = b;

    while(n > 2){
    	c = (a + 2 * b) % 9901;
    	a = b;
    	b = c;
    	n--;
    }

    int k;

    (n==1)?k=a:(n==2)?k=b:k=c;
    printf("%d", k);
    
    return 0;
}