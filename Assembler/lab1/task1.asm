; шаблон для зачётного задания №1 (калькулятор) с использованием стековых фреймов
; Д.И. Панасенко 11.04.2020

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
strnum1 db 256 dup(?)
stroperation db 1 dup(?)
strnum2 db 256 dup(?)
strnumres db 256 dup(?)
num dw ?       ; число
num1 dw ?
num2 dw ?
numres dw ?
error_message_invalid_format db "Error: incorrect string format", 0
error_message_invalid_format2 db "!", 0
data ends

code segment para public 

assume cs:code,ds:data,ss:stack

; void putchar(int c)
; выводит символ на экран (младший байт переданного аргумента)
_putchar:
    push bp
    mov bp, sp
    
    mov dx, word ptr [bp + arg1]
    mov ah, 02h
    int 21h
    
    mov sp, bp
    pop bp
    ret
    
; int getchar()
; читает символ с клавиатуры и возвращает его (считанный символ - младший байт регистра ax)
_getchar:
    push bp
    mov bp, sp
    
    mov ah, 01h
    int 21h
    
    mov sp, bp
    pop bp
    ret

; int strlen(const char *str)
; находит длинну строки (до завершающего нуля), адрес которой является аргументом
_strlen: 
    push bp
    mov bp, sp
    
    mov bx, word ptr [bp + arg1] 
    xor ax, ax ; счётчик (ax)

lencyc:    
    cmp byte ptr [bx], 0
    je lenret
    inc ax
    inc bx
    jmp lencyc
    
lenret:    
    mov sp, bp
    pop bp
    ret
    
; void putstr(const char *str)
; выводит строку на экран (до завершающего нуля), адрес которой передан в качестве аргумента
_putstr: 
    push bp
    mov bp, sp
    
    ; находим длину строки
    push word ptr [bp + arg1] 
    call _strlen
    add sp, 2
    
    ; выводим строку
    mov cx, ax
    mov dx, word ptr [bp + arg1]
    mov ah, 40h
    mov bx, 1
    int 21h
    
    mov sp, bp
    pop bp
    ret
    
; void getstr(const char *str, int max_len)
; читает строку с клавиатуры (либо max_len байт, либо до перевода строки) и сохраняет её в память, 
; при этом дописывает в конец строки завершающий 0
_getstr:
    push bp
    mov bp, sp
    
    ; чтение строки
    mov cx, word ptr [bp + arg2]
    mov dx, word ptr [bp + arg1]
    mov ah, 3fh
    mov bx, 0
    int 21h
    
    ; добавление в конец завершающего нуля
    mov bx, word ptr [bp + arg1]
    add bx, ax ; добавляем к адресу начала строки длину считанной строки
    sub bx, 2 ; убираем из строки возврат каретки (\r) и перевод строки (\n)
    mov byte ptr [bx], 0

    mov sp, bp
    pop bp
    ret

; void putnewline()
; выводит на экран возврат каретки (\r) и перевод строки (\n), т.е. переводит вывод на новую строку
_putnewline:
    push bp
    mov bp, sp
    
    mov dx, 10
    push dx
    call _putchar
    add sp, 2
    
    mov dx, 13
    push dx
    call _putchar
    add sp, 2
    
    mov sp, bp
    pop bp
    ret

; void exit(int code)
; завершает работу программы с кодом, переданным в качетве аргумента (кодом является младший байт аргумента)  
_exit:
    push bp
    mov bp, sp
    
    mov ax, word ptr [bp + arg1]
    mov ah, 4ch
	int 21h
    
    mov sp, bp
    pop bp
    ret
    
; void exit0()
; завершает работу программы с кодом 0 
_exit0:
    push bp
    mov bp, sp
    
    mov dx, 0
    push dx
    call _exit
    add sp, 2
    
    mov sp, bp
    pop bp
    ret
    
