stack segment para stack
db 256 dup(?)
stack ends

data segment para public
newline db 0Dh, 0Ah
digits db "0123456789"
var dw 0
num1 dw ?            ; число
snum1 db 15 dup(?)   ; строка для храниния числа
lnum1 dw ?           ; длина строки с числом
num2 dw 13555       ; число 65535 
snum2 db 15 dup(?)   ; строка для храниния числа
lnum2 dw ?           ; длина строки с числом
data ends

code segment para public

assume cs:code,ds:data,ss:stack

atoi: ; в регистре bx - адрес строки c числом, в регистре si - длина числа, функция возвращает в регистре di полученное число
    xor di, di          ; обнуляем регистр с результатом
    mov cx, si          ; загружаем длину строки
    mov si, bx          ; загружаем адрес строки
	mov bx, 0
atoi_loop:
	mov dx, 16			; будем умножать на 10/16
	mov al, byte ptr [si]   ; загружаем текущий символ строки
    cmp al, 0Dh         ; проверяем, что символ это перенос строки
    jl atoi_done        ; если нет, то переходим к завершению функции
	
	cmp al, 'a'
	jl _16_skip_
	
	mov dx, 16
	sub al, 'a'
	add al, 10
	jmp _10_skip_
	
  _16_skip_:
  
	sub al, '0'         ; вычитаем из текущего символа код нуля

  _10_skip_:
    mov bx, cx          ; сохраняем кол-во разрядов
	cmp cx, 1
	je for4ik_skip_
for4ik_:				; разряды числа
    mul dx              ; умножаем результат на 10
	mov dx, 16
	dec bx
	cmp bx, 1
	jne for4ik_
for4ik_skip_:

    add di, ax          ; добавляем к результату значение текущей цифры
	xor ax, ax
    inc si              ; переходим к следующему символу
    loop atoi_loop      ; повторяем до конца строки
atoi_done:	
    ret

	
	
	
itoa: ; в регистре ax - число, в регистре bx - адрес строки для числа, в регистре si - адрес длины строки для числа
	push ax
	push bx
	push cx
	push dx
	push si
	push di

	mov si, offset snum2 ; загрузить указатель на буфер
	mov cx, 0 ; количество цифр
	mov bx, 16 ; основание системы счисления

	itoa_loop:
	mov dx, 0
	div bx ; разделить на 16
	
	cmp dl, 10
	jl _16_skip_2
	
	add dl, 'a'
	sub dl, 10
	jmp _10_skip_2
	
  _16_skip_2:

  
	add dl, '0' ; преобразовать остаток в ASCII-цифру
	
  _10_skip_2:
	
	mov byte ptr [si], dl ; сохранить цифру в буфере

	inc si ; увеличить указатель на буфер
	inc cx ; увеличить счетчик цифр
	cmp ax, 0
	jnz itoa_loop ; повторять до тех пор, пока частное не станет равным нулю

	mov al, 0 ; количество цифр
	mov ah, '$' ; нулевой символ окончания строки
	mov byte ptr [si], ah ; добавить нулевой символ в конец строки

	mov si, offset snum2
	mov di, cx
	for_1_:
		push [si]
		dec di
		inc si
		cmp di, 0
		jne for_1_
	mov di, cx
	mov si, offset snum2
	for_2_:
		pop [si]
		dec di
		inc si
		cmp di, 0
		jne for_2_
	mov byte ptr [si], ah
	
	pop di
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
    ret

	
	
	
pcharf: ; в dl до вызова функци помещён код символа
    mov ah, 02h
    int 21h
    ret

pstrf: ; в dx уже лежит адрес строки, а в cx - её длина
    mov ah, 40h
    mov bx, 1
    int 21h
    ret

sstrf: ; в dx уже лежит адрес строки, а в cx - её максимальная длина
    mov ah, 3fh
    mov bx, 0
    int 21h
    ; длина строки в ax (для отсечение первода строки и возрата каретки - уменьшить ax на 2)
    dec ax
    dec ax
    ret

pnewf:
    mov dx, offset newline
    mov cx, 2
    call pstrf
    ret

exit0f:
    mov ah, 4ch
    mov al, 00h
	int 21h
    ret

start:
    mov ax, data
    mov ds, ax
    mov ax, stack
    mov ss, ax
    
    mov dx, offset snum1
    mov cx, 15
    call sstrf
    mov word ptr [lnum1], ax
    
    mov bx, offset snum1
    mov si, word ptr [lnum1]
    call atoi
    mov word ptr [num1], di	
	add word ptr [num1], 1
	
	the_loop:		
		;Преобразовать целое число в строку ASCII-символов
		mov ax, num1
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
	
	

    mov ax, word ptr [num2]
    mov bx, offset snum2
    mov si, offset lnum2
    call itoa
	
    call pnewf
    
	; Вывод полученной строки
	mov ah, 09h
	mov dx, offset snum2
	int 21h

	call exit0f
code ends

end start