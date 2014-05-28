#include "../MasterServer/linklist.h"
#include "stdio.h"

int main(int argc, char const *argv[])
{
	char t;
	linklist_t* linklist;
	linklist_init(&linklist);
	while (scanf("%c",&t) ) {
		if (t == 'i') {
			int tt;
			scanf("%d",&tt);
			linklist_push_back(linklist, (void*)tt);
		}
		if(t == 'p'){
			linklist_print(linklist);
		}
		if (t == 'd') {
			int tt;
			scanf("%d",&tt);
			linklist_delete(linklist, (void*)tt);
		}
	}
	return 0;
}