import java.io.*;
import java.util.*;

public class Main {

    static class Tree implements Comparable<Tree> {
        int x, y, len;
        Tree(int x, int y, int len) {
            this.x = x;
            this.y = y;
            this.len = len;
        }

        @Override
        public int compareTo(Tree o) {
            return this.len-o.len;
        }
    }

    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer st;

    static int N;
    static Tree[] arr;
    static int[] xarr, yarr, yidx;
    static int lenSum = 0;

    public static void main(String[] args) throws Exception {
        N = Integer.parseInt(br.readLine());
        arr = new Tree[N];
        for(int i=0;i<N;i++) {
            st = new StringTokenizer(br.readLine());
            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());
            int len = Integer.parseInt(st.nextToken());
            arr[i] = new Tree(x, y, len);
            lenSum += len;
        }

        Arrays.sort(arr);
        xarr = new int[N];
        yarr = new int[N];
        yidx = new int[1000001];
        for(int i=0;i<N;i++) {
            int x = arr[i].x, y = arr[i].y;
            xarr[i] = x;
            yarr[i] = y;
            yidx[y] = i;
        }

        Arrays.sort(xarr);
        Arrays.sort(yarr);

        int answer = N;
        for(int lx=0;lx<N;lx++) for(int rx=lx;rx<N;rx++) for(int ly=0;ly<N;ly++) {
            int cnt = N, len = lenSum;
            PriorityQueue<Integer> pq = new PriorityQueue<>((a,b) -> b-a);
            PriorityQueue<Integer> pq2 = new PriorityQueue<>((a,b) -> a-b);
            for(int ry=ly;ry<N;ry++) {
                int idx = yidx[yarr[ry]];
                if(xarr[lx] > arr[idx].x || xarr[rx] < arr[idx].x) continue;
                cnt--;
                len -= arr[idx].len;
                pq.add(arr[idx].len);
                int need = 2*(xarr[rx] - xarr[lx] + yarr[ry] - yarr[ly]);
                while(len < need && !pq.isEmpty()) {
                    len += pq.poll();
                    cnt++;
                }
                while(!pq2.isEmpty() && len - pq2.peek() >= need) {
                    cnt--;
                    pq.add(pq2.poll());
                }
                answer = Math.min(answer, cnt);
            }
        }
        bw.write(answer + "\n");
        
        bw.close();
    }
}
