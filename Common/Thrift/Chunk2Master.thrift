namespace cpp GFS

struct ChunkServerInfo {
1: string			ipAddr;
2: i64				totalMem;
3: i64				availMem;
4: list<i16>  availPort;
}

service ChunkServerManager extends shared.SharedService {
	bool register(1:string ipAddr, 2:i16 availPort),

	oneway void unregister(1:string ipAddr),

	bool heartBeat(1:ChunkServerInfo info)
}

