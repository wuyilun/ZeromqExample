#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void call();

int main(){
	printf("begin call:\n");
	call();
	printf("call return!\n");
	return 0;
}

void call()
{
	void *context = zmq_ctx_new();
	void *requester = zmq_socket(context, ZMQ_REQ);
	zmq_connect(requester, "tcp://localhost:5555");

	zmq_msg_t request;
	zmq_msg_t reply;

	int request_nbr = 1;
	zmq_msg_init_data(&request, "Hello", 5, NULL, NULL);
	printf("Seding request %d ...\n", request_nbr);
	zmq_msg_send(&request, requester, 0);
	zmq_msg_close(&request);

	zmq_msg_init(&reply);
	zmq_msg_recv(&reply, requester, 0);
	char *recvmsg;
	memset(recvmsg, 0, zmq_msg_size(&reply)+1 );
	memcpy(recvmsg, (char *)zmq_msg_data(&reply), zmq_msg_size(&reply));
	printf("Received reply %d: [%s]\n", request_nbr, recvmsg);
	zmq_msg_close(&reply);
	sleep(2);
	zmq_close(requester);
	zmq_ctx_destroy(context);

}
