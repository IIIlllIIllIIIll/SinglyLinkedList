global linked_list_add
global linked_list_append
global linked_list_remove
global linked_list_pop

extern printf
extern malloc
extern free

default rel

section .data
    negative_one: dq -1

section .text

%macro pushaq 0
    push    r12
    push    r13
    push    r14
    push    r15
    
    push    rdi
    push    rsi
    push    rbx
    push    rbp
%endmacro # pushaq

%macro popaq 0
    pop     rbp
    pop     rbx
    pop     rsi
    pop     rdi

    pop     r15
    pop     r14
    pop     r13
    pop     r12
%endmacro # popaq

linked_list_add:
    pushaq
    mov     rbp, rsp
    sub     rsp, 0x8

    ; push    rcx ; 1
    ; push    rdx ; 2
    ; push    r8  ; 3

    mov     rax, -1
    
    cmp     rcx, 0
    je      return

    cmp     r8, -1
    jl      return
    jg      positive

negative:
    cmp     qword [rcx], 0
    je      push_node
    mov     rcx, [rcx]
    jmp     negative

positive:
    cmp     r8, 0
    je      push_node

    mov     rcx, [rcx]
    dec     r8

    cmp     rcx, 0
    je      return

    jmp     positive

push_node:
    push    rcx
    push    rdx
    sub     rsp, 0x28

    mov     rcx, 16
    call    malloc
    cmp     rax, 0
    cmove   rax, [negative_one]
    je      return

    add     rsp, 0x28
    pop     rdx
    pop     rcx
    
    mov     r8, [rcx]
    mov     [rax], r8
    mov     [rax+8], rdx
    mov     [rcx], rax

    xor     rax, rax
    jmp     return

linked_list_append:
    mov     r8, -1
    jmp     linked_list_add


linked_list_remove:
    pushaq
    mov     rbp, rsp
    sub     rsp, 0x8

    ; push    rcx ; 1
    ; push    rdx ; 2

    xor     rax, rax
    
    cmp     rcx, 0
    je      return

    cmp     rdx, -1
    jl      return
    jg      remove_location

    cmp     qword [rcx], 0
    je      return
remove_last:
    mov     r8, [rcx]
    cmp     qword [r8], 0
    je      remove_node
    mov     rcx, r8
    jmp     remove_last

remove_location:    
    cmp     rdx, 0
    je      remove_node

    mov     rcx, [rcx]
    dec     rdx

    cmp     rcx, 0
    je      return

    jmp     remove_location


remove_node:
    mov     r8, [rcx]
    cmp     r8, 0
    je      return

    mov     rdx, [r8]

    mov     [rcx], rdx
    mov     rax, r8
    jmp     return


linked_list_pop:
    mov     rdx, -1
    jmp     linked_list_remove

return:
    mov     rsp, rbp
    popaq
    ret