; int atoi(const char *str, strlen) 
; функция перевода строки в число
_atoi: 
    xor di, di          ; обнуляем регистр с результатом
	mov dx, 10			; будем умножать на 10
    mov cx, si          ; загружаем длину строки
    mov si, bx          ; загружаем адрес строки
	mov bx, 0
atoi_loop:
    mov al, byte ptr [si]   ; загружаем текущий символ строки
    cmp al, 0Dh         ; проверяем, что символ это перенос строки
    jl atoi_done        ; если нет, то переходим к завершению функции
	sub al, '0'         ; вычитаем из текущего символа код нуля
	mov bx, cx          ; сохраняем кол-во разрядов
	cmp cx, 1
	je for4ik_skip_
for4ik_:				; разряды числа
    mul dx              ; умножаем результат на 10
	mov dx, 10
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

; void itoa(int num, char *str)
; функция перевода числа в строку    
_itoa: 
    push bp
	mov bp, sp
	sub sp, 10
	
	mov di, word ptr [bp+arg1] ; число
	mov si, word ptr [bp+arg2] ; буфер
	mov cx, 0
	mov bx, 10
	
	mov ax, di ; число в ax
	loop_b:
		mov dx, 0
		div bx

		add dl, '0'
		
		mov byte ptr [si], dl
		
		inc si
		inc cx
		cmp ax, 0
		jne loop_b
	
	mov al, 0 ; количество цифр
	mov ah, 0 ; нулевой символ окончания строки
	mov byte ptr [si], ah ; добавить нулевой символ в конец строки
	
	
	mov si, word ptr [bp+arg2]
	mov di, cx
	for_1_:
		push [si]
		dec di
		inc si
		cmp di, 0
		jne for_1_
	mov di, cx
	mov si, word ptr [bp+arg2]
	for_2_:
		pop [si]
		dec di
		inc si
		cmp di, 0
		jne for_2_
	mov byte ptr [si], ah
	
	mov sp, bp
	pop bp
	ret

