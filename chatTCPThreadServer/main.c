#include <pthread.h>
#include "chat.h"
#include "myServer.h"
#define LOGFILE "server.log"
#define LOG_TIME_FORMAT "%Y-%m-%d %H:%M:%S"
#define PORT 8888


 _Atomic unsigned int cli_count = 0;
 int uid = 10;
int listenfd = 0;
int port = PORT;
char *ip = "127.0.0.1";
int option = 1;
struct sockaddr_in serv_addr;
bool work;
struct sockaddr_in cli_addr;
pthread_t tid;
client_t *clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv)
{
	//client_t *cli = (client_t *)malloc(sizeof(client_t));
	/*if(argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		return 0;
	}*/



	if(prepar_socket() == 0)
	{
		return 0;
	}
	printf("WELCOME :)\n");

	while(1)
	{
            server_add_client();

			//Reduce CPU usage.
			sleep(1);
	}
	return 0;
}
