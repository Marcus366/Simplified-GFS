namespace cpp GFS

struct ReadResult {
1: string buf;
2: i64		count;
}

service FileIO {
  i64 write(1:i32 fd, 2:binary buf),

	ReadResult read(1:i32 fd, 2:i64 count)
}

