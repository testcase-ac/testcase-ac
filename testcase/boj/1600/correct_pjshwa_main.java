import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
    static int k;
    static int w;
    static int h;
    static int[][] board;
    static boolean[][][] visited;
    static int[][] hmove = {{-2, -1}, {-1,-2},{-2,1}, {-1,2}, {1, 2}, {2,1}, {1, -2}, {2,-1}};
    static int [] dx = {1,-1,0,0};
    static int [] dy = {0,0,1,-1};
    public static void main(String[] args) throws Exception {
        k = input.integer();
        w = input.integer();
        h = input.integer();
        board = new int[h][w];
        visited = new boolean[h][w][k + 1];
        for(int row=0; row<h; row++){
            for(int col=0; col<w; col++){
                int number = input.integer();
                board[row][col] = number;
            }
        }
        Queue<Monkey> queue = new LinkedList<>();
        visited[0][0][0] = true;
        queue.add(new Monkey(0, 0, 0, 0));
        while(!queue.isEmpty()){
            Monkey monkey = queue.poll();
            int x = monkey.x;
            int y = monkey.y;
            if(x==h - 1 && y==w - 1){
                System.out.println(monkey.cnt);
                System.exit(0);
            }
            for(int i=0; i<4; i++){
                int next_x = x +dx[i];
                int next_y = y +dy[i];
                if(moveable(next_x, next_y) && !visited[next_x][next_y][monkey.k]){
                    visited[next_x][next_y][monkey.k] = true;
                    queue.add(new Monkey(next_x, next_y, monkey.k, monkey.cnt + 1));
                }
            }
            if (monkey.k < k) {
                for (int i = 0; i < hmove.length; i++) {
                    int next_x = x + hmove[i][0];
                    int next_y = y + hmove[i][1];
                    if (moveable(next_x, next_y) && !visited[next_x][next_y][monkey.k + 1]) {
                        visited[next_x][next_y][monkey.k + 1] = true;
                        queue.add(new Monkey(next_x, next_y, monkey.k + 1, monkey.cnt + 1));
                    }
                }
            }
        }
        System.out.println(-1);
    }
    static boolean moveable(int x, int y){
        return x>=0 && x< h && y>=0 && y<w && board[x][y] != 1;
    }
    static Input input = new Input();
    static class Input {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer("");
        public int integer() throws Exception{
            if(!st.hasMoreElements()) st = new StringTokenizer(br.readLine());
            return Integer.parseInt(st.nextToken());
        }
    }
    static class Monkey{
        int x;
        int y;
        int k;
        int cnt;
        public Monkey(int x, int y, int k, int cnt) {
            this.x = x;
            this.y = y;
            this.k = k;
            this.cnt = cnt;
        }
    }
}
