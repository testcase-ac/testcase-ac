#include <cstdio>

int how_many_ones(int integer){
    int answer = 0;
    while(integer != 0){
        answer += (integer % 2);
        integer /= 2;
    }
    return answer;
}

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    int how_many_bottles = how_many_ones(n);
    if(k >= how_many_bottles){
    	printf("0");
    	return 0;
    }
    else{
    	n++;
    	int new_bottles = 1;
    	while(how_many_ones(n) > k){
    		n++;
    		new_bottles++;
    	}
    	printf("%d", new_bottles);
    }
    return 0;
}