#include <cstdio>

int find_max(float *a, int size){
	float max_value = 0.0f;
	int max_index;
	for(int i = 0; i < size; i++){
		if(a[i] / (i+1) > max_value){
			max_value = a[i] / (i+1);
			max_index = i;
		}
	}
	return max_index;
}

int main(){
    
    int n;
    scanf("%d", &n);
    
    float fishcakes[n];
    
    for(int i = 0; i < n; i++){
        scanf("%f", &fishcakes[i]);
    }
    int max_profit = 0;
    while(n > 0){
    	int index = find_max(fishcakes, n);
    	n -= (index+1);
    	max_profit += fishcakes[index];
    }

    printf("%d", max_profit);
    
    return 0;
}