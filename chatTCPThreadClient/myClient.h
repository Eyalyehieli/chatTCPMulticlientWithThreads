#ifndef MYCLIENT_H_INCLUDED
#define MYCLIENT_H_INCLUDED
#include "chat.h"
#include <pthread.h>
#define PORT 8888
#define LOCALHOST "127.0.0.1"


void recv_msg_handler();
void send_msg_handler();
void catch_ctrl_c_and_exit(int sig);
void client_init(char* ip,int port);
char* client_connect(char* name);
void client_threading_procces(pthread_t* send_msg,pthread_t* recv_msg);
void client_close();

#endif // MYCLIENT_H_INCLUDED
