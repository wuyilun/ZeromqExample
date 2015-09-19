/*************************************************************************
    > File Name: push.c
    > Author: wuyilun
    > Mail: wuyilun526@163.com 
    > Created Time: Fri 18 Sep 2015 08:11:37 PM CST
 ************************************************************************/

#include<stdio.h>
#include<zmq.h>
#include<string.h>

int main(){
	void *context = zmq_ctx_new();
	void *pusher = zmq_socket(context, ZMQ_PUSH);
	zmq_bind(pusher, "tcp://*:5555");
	
	while(1){
		zmq_msg_t send;
		zmq_msg_init_data(&send, "hello", 5, NULL, NULL);
		printf("Sending hello\n");
		zmq_msg_send(&send, pusher, 0);
		zmq_msg_close(&send);
		sleep(1);
	}
	zmq_close(pusher);
	zmq_ctx_destroy(context);
	return 0;
}
