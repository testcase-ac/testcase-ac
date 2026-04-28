#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    char s[31];
    for(int i = 0; i < n; i++){
        scanf(" %[^\n]",s); // doesn't automatically skip whitespace when defined as scansets
        if(s[0] >= 97) s[0] -= 32;
        printf("%s\n", s);
    }
}