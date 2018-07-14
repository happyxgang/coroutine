#include "coroutine.h"
#include <stdlib.h>

MEnv g_env;

extern "C"
{
	extern void coctx_swap(MContext *, MContext*) asm("coctx_swap");
};

void init_env();

void init_context(MContext* cxt) {
	memset(cxt, 0, sizeof(*cxt));
  cxt->esp = (void*)((unsigned long)(cxt->stack_base+sizeof(cxt->stack_base)) & -16L);
}

void co_create(MCoroutine** co, PFunc func) {
	MCoroutine* coroutine = (MCoroutine*)malloc(sizeof(MCoroutine));

	memset(coroutine, 0, sizeof(MCoroutine));

	init_context(&coroutine->cxt);
  coroutine->cxt.eip = (void*)func;

	*co = coroutine;
}


void co_resume(MCoroutine* co) {
	if (!g_env.inited) {
		init_env();
	}

	MCoroutine* cur = g_env.routine_stack[g_env.size - 1];

	g_env.routine_stack[g_env.size] = co;
  g_env.size++;

	coctx_swap(&cur->cxt, &co->cxt);
}

void co_yield() {

	MCoroutine* cur = g_env.routine_stack[g_env.size - 1];
	MCoroutine* pre = g_env.routine_stack[g_env.size - 2];

	g_env.size--;

	coctx_swap(&cur->cxt, &pre->cxt);
}

void init_env() {
	g_env.size = 0;
	MCoroutine* co = NULL;
	co_create(&co, NULL);
	g_env.routine_stack[g_env.size] = co;
	g_env.size++;
	g_env.inited=1;
}
