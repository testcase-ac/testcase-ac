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
  let s = scan.token::<String>().chars().collect::<Vec<_>>();

  let mut fcost: i32 = 0;
  let mut scost: i32 = 0;
  let mut pw = 26 * 26;
  for i in 0..3 {
    let c = s[i] as i32 - 'A' as i32;
    fcost += c * pw;
    pw /= 26;
  }

  pw = 1000;
  for i in 4..8 {
    let c = s[i] as i32 - '0' as i32;
    scost += c * pw;
    pw /= 10;
  }

  if (fcost - scost).abs() <= 100 {
    writeln!(out, "nice").ok();
  }
  else {
    writeln!(out, "not nice").ok();
  }
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
