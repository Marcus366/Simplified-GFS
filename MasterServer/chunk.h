#ifndef __CHUNK_H__
#define __CHUNK_H__


typedef struct chunk_s {
	uint64_t uuid;				/* the unique id of chunk    		*/
	uint32_t chk_addr; 			/* chunk location server address 	*/
	uint16_t chk_port; 			/* chunk port of the service 		*/
} chunk_t;


#endif