namespace cpp GFS

struct ReadResult {
1: binary buf;
2: i32		count;
}

service ChunkServer {
 	i32 open(1:string path, 2:i32 oflag, 3:i32 mode),

	i32 close(1:i32 fd),

	i64 write(1:i32 fd, 2:binary buf, 3:i32 count),

	ReadResult read(1:i32 fd, 2:i32 count)
}

