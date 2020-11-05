信号量
锁只允许一个线程进入临界区，而信号量允许多个线程同时进入临界区,主要使用在同步和按次序执行方面。

API
int sem_init(sem_t *sem, int pshared, unsigned int value);
pshared : 指明信号量的类型。不为0时此信号量在进程间共享，0为当前进程的所有线程共享。

int sem_wait(sem_t *sem);
如果信号量的值大于0,将信号量的值减1,立即返回。如果信号量的值为0,则线程阻塞(加入睡眠队列)。

int sem_post(sem_t *sem); 
让信号量的值加1，如果有线程睡眠，唤醒一个(队首)。

初始值为0,就是条件变量
初始值为1,就是锁


