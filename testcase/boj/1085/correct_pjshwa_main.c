#include <stdio.h>


int min(int x, int y){
	return (x<y?x:y);
}

int main(void){
    int a[4];

    for(int i = 0; i < 4; i++){
        scanf("%d", &a[i]);
    }
    
    printf("%d", min(min(a[2]-a[0],a[3]-a[1]),min(a[0],a[1])));
    
    return 0;
}