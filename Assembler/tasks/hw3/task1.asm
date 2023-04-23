stack segment para stack
    db 256 dup(?) 
stack ends

data segment para public
    input db 240 dup("$")
    enters db 0dh, 0ah, "$"
	probel db 20h, "$" 
data ends

code segment para public
assume cs:code, ds:data, ss:stack

start:
    mov ax, data 
    mov ds, ax

    mov ax, stack 
    mov ss, ax

    mov cx, 0
	
	mov bx, offset [input]

read_loop:
    mov ah, 01h
    int 21h
	
	mov byte ptr [bx], al 
	
	inc bx
	inc cx	
	
	cmp al, 0Dh
	jne read_loop

	mov bx, offset [input]
	
	mov dx, offset enters
    mov ah, 09h 
    int 21h 
	
write_loop:
	mov si, cx
	mov dl, byte ptr [bx+si-1] 
	mov ah, 02h
    int 21h
	
	dec cx

	cmp cx, 0
    jne write_loop

	
	mov dx, offset enters
    mov ah, 09h 
    int 21h 
	
	mov cx, 10
write_n_times:

	mov dx,offset input
	mov ah,09h
	int 21h
	
    mov dx,offset enters
	mov ah,09h
	int 21h
	
	loop write_n_times
	
	
    mov al, 0 
    mov ah, 4ch 
    int 21h 

code ends
end start