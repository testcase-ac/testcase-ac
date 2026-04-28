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
  let (n, k) = (scan.token::<usize>(), scan.token::<usize>());
  let a = (0..k).map(|_| scan.token::<usize>()).collect::<Vec<_>>();

  let mut has_n = false;
  for e in &a {
    if e == &n {
      has_n = true;
    }
  }

  if has_n {
    writeln!(out, "{} {}", n, k - 1).ok();
    for e in &a {
      if e != &n {
        write!(out, "{} ", e).ok();
      }
    }
  }
  else {
    writeln!(out, "{} {}", n, k + 1).ok();
    for e in &a {
      write!(out, "{} ", e).ok();
    }
    write!(out, "{}", n).ok();
  }
  writeln!(out).ok();
}

fn main() {
  let (stdin, stdout) = (io::stdin(), io::stdout());
  let mut scan = UnsafeScanner::new(stdin.lock());
  let mut out = io::BufWriter::new(stdout.lock());

  // let t = 1;
  let t = scan.token::<usize>();
  for _ in 0..t {
    solve(&mut scan, &mut out);
  }
}
