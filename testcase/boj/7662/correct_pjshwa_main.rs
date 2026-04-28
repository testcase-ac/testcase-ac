fn main() {
  let stdin = std::io::stdin();
  let mut buf = String::new();

  stdin.read_line(&mut buf).unwrap();
  let mut iter = buf.split_whitespace();
  let row = iter.next().unwrap().parse::<usize>().unwrap();
  let col = iter.next().unwrap().parse::<usize>().unwrap();
  buf.clear();

  let mut map = Vec::with_capacity(row);
  let mut count = Vec::with_capacity(row);
  for _i in 0 .. row {
      stdin.read_line(&mut buf).unwrap();
      let mut iter = buf.split_whitespace();
      let mut map_row = Vec::with_capacity(col);
      let mut count_row = Vec::with_capacity(col);
      for _j in 0 .. col {
          map_row.push(iter.next().unwrap().parse::<usize>().unwrap());
          count_row.push(-1);
      }
      buf.clear();
      map.push(map_row);
      count.push(count_row);
  }
  count[row - 1][col - 1] = 1;
  DFS(&map, &mut count, 0, 0);
  println!("{}", count[0][0]);
}

fn DFS(m: &Vec<Vec<usize>>, c: &mut Vec<Vec<i32>>, row: usize, col: usize) -> i32 {
  if c[row][col] >= 0 {
      return c[row][col];
  }
  c[row][col] = 0;
  if row > 0 && m[row - 1][col] < m[row][col] {
      // go up
      c[row][col] += DFS(m, c, row - 1, col);
  }
  if row + 1 < m.len() && m[row + 1][col] < m[row][col] {
      // go down
      c[row][col] += DFS(m, c, row + 1, col);
  }
  if col + 1 < m[0].len() && m[row][col + 1] < m[row][col] {
      // go right
      c[row][col] += DFS(m, c, row, col + 1);
  }
  if col > 0 && m[row][col - 1] < m[row][col] {
      // go left
      c[row][col] += DFS(m, c, row, col - 1);
  }
  return c[row][col];
}
