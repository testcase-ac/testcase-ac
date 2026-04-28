import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main { // sliding window
    static int n,d,k,c;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n=Integer.parseInt(st.nextToken());
        d=Integer.parseInt(st.nextToken());
        k=Integer.parseInt(st.nextToken());
        c=Integer.parseInt(st.nextToken());
        int[] arr = new int[n];
        int[] eated = new int[d+1];
        // 접시에 담김.
        for(int i=0; i<n; i++) arr[i]=Integer.parseInt(br.readLine());
        // 처음 0번에서 k개만큼 먹었을 때

        int count=1; eated[c]++;
        for(int i=0; i<k; i++) {
            // 한번도 먹지 않았은 종류라면
            if(eated[arr[i]] == 0) count++;
            eated[arr[i]]++;
        }
        // 현재 0번에서 k개만큼 먹었을때의 초밥의 종류 수
        int mx = count;

        // 1번부터 n-1번까지 start만 이동시키면 k는 고정이기 때문에 end를 활용할 필요 없음
        for(int i=1;i<n;i++) {
            // end 이동
            // (i + (k - 1)) % n
            int end = (i + (k - 1)) % n;
            if(eated[arr[end]]==0) {
                count++;
            }
            eated[arr[end]]++;

            // start 이동
            eated[arr[i-1]]--; // 이전의 초밥 제거
            if(eated[arr[i-1]]==0) {
                count--;
            }
            mx = Math.max(mx, count);
        }
        System.out.println(mx);
    }
}
