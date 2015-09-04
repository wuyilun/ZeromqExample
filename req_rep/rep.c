#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	void *context = zmq_ctx_new();

	void *responder = zmq_socket(context, ZMQ_REP);
	zmq_bind(responder, "tcp://*:5555");

	while(1){
		zmq_msg_t request;
		zmq_msg_init(&request);
		zmq_msg_recv(&request, responder, 0);
		char *recvmsg ;
		int recvsize = zmq_msg_size(&request);
		//memset(recvmsg, 0, recvsize);
		memcpy(recvmsg, (char *)zmq_msg_data(&request), recvsize);
		recvmsg[recvsize] = '\0';
		printf("Received request :[%s]\n", recvmsg);
		zmq_msg_close(&request);

		sleep(1);

		zmq_msg_t reply;
		//zmq_msg_init_size(&reply, 5);
		//memcpy((void*)zmq_msg_data(&reply), "World", 5);
		zmq_msg_init_data(&reply, "World", 5, NULL, NULL);
		zmq_msg_send(&reply, responder, 0);
		zmq_msg_close(&reply);
	}
	zmq_close(responder);
	zmq_ctx_destroy(context);
	return 0;
}
