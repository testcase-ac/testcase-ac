use io::Write;
use std::{io, str};

pub struct UnsafeScanner<R> {
  reader: R,
  buf_str: Vec<u8>,
  buf_iter: str::SplitAsciiWhitespace<'static>,
}

impl<R: io::BufRead> UnsafeScanner<R> {
  pub fn new(reader: R) -> Self {
    Self {
      reader,
      buf_str: vec![],
      buf_iter: "".split_ascii_whitespace(),
    }
  }
  
  pub fn token<T: str::FromStr>(&mut self) -> T {
    loop {
      if let Some(token) = self.buf_iter.next() {
        return token.parse().ok().expect("Failed parse");
      }
      self.buf_str.clear();
      self.reader
          .read_until(b'\n', &mut self.buf_str)
          .expect("Failed read");
      self.buf_iter = unsafe {
        let slice = str::from_utf8_unchecked(&self.buf_str);
        std::mem::transmute(slice.split_ascii_whitespace())
      }
    }
  }
}

const DX: [usize; 2] = [0, 1];
const DY: [usize; 2] = [1, 0];

fn rec(
  i: usize, j: usize, k: usize, t: i32,
  dp: &mut Vec<Vec<i32>>, indegree: &mut Vec<Vec<i32>>, board: &Vec<Vec<char>>
) {
  if t == 1 {
    for l in 0..2 {
      if i < DX[l] || j < DY[l] { continue; }

      let (ni, nj) = (i - DX[l], j - DY[l]);
      if board[ni][nj] == '#' { continue; }
      if dp[ni][nj] != -1 { continue; }

      dp[ni][nj] = 0;
      rec(ni, nj, k, 0, dp, indegree, board);
    }

    for l in 1..=k {
      if i < l || j < l { continue; }

      let (ni, nj) = (i - l, j - l);
      if board[ni][nj] == '#' { continue; }
      if dp[ni][nj] != -1 { continue; }

      dp[ni][nj] = 0;
      rec(ni, nj, k, 0, dp, indegree, board);
    }
  }
  else {
    for l in 0..2 {
      if i < DX[l] || j < DY[l] { continue; }

      let (ni, nj) = (i - DX[l], j - DY[l]);
      if board[ni][nj] == '#' { continue; }
      if dp[ni][nj] != -1 { continue; }

      indegree[ni][nj] -= 1;
      if indegree[ni][nj] == 0 {
        dp[ni][nj] = 1;
        rec(ni, nj, k, 1, dp, indegree, board);
      }
    }

    for l in 1..=k {
      if i < l || j < l { continue; }

      let (ni, nj) = (i - l, j - l);
      if board[ni][nj] == '#' { continue; }
      if dp[ni][nj] != -1 { continue; }

      indegree[ni][nj] -= 1;
      if indegree[ni][nj] == 0 {
        dp[ni][nj] = 1;
        rec(ni, nj, k, 1, dp, indegree, board);
      }
    }
  }
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let (n, m, k) = (scan.token::<usize>(), scan.token::<usize>(), scan.token::<usize>());

  let mut board = vec![];
  for _ in 0..n {
    let line = scan.token::<String>().chars().collect::<Vec<char>>();
    board.push(line);
  }

  let mut indegree = vec![vec![0; m]; n];
  for i in 0..n { for j in 0..m {
    for l in 0..2 {
      let (ni, nj) = (i + DX[l], j + DY[l]);
      if ni >= n || nj >= m { continue; }
      if board[ni][nj] == '#' { continue; }
      indegree[i][j] += 1;
    }
    for l in 1..=k {
      let (ni, nj) = (i + l, j + l);
      if ni >= n || nj >= m { continue; }
      if board[ni][nj] == '#' { continue; }
      indegree[i][j] += 1;
    }
  }}

  let mut dp = vec![vec![-1; m]; n];

  dp[n - 1][m - 1] = 1;
  rec(n - 1, m - 1, k, 1, &mut dp, &mut indegree, &board);

  let q = scan.token::<usize>();
  for _ in 0..q {
    let (x, y) = (scan.token::<usize>(), scan.token::<usize>());

    if dp[x - 1][y - 1] == 0 { writeln!(out, "First").ok(); }
    else { writeln!(out, "Second").ok(); }
  }
}

fn main() {
  let (stdin, stdout) = (io::stdin(), io::stdout());
  let mut scan = UnsafeScanner::new(stdin.lock());
  let mut out = io::BufWriter::new(stdout.lock());

  let t = 1;
  // let t = scan.token::<usize>();
  for _ in 0..t {
    solve(&mut scan, &mut out);
  }
}
