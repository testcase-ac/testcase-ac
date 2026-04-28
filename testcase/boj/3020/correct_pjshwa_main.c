#include <stdio.h>

int main(){
    int n,h;scanf("%d%d", &n,&h);
    int obs[h], down_obs[h];
    for(int i = 0; i < h; i++){
        obs[i]=0;down_obs[i]=0;}
    for(int i = 0; i < n; i++){
        int k;
            scanf("%d", &k);
        if(i%2==0)//석순
        {
            
            obs[k-1]++;
        }
        else{
            down_obs[k-1]++;
        }
    }
    for(int i = h-1; i > 0; i--){
        obs[i-1] += obs[i];
        down_obs[i-1] += down_obs[i];
    }
    for(int i = 0; i < h; i++){
        obs[i] += down_obs[h-1-i];
    }
    int min=n;
    for(int i=0;i<h;i++){
        if(min>obs[i]) min=obs[i];
    }
    int min_part=0;
    for(int i=0;i<h;i++){
        if(min==obs[i]) min_part++;
    }
    printf("%d %d",min,min_part);
}