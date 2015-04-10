#文件说明
libgenredisclient.a为静态链接库文件。
该库文件主要提供redis client的conect 、ping 、free-connect、publish
、subscribe以及unsubscribe的接口函数。

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
