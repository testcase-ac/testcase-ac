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

fn s4(n: usize) -> usize {
  if n == 0 { return 1; }

  // sum of divisors
  let (mut s, mut os) = (0, 0);
  let q = (n as f64).sqrt() as usize + 1;
  for i in 1..q {
    if n % i == 0 {
      s += i;
      if i & 1 == 1 { os += i; }
      if i * i != n {
        s += n / i;
        if (n / i) & 1 == 1 { os += n / i; }
      }
    }
  }

  if (n & 1) == 1 { 8 * s }
  else { 24 * os }
}

fn s5(n: usize) -> usize {
  let q = (n as f64).sqrt() as usize + 1;

  let mut ret = s4(n);
  for i in 1..q {
    if n < i * i { break; }
    ret += s4(n - i * i) * 2;
  }
  ret
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let n = scan.token::<usize>();
  writeln!(out, "{}", s4(n)).ok();
  writeln!(out, "{}", s5(n)).ok();
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
