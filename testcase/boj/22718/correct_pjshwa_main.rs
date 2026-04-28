use io::Write;
use std::{io, str, collections::BinaryHeap};

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

fn theta(n: usize) -> usize {
  let mut ret = 0;
  let q = (n as f64).sqrt() as usize;
  for i in 1..=q {
    if n % i == 0 {
      ret += i;
      if i * i != n { ret += n / i; }
    }
  }
  ret
}

const MAX: usize = 1e6 as usize;

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let mut pr = vec![];
  let mut lp = vec![0; MAX + 1];

  for i in 2..=MAX {
    if lp[i] == 0 { lp[i] = i; pr.push(i); }
    for j in 0..pr.len() {
      if pr[j] <= lp[i] && i * pr[j] <= MAX { lp[i * pr[j]] = pr[j]; }
    }
  }

  let mut h = BinaryHeap::new();
  let mut l = 1;
  h.push()

  let mut ans = 0.0 as f64;
  for i in 1..=n {
    let u = theta(i) as f64 / i as f64;
    if ans < u {
      // writeln!(out, "{}", i).ok();
      ans = u;
    }
  }

  loop {
    let n = scan.token::<usize>();
    if n == 0 { break; }
    writeln!(out, "{:.10}", ans).ok();
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
