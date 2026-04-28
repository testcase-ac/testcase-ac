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

fn cval(n: usize, z: usize) -> usize {
  if n <= z { return n; }

  let q = n / z;
  let r = n % z;
  let v = q * (q + 1) / 2;

  v * z + r * (q + 1)
}

const INF: i64 = 1e18 as i64;

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let (n, m, k) = (scan.token::<usize>(), scan.token::<usize>(), scan.token::<usize>());
  let mut b = vec![0; m + 1];
  for _ in 0..n {
    let x = scan.token::<usize>();
    b[x] += 1;
  }

  let mut d = vec![vec![INF; k + 1]; m + 1];
  d[0][0] = 0;
  for i in 1..=m {
    for nk in 0..=k {
      for add in 0..=nk {
        let v = cval(b[i], add + 1);
        d[i][nk] = d[i][nk].min(d[i - 1][nk - add] + v as i64);
      }
    }
  }

  writeln!(out, "{}", d[m][k]).ok();
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