; int check(const char *input_line)    
; функция проверки введённой строки на соответствие формату
; функция возвращает 1, если строка удовлетворяет формату, иначе возвращает 0
; при выполнении дополнительного задания, функция также выводит сообщение об ошибке    
_check: 
    push bp
    mov bp, sp
    
	; Сохраняем регистры, которые будут использоваться
    push ax
    push bx
    push cx

    

	mov dx, word ptr [bp + arg1]
	push dx
	
	call _strlen ; ax == strlen
	add sp, 2
	
	; add ax, '0'
	; push ax
	; call _putchar ; проверка длины
	; add sp, 2
	
	
	xor dx, dx
	push di
	xor di, di
	

	mov bx, word ptr [bp + arg1] ; Адрес строки
	mov di, offset strnum1
	

    ; Проверяем первое число
    mov cl, byte ptr [bx] ; Получаем первый символ строки
	
	;записываем первый символ в strnum1
	mov dx, [bx]
	mov [di], dx
	
    cmp cl, '-' ; Проверяем, является ли первый символ знаком "-"
    je check_digit ; Если знак "-", переходим к проверке числа

    cmp cl, '0' ; Проверяем, является ли первый символ цифрой
    jl skip ; Если первый символ не цифра, строка некорректна
	
  
	
    cmp cl, '9'
    jg skip; Если первый символ не цифра, строка некорректна

	
  check_digit:
	dec ax
    inc bx ; Переходим ко следующему символу
    mov cl, byte ptr [bx] ; Получаем следующий символ строки

    cmp cl, ' ' ; Проверяем, является ли символ знаком " "
    je check_operation ; Если знак " ", переходим к проверке операции

	;записываем символ в strnum1
	inc di
	mov dx, [bx]
	mov [di], dx
	
    cmp cl, '0' ; Проверяем, является ли символ цифрой
    jl check_invalid ; Если символ не цифра, строка некорректна
    cmp cl, '9'
    jg check_invalid ; Если символ не цифра, строка некорректна
	
	jmp check_digit


  check_operation:
	dec ax
    inc bx ; Переходим к четвертому символу
    mov cl, byte ptr [bx] ; Получаем следующий символ строки(после первого пробела)

	
	mov di, offset stroperation	
	mov dx, [bx]
	mov [di], dx
    cmp cl, '+' ; Проверяем, является ли операцией сложения
    je check_space ; Если операция допустима, переходим к проверке пробела

    cmp cl, '-' ; Проверяем, является ли операцией вычитания
    je check_space ; Если операция допустима, переходим к проверке пробела
	
	cmp cl, '*' ; Проверяем, является ли операцией вычитания
    je check_space ; Если операция допустима, переходим к проверке пробела
	
	cmp cl, '/' ; Проверяем, является ли операцией вычитания
    je check_space ; Если операция допустима, переходим к проверке пробела
	
	cmp cl, '%' ; Проверяем, является ли операцией вычитания
    je check_space ; Если операция допустима, переходим к проверке пробела

    jmp check_invalid ; Если операция не допустима, строка некорректна

  check_space:
	dec ax
    inc bx ; Переходим к следующему символу (после знака операции)
    mov cl, byte ptr [bx] ; Получаем символ строки

    cmp cl, ' ' ; Проверяем, является ли символ пробелом
    je check_minus_sign ; Если пробел, переходим к проверке второго числа

    jmp check_invalid ; Если символ не пробел, строка некорректна

		 skip:
	   jmp check_invalid ; far
  check_minus_sign:
    mov di, offset strnum2
	
	dec ax
	inc bx ; Переходим к следующему символу
    mov cl, byte ptr [bx] ; Получаем следующий символ строки

	mov dx, [bx]
	mov [di], dx
	
    cmp cl, '-' ; Проверяем, является ли символ знаком "-"
    je check_digit2 ; Если знак "-", переходим к проверке самого числа
	
	cmp cl, '0' ; Проверяем, является ли символ цифрой
    jl check_invalid ; Если символ не цифра, строка некорректна
	
    cmp cl, '9'
    jg check_invalid ; Если символ не цифра, строка некорректна
	
  check_digit2:  
	dec ax
	
    inc bx ; Переходим к следующему символу
    mov cl, byte ptr [bx] ; Получаем следующий символ строки

	cmp ax, 1 ; Проверяем, не закончилась ли строка
    jl check_end ; Если  символ не цифра, строка некорректна
	
	inc di
	mov dx, [bx] ; 
	mov [di], dx
	
    cmp cl, '0' ; Проверяем, является ли символ цифрой
    jl check_invalid ; Если  символ не цифра, строка некорректна
    cmp cl, '9'     
    jg check_invalid ; Если символ не цифра, строка некорректна
	
	jmp check_digit2 ; Если знак "-", переходим к концу проверки
  
 
  check_invalid:
    ; Выводим сообщение об ошибке и возвращаем 0
    mov dx, offset error_message_invalid_format
    push dx
    call _putstr
    add sp, 2
    xor ax, ax ; Возвращаем 0
	jmp check_cleanup
  
  check_end:
  
    mov ax, 1 ; Возвращаем 1 (успешное выполнение)
    jmp check_cleanup

	
check_cleanup:
    ; Восстанавливаем регистры
    pop cx
    pop bx

    
    mov sp, bp
    pop bp
    ret

