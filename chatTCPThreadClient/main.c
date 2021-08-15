
#include "chat.h"
#include <pthread.h>
#include "myClient.h"

volatile sig_atomic_t flag = 0;
struct sockaddr_in server_addr;
int sockfd = 0;
char room[3];
char name[32];


int main(int argc, char **argv)
{

	char *ip = LOCALHOST;
	int port = PORT;
	pthread_t send_msg;
	pthread_t recv_msg;
	signal(SIGINT, catch_ctrl_c_and_exit);
	char* name=(char*)malloc(sizeof(32));


	//Socket settings
	client_init(ip,port);

	//Connect to Server
	name=client_connect(name);

    if(pthread_create(&send_msg, NULL, (void *) send_msg_handler, (void*)name) != 0)
	{
		perror("client: pthread");
		return 0;
	}                                                                                  //TODO:check about the function

	if(pthread_create(&recv_msg, NULL, (void *) recv_msg_handler, NULL) != 0)
	{
		perror("client: pthread");
		return 0;
	}

	client_close();
	free(name);
	return 0;
}

