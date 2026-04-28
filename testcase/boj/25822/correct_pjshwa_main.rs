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
  let (c, n) = (scan.token::<f64>(), scan.token::<usize>());
  let fcount = 2.min((c / 0.99) as usize);

  let a = (0..n).map(|_| scan.token::<usize>()).collect::<Vec<_>>();
  let mut d = vec![vec![0; fcount + 1]; n + 1];

  let mut mval = 0;
  for i in 0..n { mval = mval.max(a[i]); }

  for i in 1..=n {
    for f in 0..=fcount {
      if a[i - 1] > 0 {
        d[i][f] = d[i][f].max(d[i - 1][f] + 1);
      }
      if f > 0 {
        d[i][f] = d[i][f].max(d[i - 1][f - 1] + 1);
      }
    }
  }

  let mut ans = 0;
  for i in 1..=n {
    for f in 0..=fcount { ans = ans.max(d[i][f]); }
  }
  writeln!(out, "{}", ans).ok();
  writeln!(out, "{}", mval).ok();
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
