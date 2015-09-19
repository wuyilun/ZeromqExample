/*************************************************************************
    > File Name: pull.c
    > Author: wuyilun
    > Mail: wuyilun526@163.com 
    > Created Time: Fri 18 Sep 2015 08:30:02 PM CST
 ************************************************************************/

#include<stdio.h>
#include<zmq.h>
#include<string.h>
#include<malloc.h>


int main(){
	void *context = zmq_ctx_new();
	void *puller = zmq_socket(context, ZMQ_PULL);
	zmq_connect(puller, "tcp://localhost:5555");
	int i = 0;
	while(1){
		zmq_msg_t recv;
		zmq_msg_init(&recv);
		zmq_msg_recv(&recv, puller, 0);
		char recvmsg[100];
		memset(recvmsg, 0, zmq_msg_size(&recv)+1);
		memcpy(recvmsg, (char *)zmq_msg_data(&recv), zmq_msg_size(&recv));
		recvmsg[zmq_msg_size(&recv)] = '\0';
		++i;
		printf("Received %d: [%s]\n", i, recvmsg);
		zmq_msg_close(&recv);
	}
	zmq_close(puller);
	zmq_ctx_destroy(context);
	return 0;
}
