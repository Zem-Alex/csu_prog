arg1 equ 4
arg2 equ 6
arg3 equ 8
arg4 equ 10

var1 equ -2
var2 equ -4
var3 equ -6
var4 equ -8
var5 equ -10
var6 equ -12
var7 equ -14

stack segment para stack
db 65530 dup(?)
stack ends

data segment para public
START_X DW 0
END_X DW 160
START_Y DW 0
END_Y DW 100
COLOR DB 2
DIAGONAL_Y_INCREMENT DW ?
DIAGONAL_X_INCREMENT DW ?
SHORT_DISTANCE DW ?
STRAIGHT_X_INCREMENT DW ? 
STRAIGHT_Y_INCREMENT DW ? 
STRAIGHT_COUNT DW ?
DIAGONAL_COUNT DW ? 
data ends

code segment para public 

assume cs:code,ds:data,ss:stack

include strings.inc

_draw_line_brez proc near
    push bp
    mov bp, sp
    sub sp, 14 ; выделяем память для локальных переменных
	
    ;вычисление вертикальной дистанции
	mov di, word ptr [bp + arg4] ;вычитаем координату начальной
	sub di, word ptr [bp + arg3] ;точки из координаты конечной
	jge keep_y ;вперед если наклон < 0

	neg dx ;иначе инкремент равен -1
	neg di ;а дистанция должна быть > 0

keep_y: 
	mov word ptr [bp + var1], dx
	;вычисление горизонтальной дистанции
	mov si, word ptr [bp + arg2] ;вычитаем координату начальной
	sub si, word ptr [bp + arg1] ;точки из координаты конечной
	jge keep_x ;вперед если наклон < 0
	neg cx ;иначе инкремент равен -1
	neg si ;а дистанция должна быть > 0

keep_x: 
	mov word ptr [bp + var1], cx ; diagonal_y_increment
	
	;определяем горизонтальны или вертикальны прямые сегменты
	cmp si, di ;горизонтальные длиннее?
	jge horz_seg ;если да, то вперед
	mov cx, 0 ;иначе для прямых x не меняется
	xchg si, di ;помещаем большее в cx
	jmp save_values;сохраняем значения

horz_seg: 
	mov dx,0 ;теперь для прямых не меняется y
save_values: 
	
	mov word ptr [bp + var2], di ;меньшее расстояние      [short_distance]
	mov word ptr [bp + var3], cx ;один из них 0,
	mov word ptr [bp + var4], dx ;а другой - 1.
	;вычисляем выравнивающий фактор
	mov ax, word ptr [bp + var2] ;меньшее расстояние в ax
	shl ax, 1 ;удваиваем его
	mov word ptr [bp + var5], ax ;запоминаем его
	sub ax, si ;2*меньшее - большее
	mov bx, ax ;запоминаем как счетчик цикла
	sub ax, si ;2*меньшее - 2*большее
	mov word ptr [bp + var6], ax ;запоминаем
	;подготовка к выводу линии
	mov dx, word ptr [bp + arg1] ;начальная координата x
	mov cx, word ptr [bp + arg3] ;начальная координата y
	inc si ;прибавляем 1 для конца
	mov al, color ;берем код цвета
	
	;теперь выводим линию
mainloop: 
	dec si ;счетчик для большего расстояния
	jz line_finished ;выход после последней точки
	
	mov ah,12 ;функция вывода точки
	int 10h ;выводим точку
	
	cmp bx,0 ;если bx < 0, то прямой сегмент
	jge diagonal_line ;иначе диагональный сегмент
	;выводим прямые сегменты
	add cx, word ptr [bp + var3] ;определяем инкре-
	add dx, word ptr [bp + var4] ;менты по осям
	add bx, word ptr [bp + var5] ;фактор выравнивания
	jmp mainloop ;на следующую точку
	
	;выводим диагональные сегменты
diagonal_line: 
	add dx, word ptr [bp + var1] ;менты по осям
	add bx, word ptr [bp + var6] ;фактор выравнивания
	jmp mainloop ;на следующую точку


    
    mov sp, bp
    pop bp
    ret
_draw_line_brez endp  
    
start:
    mov ax, data
    mov ds, ax
    mov ax, stack
    mov ss, ax
    
	;установка режима дисплея
	mov ah, 0 ;функция установки режима
	mov al, 4h ;цветной 320*200
	int 10h ;установка режима

	;установка начальных инкрементов для каждой позиции точки
	mov cx, 1 ;инкремент для оси x
	mov dx, 1 ;инкремент для оси y

	mov dx, 199 ; END_Y
    push dx
    mov dx, 0; START_Y
    push dx
    mov dx, 319 ; END_X
    push dx
	mov dx, 0 ; START_X
	push dx
	call _draw_line_brez
	add sp, 8
	
	
  line_finished:
	call _getchar ; ждём ввод
	
	;установка режима дисплея
	mov ah,0 ;функция установки режима
	mov al,2 ;текстовый 80*25
	int 10h ;установка режима
    
    call _exit0
	
code ends

end start