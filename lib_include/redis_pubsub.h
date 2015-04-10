/* Copyright (C) 2015/04/09 , Genvision
 * File Name   : redis_pubsub.h
 * Description : 
 * Verision    : 1.0
 * Date        : Apr 9, 2015
 * Author      : Peter Zhang
 * Email       : zfy31415926.love@163.com OR zhangfy@genvision.cn
 */
#ifndef __REDIS_PUBSUB_H__
#define __REDIS_PUBSUB_H__
#include <hiredis.h>

/* name    : redisPublishMessage
 * input param
 *       param1  : redisContext pointer
 *       param2  : channel name
 *       param3  : message buffer pointer
 *       param4  : message len
 * function: publish the messahe to the channel
 * return  : return the number of subscribe, if success; or, return -1
 */
int redisPublishMessage(redisContext *c, const char *channel, \
		const char *msg, size_t len);

/* name    : redisSubscribeMessage
 * input param
 *       param1  : redisContext pointer
 *       param2  : channel name
 *       param3  : message handler function pointer
 * function: subscribe the channel and receive messahe from it
 * return  : return 0, if success; or, return -1
 */
int redisSubscribeMessage(redisContext *c, const char *channel,\
		int (*message_handler)(const char *msg, size_t len));

/* name    : redisUnsubscribeMessage
 * input param
 *       param1  : redisContext pointer
 *       param2  : channel name
 * function: unsubscribe the channel
 * return  : return 0, if success; or, return -1
 */
int redisUnsubscribeMessage(redisContext *c, const char *channel);
#endif
