#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <redis_connect.h>
#include <redis_pubsub.h>
#include <pthread.h>
#include <unistd.h>
void * thread_publish(void *args);
void * thread_subscribe(void *args);
/* name    : main
 * param1  : the number of the args
 * param2  : host ip
 * param3  : host port
 * function: only test
 * return  : return 0, if success; or, return -1
 */
int main(int argc, const char *argv[])
{
	redisContext *c_pub;
	redisContext *c_sub;
	const char *hostname = (argc > 1) ?argv[1] : "127.0.0.1";
    int port = (argc > 2) ? atoi(argv[2]) : 6379;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	/*build connection*/
	c_pub = redisBuildConnect(hostname,port,timeout);
	if (c_pub == NULL)
	{
		return -1;
	}
	c_sub = redisBuildConnect(hostname,port,timeout);
	if (c_sub == NULL)
	{
		return -1;
	}
	/*test connection*/
	if (redisPingTest(c_pub) != 0)
	{
		printf("Connection is unnomal\n");
	}
	if (redisPingTest(c_sub) != 0)
	{
		printf("Connection is unnomal\n");
	}

	pthread_t pt_publish_id;
	pthread_create(&pt_publish_id,NULL,thread_publish,(void *)c_pub);

	pthread_t pt_subscribe_id;
	pthread_create(&pt_subscribe_id,NULL,thread_subscribe,(void *)c_sub);

	pthread_join(pt_publish_id, NULL);

	redisUnsubscribeMessage(c_sub, "channel.1");
	pthread_join(pt_subscribe_id, NULL);

    /* Disconnects and frees the context */
	redisFreeConnect(c_pub);
	redisFreeConnect(c_sub);

	return 0;
}
void * thread_publish(void *args)
{
	redisContext *c = (redisContext *)args;
	int i = 10;
	const char msg[8] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06};
	while (i)
	{
		redisPublishMessage(c, "channel.1",msg,7);
		sleep(1);
		i --;
	}
	printf("thread_publish exit\n");
	pthread_exit(NULL);
}
int message_handler(const char *msg,size_t len)
{
	int i =0;
	for (;i<len;i++)
	{
		printf("%d\t",msg[i]);
	}
	printf("\n");
	return 0;
}
void * thread_subscribe(void *args)
{
	redisContext *c = (redisContext *)args;
	redisSubscribeMessage(c,"channel.1",message_handler);

	printf("thread_subscribe exit\n");
	pthread_exit(NULL);
}
