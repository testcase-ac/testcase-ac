use io::Write;
use std::{io, str, collections::VecDeque};

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

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let (n, m) = (scan.token::<usize>(), scan.token::<usize>());
  let a = (0..n).map(|_| (0..m).map(|_| scan.token::<i32>()).collect::<Vec<_>>()).collect::<Vec<_>>();
  let dx = [0, 1, 0, -1]; let dy = [1, 0, -1, 0];
  let jx = [0, 2, 0, -2]; let jy = [2, 0, -2, 0];

  let mut left = 0; let mut right = 1_000_000_001;
  while left < right {
    let mid = (left + right) / 2;

    let mut q = VecDeque::new();
    let mut vis = vec![vec![vec![false; 2]; m as usize]; n as usize];

    if a[0][0] <= mid {
      q.push_back((0, 0, 0));
      vis[0][0][0] = true;
    }

    while !q.is_empty() {
      let (i, j, u) = q.pop_front().unwrap();

      for k in 0..4 {
        let (ni, nj) = (i as i32 + dx[k], j as i32 + dy[k]);
        if ni < 0 || nj < 0 || ni >= n as i32 || nj >= m as i32 { continue; }

        let (ni, nj) = (ni as usize, nj as usize);
        if !vis[ni][nj][u] && a[ni][nj] <= mid {
          q.push_back((ni, nj, u));
          vis[ni][nj][u] = true;
        }
      }

      for k in 0..4 {
        let (ji, jj) = (i as i32 + jx[k], j as i32 + jy[k]);
        if ji < 0 || jj < 0 || ji >= n as i32 || jj >= m as i32 { continue; }

        let (ji, jj) = (ji as usize, jj as usize);
        if u == 0 && !vis[ji][jj][1] && a[ji][jj] <= mid {
          q.push_back((ji, jj, 1));
          vis[ji][jj][1] = true;
        }
      }
    }

    if vis[n - 1][m - 1][0] || vis[n - 1][m - 1][1] { right = mid; }
    else { left = mid + 1; }
  }

  writeln!(out, "{}", left).ok();
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
