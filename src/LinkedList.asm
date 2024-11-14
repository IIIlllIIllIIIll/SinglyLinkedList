global linked_list_add
global linked_list_append
global linked_list_remove
global linked_list_pop

section .data

section .text

extern printf
extern malloc
extern free

linked_list_add:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 16

    ; push    rcx ; 1
    ; push    rdx ; 2
    ; push    r8  ; 3
    mov       [rbp], rdx

    mov     rax, -1
    
    cmp     rcx, 0
    je      return

    cmp     r8, 0
    je      push_node
    jg      positive

negative:
    cmp     qword [rcx], 0
    je      push_node
    mov     rcx, [rcx]
    jmp     negative

positive:
    mov     rcx, [rcx]
    dec     r8

    cmp     rcx, 0
    je      return

    cmp     r8, 0
    je      push_node

    jmp     positive

push_node:
    mov     [rbp-8], rcx

    mov     rcx, 16
    push    rcx
    call    malloc
    mov     rdi, rax
    cmp     rax, 0
    mov     rax, -1
    je      return

    mov     rdx, [rbp]
    mov     rcx, [rbp-8]
    
    mov     r8, [rcx]
    mov     [rdi], r8
    mov     [rdi+8], rdx
    mov     [rcx], rdi

    xor     rax, rax

return:
    mov     rsp, rbp
    pop     rbp
    ret

linked_list_append:
    mov     r8, -1
    jmp     linked_list_add


linked_list_remove:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 0

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
    cmp     rcx, 0
    je      return

    cmp     rdx, 0
    je      remove_node
    
    mov     rcx, [rcx]
    dec     rdx

    jmp     remove_location


remove_node:
    mov     r8, [rcx]
    mov     rdx, [r8]
    mov     [rcx], rdx
    mov     rax, r8
    jmp     return


linked_list_pop:
    mov     rdx, -1
    jmp     linked_list_remove
