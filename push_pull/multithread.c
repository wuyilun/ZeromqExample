/*************************************************************************
    > File Name: multithread.c
    > Author: wuyilun
    > Mail: wuyilun526@163.com 
    > Created Time: Sat 19 Sep 2015 08:55:03 AM CST
 ************************************************************************/

#include<stdio.h>
#include<zmq.h>
#include<pthread.h>
#include"../include/zhelpers.h"

static void * worker(void *context){
	void *w = zmq_socket(context, ZMQ_PULL);
	zmq_connect(w, "inproc://workers");
	//zmq_connect(w, "tcp://localhost:5557");
	while(1){
		int id = pthread_self();
		printf("%d:", id);
		char *receiver = s_recv(w);
		sleep(2);
		printf("%s\n", receiver);
		free(receiver);
	}
	zmq_close(w);
	return NULL;
}

int main(){
	void *context = zmq_ctx_new();
	void *pusher = zmq_socket(context, ZMQ_PUSH);
	zmq_bind(pusher, "inproc://workers");
	//zmq_bind(pusher, "tcp://*:5557");

	int thread_number;
	for(thread_number = 0; thread_number < 3; ++thread_number){
		pthread_t pt;
		pthread_create(&pt, NULL, worker, context);
	}

	int send_num = 1;
	char send_string[100];
	while(1){
		sprintf(send_string, "%d", send_num++);
		s_send(pusher, send_string);
		sleep(2);
	}
	zmq_close(pusher);
	zmq_ctx_destroy(context);
	return 0;
}
