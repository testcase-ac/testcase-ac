#include <cstdio>
  
int main(){
    int n;
    scanf("%d", &n);
      
    for(int i = 0; i < n; i++){
        int p;
        scanf("%d", &p);
        char s[21];
        scanf("%s", s);
        for(int i = 0; s[i] != 0; i++){
            for(int j = 0; j < p; j++){
                printf("%c", s[i]);
            }
        }
        printf("\n");
    }
}