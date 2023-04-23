data segment
	;msg db '$'
    number dw 0 ; целое число
	enters db 0dh, 0ah, "$"
	probel db 20h, "$" 
data ends

code segment
    assume cs:code, ds:data
start:
    mov ax, data
    mov ds, ax ; загрузить сегмент данных
    
	mov si, 256
	mov di, 8 ; загрузить число в регистр DI
the_loop:		
		; Преобразовать целое число в строку ASCII-символов
		mov ax, number
		inc number
		mov cx, 0 ; количество цифр
		mov bx, 10 ; основание системы счисления
		
	int2str_loop:
		xor dx, dx
		div bx ; разделить на 10
		
		add dl, '0' ; преобразовать остаток в ASCII-цифру
		push dx ; сохранить цифру в стеке
		inc cx ; уменьшить счетчик цифр
		cmp ax, 0 ; test ax, ax
		jnz int2str_loop ; повторять до тех пор, пока частное не станет равным нулю		
	
	int2str_print:
		pop dx ; получить цифру из стека
		mov ah, 02h
		int 21h ; вывести цифру на экран
		loop int2str_print ; повторять для всех цифр
		
		mov ax, number
		xor dx, dx
		div di
		
		cmp dx, 0
		jne metka_probel
		
		mov dx, 58 ; :s
		mov ah, 02h 
		int 21h 
		
		mov dx, offset probel
		mov ah, 09h 
		int 21h 
		
		mov dx, number ; symbol
		mov ah, 02h 
		int 21h 
		
		mov dx, offset enters
		mov ah, 09h 
		int 21h 
		
		jmp metka_exit
		
	metka_probel:	
		mov dx, 58 ; :
		mov ah, 02h 
		int 21h 
		
		mov dx, offset probel
		mov ah, 09h 
		int 21h 
		
		mov dx, number ; symbol
		mov ah, 02h 
		int 21h 
		
		mov dx, offset probel
		mov ah, 09h 
		int 21h 
		
	 metka_exit:   	
	
		dec si
		cmp si, 0
		jne the_loop 

    metka:
    mov ax, 4c00h ; завершить программу с кодом 0
    int 21h
code ends
end start