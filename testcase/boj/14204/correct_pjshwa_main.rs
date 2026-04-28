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

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let (n, m) = (scan.token::<usize>(), scan.token::<usize>());
  let a = (0..n).map(|_| (0..m).map(|_| scan.token::<usize>()).collect::<Vec<_>>()).collect::<Vec<_>>();

  let mut b = vec![];
  for j in 0..m { b.push((a[0][j], j)); }
  b.sort();

  let mut v = vec![];
  for i in 0..n {
    let mut cur = vec![];
    for j in 0..m {
      let nj = b[j].1;
      cur.push(a[i][nj]);
    }
    v.push(cur);
  }
  v.sort_by(|a, b| a[0].cmp(&b[0]));

  for i in 0..n {
    if i > 0 && v[i][0] < v[i - 1][m - 1] { writeln!(out, "0").ok(); return; }
    for j in 0..m {
      if j > 0 && v[i][j] < v[i][j - 1] { writeln!(out, "0").ok(); return; }
    }
  }
  writeln!(out, "1").ok();
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
