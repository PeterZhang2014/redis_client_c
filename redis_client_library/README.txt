#文件说明
     libgenredisclient.a为静态链接库文件。
     该库文件主要提供redis client的conect 、ping 、free-connect、publish、subscribe
以及unsubscribe的接口函数。

#使用说明
     接口函数的使用请参考测试文件test.c

#编译
     例：gcc test.c -I ./ ./libgenredisclient.a -lpthread
     其中 -I ./  指定库的头文件存放目录
         ./libgenredisclient.a 和 -lpthread为链接库文件

#生成的执行文件使用
     ./a.out ip port
     ip为redis-server的ip
     port为redis-server的port

#改动说明 v0.0.1 ~ v0.0.2 Apr 15,2015
     本次改动主要是给redisSubscirbeMessage函数增加外部入参void *arg,此参数作为函数
int (*message_handler)(const char *msg, size_t len, void *arg)的第三个参数传递进去。
