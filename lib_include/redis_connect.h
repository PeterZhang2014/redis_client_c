/* Copyright (C) 2015/04/10 , Genvision
 * File Name   : redis_connect.h
 * Description : 
 * Verision    : 1.0
 * Date        : Apr 10, 2015
 * Author      : Peter Zhang
 * Email       : zfy31415926.love@163.com OR zhangfy@genvision.cn
 */
#ifndef __REDIS_CONNECT_H__
#define __REDIS_CONNECT_H__
#include <hiredis.h>

/* name       : redisBuildConnect
 * input param 
 *       param1 : host ip
 *       param2 : host port
 *       param3 : timeout
 * function   : build the connection with redis-server
 * return     : the pointer typed with redisContext * will be returned,if
 *              success; or,NULL will be returned
 */
redisContext *redisBuildConnect(const char *ip, int port,const struct timeval timeout);

/* name       : redisFreeConnect
 * input param 
 *       param1 : redis context pointer
 * function   : free the connection with redis-server
 * return     : none
 */
void redisFreeConnect(redisContext *c);

/* name       : redisPingTest
 * input param 
 *       param1 : redis context pointer
 * function   : detection of network connection is normal
 * return     : if connection is nomal, return 0; or, return -1
 */
int redisPingTest(redisContext *c);
#endif /*endif __REDIS_CONNECT_H__*/
