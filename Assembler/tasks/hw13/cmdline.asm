arg1 equ 4
arg2 equ 6
arg3 equ 8
arg4 equ 10

var1 equ -2
var2 equ -4
var3 equ -6
var4 equ -8

stack segment para stack
db 65530 dup(?)
stack ends

data segment para public

str1 db 256 dup(?)
str2 db "Hello, World!", 0
strmax db 255 
strlen db 0
string db 256 dup (?)
enters db 0dh, 0ah, "$"

data ends

code segment para public 

assume cs:code,ss:stack

; void print_args(int cur_ds)
_print_args:
    push bp
    mov bp, sp
    
    ; восстанавливаем PSP
    mov ah, 62h
    int 21h
    mov ds, bx
    
    xor cx, cx
	xor ax, ax
	mov bx, 80h
    mov cl, byte ptr ds:[80h]   ; size of parameter string
	mov di, offset string
	
 for_i:
	cmp cl, 0
	je for_i_end
	dec cl
	inc bx
	mov al, byte ptr ds:[bx]
	mov byte ptr [di], al
	inc di
	jmp for_i
 for_i_end:
 
	mov byte ptr [di+1], '$'
	mov di, offset string
	mov cl, byte ptr ds:[80h]
	xor dx, dx
	mov ah, 02h
	
 write_string:
    cmp cl, 0
	je write_string_end
	dec cl
	mov dl, byte ptr [di] 
	cmp dl, ' '
	jne print_
	mov dl, 0ah
 print_:	
    mov ah, 02h
    int 21h
	inc di
	jmp write_string
 write_string_end:
	
    ;mov ah, 40h                 ; write
    ;mov bx, 1                   ; ... to standard output
    ;mov dx, 81h                 ; ... the parameter string
    ;int 21h                     ; ... by calling DOS
    call _putnewline
    
    ; восстанавливаем исходный ds
    mov ds, word ptr [bp + arg1]
    
    mov sp, bp
    pop bp
    ret

include strings.inc
 
start:
    mov ax, data
    mov ds, ax
    mov ax, stack
    mov ss, ax
    
    push ds
    call _print_args
    add sp, 2
    
    mov dx, offset str2
    push dx
    call _putstr
    add sp, 2
    call _putnewline
    
    call _exit0
code ends

end start