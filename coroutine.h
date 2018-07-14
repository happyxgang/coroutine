#ifndef _COROUTINE_H_
#define _COROUTINE_H_
#include <string.h>
typedef void (*PFunc)(void);


struct MContext {
	void* eip;
	void* esp;
	void* ebp;
	char stack_base[1024*10];
};

void init_context(MContext* cxt);
void make_context(MContext* cxt, void* p1, void* p2);

struct MCoroutine{
	MContext cxt;
	MCoroutine() {
		init_context(&cxt);
	}
};

struct MEnv {
	int size;
	MCoroutine* routine_stack[100];
	int inited;
	MEnv() {
		inited = 0;
		size = 0;
		memset(routine_stack, 0, sizeof(routine_stack));
	}
};

extern MEnv g_env;
void co_create(MCoroutine** co, PFunc func);
void co_resume(MCoroutine *co);
void co_yield();


#endif
