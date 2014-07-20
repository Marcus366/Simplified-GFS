namespace cpp GFS

struct ReadResult {
1: string buf;
2: i64		count;
}

struct FileInfo {
1: string ipAddr;
2: string uuid;
3: i32		fd;
}

service FileOpManager {
	i32 open(1:string path, 2:i32 oflag, 3:i32 mode),

	i32 close(1:i32 fd),

	FileInfo askNewChunk(1:i32 fd)
}

