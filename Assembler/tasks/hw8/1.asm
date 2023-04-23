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
k dw 100
data ends

code segment para public 

assume cs:code,ds:data,ss:stack

include strings.inc
    
; void setmode(int mode)
; установка видеорежима (номер режима в младшем байте аргумента)    
_setmode proc near
    push bp
    mov bp, sp
    
    mov ax, word ptr [bp + arg1]
    mov ah, 00h
    int 10h
    
    mov sp, bp
    pop bp
    ret
_setmode endp 

; void drawpixel(int row, int column, int color)
; рисование пикселя (код цвета в младшем байте аргумента)    
_drawpixel proc near
    push bp
    mov bp, sp
    
    mov bh, 0
    mov dx, word ptr [bp + arg1]
    mov cx, word ptr [bp + arg2]
    mov ax, word ptr [bp + arg3]
    mov ah, 0ch
    int 10h
    
    mov sp, bp
    pop bp
    ret
_drawpixel endp  
    
start:
    mov ax, data
    mov ds, ax
    mov ax, stack
    mov ss, ax

    ; Переходим в графический режим 320х200
    mov dx, 04h
    push dx
    call _setmode
    add sp, 2
    
	mov di, 0
	
loop_horisontal:
    ; Отображение пикселей
    mov dx, 0Eh ; color
    push dx
    mov dx, di; x
    push dx
    mov dx, 25 ; y
    push dx
    call _drawpixel
    add sp, 6
	
    inc di
	cmp di,k
	jne loop_horisontal
	
	mov di, 0
	
loop_vertical:
    ; Отображение пикселей
    mov dx, di ; color
    push dx
    mov dx, 25; x
    push dx
    mov dx, di ; y
    push dx
    call _drawpixel
    add sp, 6
	
    inc di
	cmp di,k
	jne loop_vertical
	
	
    
    call _getchar
  
    ; Переходим в текстовый режим 80х25
    mov dx, 02h
    push dx
    call _setmode
    add sp, 2
    
    call _exit0
code ends

end start