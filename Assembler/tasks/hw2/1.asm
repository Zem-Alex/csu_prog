stack segment para public
db 16 dup(?)
stack ends


data segment para public

strmax1 db 240 
strlen1 db ?  
strdata1 db 241 dup('$')

strmax2 db 240
strlen2 db ?
strdata2 db 241 dup('$')

strmax3 db 240
strlen3 db ?
strdata3 db 241 dup('$')

enters db 0ah, "$"
input db "Intput:", 0ah, 0dh, "$"
output db "Output:", 0ah, 0dh, "$"

data ends


code segment para public

assume ds:data, ss:stack, cs:code

start:

	mov ax, data
	mov ds, ax
	
	mov ax, stack
	mov ss, ax
	
	mov ah, 09h
	mov dx, offset enters ; Вывод переносов 
	int 21h
	
	mov ah, 09h
	mov dx, offset input ; Вывод input
	int 21h
	
	mov ah, 09h
	mov dx, offset enters ; Вывод переносов
	int 21h
	
	; Cx счетчик, si итератор для смещения
	xor si, si 
	xor cx, cx
	
	mov bx, offset strmax1
	
loop_:
	lea dx, word ptr [bx + si] 
	
	mov ah, 0ah ; Скан строки 
	int 21h
	
	mov ah, 09h
	mov dx, offset enters ; Вывод переносов 
	int 21h
	
	add si, 243; Сдвигаемся итератором на весь размер блока 
	
	inc cx
	cmp cx, 3
	jne loop_

	
	mov ah, 09h
	mov dx, offset enters ; Вывод переносов 
	int 21h
	
	mov ah, 09h
	mov dx, offset output ; Вывод output
	int 21h

	mov ah, 09h
	mov dx, offset enters ; Вывод переносов
	int 21h
	
	;a) Вывод через пробелы
	
	mov dx, offset strmax1
	call printStr
	
	mov ah, 02h
	mov dl, 20h ; Код пробела
	int 21h
	
	mov dx, offset strmax2
	call printStr
	
	mov ah, 02h
	mov dl, 20h ; Код пробела
	int 21h
	
	mov dx, offset strmax3
	call printStr
	
	mov ah, 02h
	mov dl, 20h ; Код пробела
	int 21h

	mov ah, 09h
	mov dx, offset enters ; Вывод переносов
	int 21h
	
	
	mov ah, 09h
	mov dx, offset enters ; Вывод переносов 
	int 21h
	
	;а) через точку с запятой
	
	mov dx, offset strmax1
	call printStr
	
	mov ah, 02h
	mov dl, 59 ; Код точки с запятой
	int 21h
	
	mov dx, offset strmax2
	call printStr
	
	mov ah, 02h
	mov dl, 59 ; Код точки с запятой
	int 21h
	
	mov dx, offset strmax3
	call printStr
	
	mov ah, 02h
	mov dl, 59 ; Код точки с запятой
	int 21h
	
	mov ah, 09h
	mov dx, offset enters
	int 21h
	
	
	mov ah, 09h
	mov dx, offset enters ; Вывод переносов
	int 21h
	
	;б) через перенос строки
	
	mov dx, offset strmax1
	call printStr
	
	mov ah, 02h
	mov dl, 10 ; Перенос
	int 21h
	
	mov dx, offset strmax2
	call printStr
	
	mov ah, 02h
	mov dl, 10 ; Перенос
	int 21h
	
	mov dx, offset strmax3
	call printStr
	
	mov ah, 02h
	mov dl, 10 ; Перенос
	int 21h
	
	mov ah, 09h
	mov dx, offset enters
	int 21h
	
	
	mov ax, 4c00h
	int 21h

printStr proc
	
	; dx - адрес структуры всей строки
	mov bx, dx
	
	xor cx, cx
	mov cl, byte ptr [bx + 1] ; вычисление актуальной длины строки, mov стоит потому что разыменовываем
	
	lea bx, word ptr [bx + 2] ; Начальная точка строки
	
	xor si, si
	mov ah, 02h 
	
for_i:
	mov dl, byte ptr [bx + si]
	int 21h
	inc si
	
	dec cx
	cmp cx, 0
	jne for_i
	
	ret

printStr endp

code ends
end start