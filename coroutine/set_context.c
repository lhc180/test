#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

/* 执行上下文结构体 */
/* typedef struct ucontext {
 *         struct ucontext *uc_link;    //从当前上下文返回时，将切换到的上下文环境.
 *         sigset_t         uc_sigmask; //保存上下文中阻塞的信号.
 *         stack_t          uc_stack;   //上下文使用的栈空间.
 *         mcontext_t       uc_mcontext;//保存当前上下文的执行状态，如寄存器状态，cpu计数，etc.
 *         ....
 *         } ucontext_t; */

/* setcontext 家族中的函数集合,切换到ucp所指定的上下文中 
 * int   setcontext(const ucontext_t *ucp) */

/* 保存当前上下文到 ucp中
 * int   getcontext(ucontext_t *ucp) */

/* 在ucp 环境中，创建一个可选的控制线程，之前ucp环境必须被初始化，并且ucp.uc_stack必须指向已分配的一段栈空间。
 * 当通过setcontext或swapcontext切换到ucp上下文时，控制流从func开始执行。
 * void  makecontext(ucontext_t *ucp, void *func(), int argc, ...) */

/* 切换执行控制权到 ucp指定的环境，保存当前执行环境到oucp       
 * int   swapcontext(ucontext_t *oucp, ucontext_t *ucp) */

void loop(
		ucontext_t *loop_context,
		ucontext_t *other_context,
		int *i_from_iterator)
{
	int i;

	for (i = 0; i < 10; i++) {
		/* 将循环计数写到迭代器中 */
		*i_from_iterator = i;

		/* 保存当前执行上下文到 loop_context,
		 * 并切换到other_context 执行上下文中 */
		swapcontext(loop_context, other_context);
	}

	/* loop_context上下文执行流将结束，
	 * 并且执行上下文将自动切换到(&loop_context->uc_link)上下文
	 * 因此不用显式调用 setcontext(&loop_context->uc_link) */
}
int main(void)
{
	/* 定义3个contexts
	 * (1) main_context1: 保存main函数中的执行上下文，loop 执行流完成时，切换到的执行上下文
	 * (2) main_context2: 保存main函数中的执行上下文，loop 执行流执行过程中，通过swapcontext切换到main中的执行上下文
	 * (3) loop_context:  保存loop函数中的执行上下文，main函数中通过swapcontext 从main_context2切换到 loop_context */
	ucontext_t main_context1, main_context2, loop_context;

	char iterator_stack[SIGSTKSZ];
	/* iterator_loop 结束标志 */
	volatile int iterator_finished;
	/* 迭代器 */
	volatile int i_from_iterator;

	/* makecontext loop_context 之前必须要通过 getcontext 并初始化loop_context */
	getcontext(&loop_context);
	loop_context.uc_link          = &main_context1;
	loop_context.uc_stack.ss_sp   = iterator_stack;
	loop_context.uc_stack.ss_size = sizeof(iterator_stack);

	/* 填充loop_context执行流 */
	makecontext(&loop_context, (void (*)(void)) loop, 
			3, &loop_context, &main_context2, &i_from_iterator);

	/* 清除迭代器 finished 标志 */
	iterator_finished = 0;

	/* 保存当前context。当loop上下文控制流执行完成时，执行上下文将切换到该处 */ 
	getcontext(&main_context1);
	printf("main1\n");
	if (!iterator_finished) {
		/* 设置iterator_finished，当iterator上下文执行流结束时，
		 * 上下文切换到uc_link指定的上下文，也即main_context1.
		 * 此时if条件判断失败，迭代操作不会被重启*/
		iterator_finished = 1;

		printf("main2\n");
		while(1) {
			/* 保存当前执行上下文到 main_context2，切换到当前执行上下文到 loop_context */
			swapcontext(&main_context2, &loop_context);
			printf("%d\n", i_from_iterator);
		}
	}
	printf("main3\n");

	return 0;
}