; void calc()    
; функция калькулятора (вызывает нужные функции: чтения строки, проверки строки, 
; перевода строк в числа, выполнения математической операции и вывода результата) 
_calc: 
    push bp
    mov bp, sp
    
	;получаем строку
	mov dx, 20
	push dx
	mov dx, offset str1
	push dx
	call _getstr
	add sp, 4
	
	
	
	;проверяю итоа
	; mov dx, offset str3
	; push dx
	; mov dx, num
	; push dx
	; call _itoa
	; add sp, 4
	
	;вывожу итоа
	; mov dx, offset str3
	; push dx
	; call _putstr
	; add sp, 2
	
	; call _putnewline
	
	;проверки строки на соответсвие формату
	mov dx, offset str1
	push dx
	call _check
	add sp, 2
	
	;выводим строку (для отладки)
	mov dx, offset strnum1
	push dx
	call _putstr
	add sp, 2
	
	;выводим операцию
	xor ax, ax
	mov di, offset stroperation
	mov dl, byte ptr [di]  
	mov ah, 02h
	int 21h
	
	;выводим строку (для отладки)
	mov dx, offset strnum2
	push dx
	call _putstr
	add sp, 2
	
	call _putnewline
	
	
	; размер первого числа
	mov dx, offset strnum1
	push dx
	call _strlen
	add sp, 2
	
	;atoi первого числа вырванного из исходной строки
	dec ax
	mov si, ax
	mov bx, offset strnum1
	call _atoi
	mov word ptr [num1], di	
	;add word ptr [num1], 2
	
	;проверяю итоа
	mov dx, offset strnum1
	push dx
	mov dx, num1
	push dx
	call _itoa
	add sp, 4
	
	;выводим строку (для отладки)
	mov dx, offset strnum1
	push dx
	call _putstr
	add sp, 2
	
	call _putnewline
	
	;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	; размер второго числа
	mov dx, offset strnum2
	push dx
	call _strlen
	add sp, 2
	
	;atoi второга числа вырванного из исходной строки
	;dec ax
	mov si, ax
	mov bx, offset strnum2
	call _atoi
	mov word ptr [num2], di	
	;add word ptr [num2], 2
	
	;проверяю итоа
	mov dx, offset strnum2
	push dx
	mov dx, num2
	push dx
	call _itoa
	add sp, 4
	
	;выводим строку (для отладки)
	mov dx, offset strnum2
	push dx
	call _putstr
	add sp, 2
	
	
	;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!получили числа как инты, далее операции над ними!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	call _putnewline
	
	mov dx, offset stroperation
	push dx
	mov dx, num2
	push dx
	mov dx, num1
	push dx
	call _operation_func
	add sp, 6
	
	mov word ptr [numres], di	
	
	;проверяю итоа
	mov dx, offset strnumres
	push dx
	mov dx, numres
	push dx
	call _itoa
	add sp, 4
	
	;выводим строку (для отладки)
	mov dx, offset strnumres
	push dx
	call _putstr
	add sp, 2
	
    mov sp, bp
    pop bp
    ret

;void _operation_func(int num1, int num2, char operation)
;результат пусть будет в di
_operation_func:
	push bp
    mov bp, sp
	
	mov ax, word ptr [bp + arg1]
	mov bx, word ptr [bp + arg3]
	mov cx, [bx]
	
	cmp cl, '+'
	jne _next_op
	add ax, word ptr [bp + arg2]
  _next_op:
  
    cmp cl, '-'
	jne _next_op2
	sub ax, word ptr [bp + arg2]
  _next_op2:
  
    cmp cl, '*'
	jne _next_op3
	mov bx, word ptr [bp + arg2]
	imul bx
  _next_op3:
  
    cmp cl, '/'
	jne _next_op4
	mov dx, 0
	mov bx, word ptr [bp + arg2]
	idiv bx
  _next_op4:
  
    cmp cl, '%'
	jne _the_end
	mov dx, 0
	mov bx, word ptr [bp + arg2]
	idiv bx
	mov ax, dx
  _the_end:

  
	mov di, ax
	
	mov sp, bp
    pop bp
    ret




start: ; вызов функции calc (модифицировать главную функцию программы не требуется)
    mov ax, data
    mov ds, ax
    mov ax, stack
    mov ss, ax
    
    call _calc

	call _exit0
code ends

end start