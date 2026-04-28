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

const INF: i64 = 0x3f3f3f3f3f3f3f3f;

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let (n, m) = (scan.token::<usize>(), scan.token::<usize>());
  let a = (0..n).map(|_| scan.token::<i64>()).collect::<Vec<_>>();

  let mut d = vec![vec![-INF; 2 * m + 1]; n + 1];
  d[0][0] = 0;

  for i in 1..=n { for j in 0..=(2 * m) {
    if j & 1 == 1 {
      d[i][j] = d[i - 1][j] + a[i - 1];
      d[i][j] = d[i][j].max(d[i - 1][j - 1] + a[i - 1]);
    }
    else {
      d[i][j] = d[i - 1][j];
      if j > 0 { d[i][j] = d[i][j].max(d[i - 1][j - 1]); }
    }
  }}

  writeln!(out, "{}", d[n][2 * m].max(d[n][2 * m - 1])).ok();
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
