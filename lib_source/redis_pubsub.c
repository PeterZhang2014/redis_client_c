/* Copyright (C) 2015/04/09 , Genvision
 * File Name   : redis_pubsub.c
 * Description : 
 * Verision    : 1.0
 * Date        : Apr 9, 2015
 * Author      : Peter Zhang
 * Email       : zfy31415926.love@163.com OR zhangfy@genvision.cn
 */
/********************************************************************
 *                      INCLUDE                                     *
 ********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <redis_pubsub.h>
#include <sys/select.h>
#include <string.h>
/********************************************************************
 *                       DEFINE                                     *
 ********************************************************************/

/********************************************************************
 *                     GLOBAL VARIABLES                             *
 ********************************************************************/
static int g_iSubscribeExitFlag = 0;
/********************************************************************
 *                     EXTERN VARIABLES                             *
 ********************************************************************/

/********************************************************************
 *                     FUNCTION DEFINE                              *
 ********************************************************************/
/* name    : redisPublishMessage
 * input param
 *     param1  : redisContext pointer
 *     param2  : channel name
 *     param3  : message buffer pointer
 *     param4  : message len
 * function: publish the messahe to the channel
 * return  : return the number of subscribe, if success; or, return -1
 */
int redisPublishMessage(redisContext *c, const char *channel, \
		const char *msg, size_t len)
{
	redisReply *reply = NULL;
	int ret = 0;

	reply = redisCommand(c,"PUBLISH %s %b",channel,msg,len);
	if (reply->type == REDIS_REPLY_ERROR)
	{
		printf("Publish message error : %s\n",reply->str);
		freeReplyObject(reply);
		return -1;
	}
	ret = reply->integer;
	freeReplyObject(reply);

	return ret;
}
/* name    : redisSubscribeMessage
 * input param
 *       param1  : redisContext pointer
 *       param2  : channel name
 *       param3  : message handler function pointer
 * function: subscribe the channel and receive messahe from it
 * return  : return 0, if success; or, return -1
 */
int redisSubscribeMessage(redisContext *c, const char *channel,\
		int (*message_handler)(const char *msg, size_t len))
{
	redisReply *reply = NULL;
	void *_reply = NULL;

	/*subscribe channel*/
	reply = redisCommand(c,"SUBSCRIBE %s",channel);
	if (reply->type == REDIS_REPLY_ERROR)
	{
		printf("Subscribe channel %s error : %s\n",channel,reply->str);
		return -1;
	}
	freeReplyObject(reply);
	/*receive message*/
	fd_set rfd;
	int max_fd = c->fd + 1;
	while (1)
	{
		FD_ZERO(&rfd);
		FD_SET(c->fd, &rfd);
		struct timeval timeout= {0,200}; //200us
		int ret = select(max_fd, &rfd, NULL, NULL,&timeout);
		if ((ret > 0) && (FD_ISSET(c->fd,&rfd)))
		{
		    if (redisGetReply(c,&_reply) != REDIS_OK)
		    {
			    printf("redisGetReply error\n");
			    return -1;
		    }
		    reply = (redisReply *)_reply;
		    if (reply->type == REDIS_REPLY_ERROR)
		    {
			    printf("Receive message error : %s\n",reply->str);
			    continue;
		    }
			if (strcmp(reply->element[0]->str, "message") == 0)
			{
				if (strcmp(reply->element[1]->str, channel) == 0)
				{
					/*process message data*/
					if (message_handler != NULL)
					{
						message_handler(reply->element[2]->str,reply->element[2]->len);
					}
				}
			}
            freeReplyObject(reply);
		}//end if(ret > 0)
		if (g_iSubscribeExitFlag == 1)
		{
			break;
		}
	}

	return 0;
}
/* name    : redisUnsubscribeMessage
 * input param 
 *       param1  : redisContext pointer
 *       param2  : channel name
 * function: unsubscribe the channel
 * return  : return 0, if success; or, return -1
 */
int redisUnsubscribeMessage(redisContext *c, const char *channel)
{
	redisReply *reply = NULL;

	/*unsubscribe channel*/
	reply = redisCommand(c,"UNSUBSCRIBE %s",channel);
	if (reply->type == REDIS_REPLY_ERROR)
	{
		printf("Unsubscribe channel %s error : %s\n",channel,reply->str);
		return -1;
	}
	g_iSubscribeExitFlag = 1;
    return 0;
}
