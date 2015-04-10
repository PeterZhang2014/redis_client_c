/* Copyright (C) 2015/04/10 , Genvision
 * File Name   : redis_connect.h
 * Description : 
 * Verision    : 1.0
 * Date        : Apr 10, 2015
 * Author      : Peter Zhang
 * Email       : zfy31415926.love@163.com OR zhangfy@genvision.cn
 */
/********************************************************************
 *                      INCLUDE                                     *
 ********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <redis_connect.h>
#include <string.h>
/********************************************************************
 *                       DEFINE                                     *
 ********************************************************************/

/********************************************************************
 *                     GLOBAL VARIABLES                             *
 ********************************************************************/

/********************************************************************
 *                     EXTERN VARIABLES                             *
 ********************************************************************/

/********************************************************************
 *                     FUNCTION DEFINE                              *
 ********************************************************************/
/* name       : redisBuildConnect
 * input param 
 *       param1 : host ip
 *       param2 : host port
 *       param3 : timeout
 * function   : build the connection with redis-server
 * return     : the pointer typed with redisContext * will be returned,if
 *              success; or,NULL will be returned
 */
redisContext *redisBuildConnect(const char *ip, int port,const struct timeval timeout)
{
	redisContext *c = NULL;

	c = redisConnectWithTimeout(ip,port,timeout);
	if (c == NULL || c->err)
	{
		if (c)
		{
			printf("Connection error : %s\n",c->errstr);
			redisFree(c);
		}
		else
		{
			printf("Connection error : can't allocate redis context\n");
		}
		return NULL;
	}
	return c;
}
/* name       : redisFreeConnect
 * input param 
 *       param1 : redis context pointer
 * function   : free the connection with redis-server
 * return     : none
 */
void redisFreeConnect(redisContext *c)
{
	return redisFree(c);
}
/* name       : redisPingTest
 * input param 
 *       param1 : redis context pointer
 * function   : detection of network connection is normal
 * return     : if connection is nomal, return 0; or, return -1
 */
int redisPingTest(redisContext *c)
{
	redisReply *reply = NULL;
	
	reply = redisCommand(c,"PING");
	if (strcmp(reply->str,"PONG") == 0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}
