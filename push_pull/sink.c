/*************************************************************************
    > File Name: sink.c
    > Author: wuyilun
    > Mail: wuyilun526@163.com 
    > Created Time: Fri 18 Sep 2015 10:36:43 PM CST
 ************************************************************************/

#include<stdio.h>
#include"../include/zhelpers.h"

int main(){
	void *context = zmq_ctx_new();
	void *receiver = zmq_socket(context, ZMQ_PULL);
	zmq_bind(receiver, "tcp://*:5558");
	char *string = s_recv(receiver);
	free(string);
	int64_t start_time = s_clock();

	int task_nbr;
	for(task_nbr = 0; task_nbr < 100; ++task_nbr){
		char *string = s_recv(receiver);
		free(string);
		if((task_nbr/10)*10 == task_nbr)
			printf(":");
		else
			printf(".");
		fflush(stdout);
	}
	printf("Total elapsed time: %d msec\n", (int)(s_clock() - start_time));
	zmq_close(receiver);
	zmq_ctx_destroy(context);
	return 0;
}
