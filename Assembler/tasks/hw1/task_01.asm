stack segment para stack
    db 256 dup(?)
stack ends

data segment para public
    input db 1
data ends

code segment para public
assume cs:code, ds:data, ss:stack

start:
    mov ax, data 
    mov ds, ax

    mov ax, stack
    mov ss, ax
	

    mov ah, 01h
    int 21h

    mov [input], al

    mov dl, [input]
    mov ah, 02h 
    int 21h

    mov al, 0
    mov ah, 4ch
    int 21h

code ends
end start
