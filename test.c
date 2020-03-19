/*#include <stdio.h>
#include <czmq.h>

#include <pthread.h>

void *task() {
	
	zsock_t *pull = zsock_new_pull("ipc:///tmp/feeds/0");
	char * result = zstr_recv(pull);
	printf("Info receiver: %s\n", result);
	zstr_free(&result);
	zsock_destroy(&pull);

	
}


int main(void) {
	
	zsock_t *push = zsock_new_push("ipc:///tmp/feeds/0");
	printf("Start\n");
	zstr_send(push, "Hello");
	

	
	pthread_t t;
	
	if(  pthread_create(&t, NULL, task, NULL) ) {
		
			printf("Error creating thread.\n");
	}
	
	if (  pthread_join(t, NULL) ) {
		
		printf("Error creating join\n");
		
	}
	
	zsock_destroy(&push);
	return 0;
}

*/
#include <stdio.h>
#include <czmq.h>


int main(void) {
	
	zsock_t *pull = zsock_new_pull("ipc:///tmp/feeds");

	printf("Start\n");
	

	char * result = zstr_recv(pull);
	printf("Info receiver: %s\n", result);
	zstr_free(&result);
	
	zsock_destroy(&pull);	
	return 0;
}

