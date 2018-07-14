#include "coroutine.h"
#include <stdlib.h>

MEnv g_env;

extern "C"
{
	extern void coctx_swap(MContext *, MContext*) asm("coctx_swap");
};

//----- --------
// 32 bit
// | regs[0]: ret |
// | regs[1]: ebx |
// | regs[2]: ecx |
// | regs[3]: edx |
// | regs[4]: edi |
// | regs[5]: esi |
// | regs[6]: ebp |
// | regs[7]: eax |  = esp
enum {
	kEIP = 0,
	kESP = 7,
};

void MCoroutineFunc(MCoroutine* co, void* param) {
	if (co) {
		//co->func(co->param);
		//co->func();
	}
	co_yield();
}

struct CoParam{
	void* p1;
	void* p2;
};
void init_context(MContext* cxt) {
	memset(cxt, 0, sizeof(*cxt));
  cxt->reg[1] = (void*)((unsigned long)(cxt->stack_base+sizeof(cxt->stack_base)) & -16L);
}

//void make_context(MContext* cxt, void* p1, void* p2) {
//	char* sp = (char*)((unsigned long)(cxt->stack_base) + cxt->stack_size - sizeof(CoParam));
//	sp = (char*)((unsigned long)sp & -16L);
//
//	CoParam* p = (CoParam*)sp;
//	p->p1= p1;
//	p->p2= p2;
//
//	cxt->regEIP] = (void*)(&MCoroutineFunc);
//	cxt->reg[kESP] = (void*)((unsigned long)sp - 4);
//}
//
void co_create(MCoroutine** co, PFunc func) {
	MCoroutine* coroutine = (MCoroutine*)malloc(sizeof(MCoroutine));

	memset(coroutine, 0, sizeof(MCoroutine));
	//coroutine->func = func;
	//coroutine->param = param; 

	init_context(&coroutine->cxt);
  coroutine->cxt.reg[0]=(void*)func;
	//coroutine->cxt.stack_base = (char*)malloc(1024);
	//coroutine->cxt.stack_size = 1024;

	*co = coroutine;
}

void init_env() {
	g_env.size = 0;
	MCoroutine* co = NULL;
	co_create(&co, NULL);
	g_env.routine_stack[g_env.size] = co;
	g_env.size++;
	g_env.inited=1;
}

void co_resume(MCoroutine* co) {
	if (!g_env.inited) {
		init_env();
	}
	if (!co->started) {
	//	make_context(&co->cxt, (void*)co, 0);
		co->started = 1;
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

