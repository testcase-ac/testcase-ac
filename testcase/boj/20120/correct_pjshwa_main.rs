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

const INF: i64 = 1e18 as i64;

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let n = scan.token::<usize>();
  let a = (0..n).map(|_| scan.token::<i64>()).collect::<Vec<_>>();

  // d[i][j][k] = i-th index, j-th combo, k-th zero streak
  let mut d = vec![vec![vec![-INF; 3]; n + 1]; n + 1];
  d[0][0][0] = 0;

  for i in 1..=n { for j in 0..=n {
    for k in 0..3 {
      // Hit this note
      if j > 0 {
        d[i][j][0] = d[i][j][0].max(d[i - 1][j - 1][k] + a[i - 1] * j as i64);
      }

      // Skip this note
      if k > 0 {
        d[i][0][k] = d[i][0][k].max(d[i - 1][j][k - 1]);
      }
    }
  }}

  let mut ans = 0;
  for j in 0..=n { for k in 0..3 { ans = ans.max(d[n][j][k]); }}
  writeln!(out, "{}", ans).ok();
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
