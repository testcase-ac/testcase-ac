#include <iostream>

int main() {
  int row_count, col_count, lyr_count;
  std::cin >> row_count >> col_count >> lyr_count;

  char board[lyr_count][row_count][col_count + 1];
  for (int i = 0; i < lyr_count; ++i) {
    for (int j = 0; j < row_count; ++j) std::cin >> board[i][j];
  }

  for (int l = 0; l < lyr_count; ++l) {
    for (int r = 0; r < row_count; ++r) {
      for (int c = 0; c < col_count; ++c) {

        if (board[l][r][c] == '*') {
          std::cout << '*';
          continue;
        }

        int adj_mine_cnt = 0;
        for (int dl = -1; dl <= 1; ++dl) for (int dr = -1; dr <= 1; ++dr) for (int dc = -1; dc <= 1; ++dc) {

          if (dl == 0 && dr == 0 && dc == 0) continue;

          int nl = l + dl, nr = r + dr, nc = c + dc;
          if (nl < 0 || nl >= lyr_count) continue;
          if (nr < 0 || nr >= row_count) continue;
          if (nc < 0 || nc >= col_count) continue;

          if (board[nl][nr][nc] == '*') ++adj_mine_cnt;

        }

        std::cout << adj_mine_cnt % 10;
      }

      std::cout << '\n';
    }

  }
}
