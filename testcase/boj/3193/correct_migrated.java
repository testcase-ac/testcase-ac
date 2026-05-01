import java.io.*;
import java.util.*;

public class Main {
    static int n;
    static int k;
    static int[] dx = {1, 0, -1, 0};
    static int[] dy = {0, -1, 0, 1};
    static int gravity = 0;
    static char[][] map;
    static Pos ball;

    static class Pos {
        int x;
        int y;

        Pos(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    static void drop() {
        while (true) {
            int nx = ball.x + dx[gravity];
            int ny = ball.y + dy[gravity];

            if (nx < 0 || nx >= n || ny < 0 || ny >= n) break;
            if (map[nx][ny] == 'X') break;

            map[ball.x][ball.y] = '.';
            map[nx][ny] = 'L';

            ball.x = nx;
            ball.y = ny;
        }
    }

    static void print() {
        StringBuilder sb = new StringBuilder();
        if (gravity == 0) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    sb.append(map[i][j]);
                }
                sb.append("\n");
            }
        } else if (gravity == 1) {
            for (int i = n - 1; i >= 0; i--) {
                for (int j = 0; j < n; j++) {
                    sb.append(map[j][i]);
                }
                sb.append("\n");
            }
        } else if (gravity == 2) {
            for (int i = n - 1; i >= 0; i--) {
                for (int j = n - 1; j >= 0; j--) {
                    sb.append(map[i][j]);
                }
                sb.append("\n");
            }
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = n - 1; j >= 0; j--) {
                    sb.append(map[j][i]);
                }
                sb.append("\n");
            }
        }
        System.out.println(sb);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        n = Integer.parseInt(st.nextToken());
        k = Integer.parseInt(st.nextToken());
        map = new char[n][n];

        for (int i = 0; i < n; i++) {
            String line = br.readLine();
            for (int j = 0; j < n; j++) {
                map[i][j] = line.charAt(j);
                if (map[i][j] == 'L') ball = new Pos(i, j);
            }
        }

        for (int i = 0; i < k; i++) {
            String dir = br.readLine();

            if (dir.equals("L")) gravity = (gravity + 1) % 4;
            else gravity = (gravity + 3) % 4;

            drop();
        }

        print();
    }
}
