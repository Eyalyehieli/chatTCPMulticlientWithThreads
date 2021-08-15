#ifndef MYSERVER_H_INCLUDED
#define MYSERVER_H_INCLUDED
#include <pthread.h>
#include "chat.h"
#define LOGFILE "server.log"
#define LOG_TIME_FORMAT "%Y-%m-%d %H:%M:%S"
#define PORT 8888

//Client structure
typedef struct client
{
	struct sockaddr_in address;
	int sockfd;
	int uid;
	char room;
	char name[32];
} client_t;

void get_timestamp(char *dt);
void print_log (char *msg);
void printclient(struct sockaddr_in addr);
void queue_add(client_t *cl);
void queue_remove(int uid);
void sendinfo(char *s, int uid, char room);
void *handle_client(void *arg);
int prepar_socket();
void server_add_client();


#endif // MYSERVER_H_INCLUDED
