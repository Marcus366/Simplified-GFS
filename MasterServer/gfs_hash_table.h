#ifndef __GFS_HASH_TABLE_H__
#define __GFS_HASH_TABLE_H__


#include <sys/types.h>
#include "gfs_list.h"


typedef uint32_t (*hash_func)(void *);

typedef struct gfs_hash_table_s {
	uint32_t 	size;
	uint32_t 	capacity;
	void 		*elem;
	hash_func 	func;
} gfs_htable_t;


int 	gfs_htable_new(gfs_htable_t **table, hash_func func);
int 	gfs_htable_free(gfs_htable_t **table);

void 	gfs_htable_put(gfs_htable_t *table, void* key, void* val);
void*	gfs_htable_get(gfs_htable_t *table, void* key);


#endif
