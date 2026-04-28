use std::{io, str, cmp};

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

fn main() {
  let (stdin, stdout) = (io::stdin(), io::stdout());
  let mut scan = UnsafeScanner::new(stdin.lock());

  let s = scan.token::<String>();
  let t = scan.token::<String>();
  let s_chars = s.chars().collect::<Vec<_>>();
  let t_chars = t.chars().collect::<Vec<_>>();

  let n = s.len();
  let mut si = usize::MAX;
  let mut ei = 0;

  for i in 0..n {
    if s_chars[i] != t_chars[i] {
      si = cmp::min(si, i as usize);
      ei = cmp::max(ei, i as usize);
    }
  }

  for i in si..=ei {
    if s_chars[i] != t_chars[ei + si - i] {
      println!("0");
      return;
    }
  }

  let mut ans = 1;
  for i in 1..=si {
    if ei + i >= n {
      break;
    }
    if s_chars[si - i] == t_chars[ei + i] {
      ans += 1;
    }
    else {
      break;
    }
  }

  println!("{}", ans);
}
