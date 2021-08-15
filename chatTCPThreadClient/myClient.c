#include "myClient.h"


extern volatile sig_atomic_t flag;
extern struct sockaddr_in server_addr;
extern int sockfd;
extern char room[3];

void catch_ctrl_c_and_exit(int sig)
{
	flag = 1;
}

void send_msg_handler(char* name)
{
	char st[LEN] = {};
	char buffer[LEN + 32] = {};
	bool work = true;
	while(work)
	{
		fgets(st, LEN, stdin);
		strcat(st,"3");
		str_trim_lf(st, LEN);

		if (strcmp(st, "~exit~") == 0 /*|| st[0]=='\0'*/)
		{
			work = false;
    	}
		else
		{
			sprintf(buffer, "%s: %s \n", name+1, st);
			send(sockfd, buffer, strlen(buffer), 0);
		}
		if (work)
		{
			bzero(st, LEN);
			bzero(buffer, LEN + 32);
		}
	}
	flag=1;
}

//Receive message.
void recv_msg_handler()
{
	char baf[LEN] = {};
	bool work = true;
	while(work)
	{
		int receive = recv(sockfd, baf, LEN, 0);
    	if (receive > 0)
		{
    		printf("%s", baf);
    	}
		else if (receive == 0)
		{
			work = false;
    	}
		else
		{
			perror("recv");
		}
		if (work)
		{
			memset(baf, 0, sizeof(baf));
		}
	}
}

void client_init(char* ip,int port)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_port = htons(port);
}

char* client_connect(char* name)
{

   if ((connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))) == -1)
	{
		perror("client: connect");
		return;
	}

	strcpy(name,"1");

	printf("Please enter your name: ");
	fgets(name+1, 31, stdin);
	str_trim_lf(name, strlen(name));

	if (strlen(name) > 32 || strlen(name) < 2)
	{
		printf("Name must be less than 30 and more than 2 characters.\n");
		return;
	}

	//Send name
	send(sockfd, name, 32, 0);

	printf("What room would you like to be in? \n r1 r2 or r3\n");
	fgets(room,3,stdin);
	str_trim_lf(room, 2);

	strcat(room,"2");

	send(sockfd, room, 2, 0);

	printf("WELCOME :)\n");
	return name;
}

void client_threading_procces(pthread_t* send_msg,pthread_t* recv_msg)
{
   if(pthread_create(send_msg, NULL, (void *) send_msg_handler, NULL) != 0)
	{
		perror("client: pthread");
		return;
	}

	if(pthread_create(recv_msg, NULL, (void *) recv_msg_handler, NULL) != 0)
	{
		perror("client: pthread");
		return;
	}
}

void client_close()
{
  while (1)
	{
		if(flag)
		{
			printf("\n Good Bye :)\n");
			close(sockfd);
			break;
    	}
	}
}

