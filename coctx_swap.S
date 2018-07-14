/*
* Tencent is pleased to support the open source community by making Libco available.

* Copyright (C) 2014 THL A29 Limited, a Tencent company. All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License"); 
* you may not use this file except in compliance with the License. 
* You may obtain a copy of the License at
*
*	http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, 
* software distributed under the License is distributed on an "AS IS" BASIS, 
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
* See the License for the specific language governing permissions and 
* limitations under the License.
*/

.globl coctx_swap
#if !defined( __APPLE__ ) && !defined( __FreeBSD__ )
.type  coctx_swap, @function
#endif
coctx_swap:

	movl 4(%esp), %eax // eax is a no 
  movl (%esp), %ebx  //ebx is next ip
  movl %ebx, (%eax)
  movl %esp, 4(%eax)
  movl %ebp, 8(%eax)
  
  movl 8(%esp), %eax // eax is cur co
  movl (%eax), %ebx // move cur co to ebp
  movl 4(%eax), %esp// 
  movl 8(%eax), %ebp// 

  jmp *%ebx
