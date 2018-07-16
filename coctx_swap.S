.globl coctx_swap

coctx_swap:

	movl 4(%esp), %eax // %eax now is pointer to current context

  movl (%esp), %ebx //%esp points to return address, load it to %ebx

  // save return address to context
  movl %ebx, (%eax) 
  movl %esp, 4(%eax)
  movl %ebp, 8(%eax)
  movl %esi, 0xc(%eax)
  movl %edi, 0x10(%eax)
  movl %ebx, 0x14(%eax)
  
  movl 8(%esp), %eax // %eax now is pointer to next context

  // recover saved pointers
  movl 4(%eax), %esp
  movl 8(%eax), %ebp// 
  movl 0xc(%eax), %esi// 
  movl 0x10(%eax), %edi// 
  movl 0x14(%eax), %ebx// 

  movl (%eax), %eax// now %eax contains the address of next instruction

  jmp *%eax // jmp to the address
