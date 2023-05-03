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

_draw_line_x proc near
	push bp
    mov bp, sp
	mov si, word ptr [bp + arg1]
loop_horisontal:
    ; Отображение пикселей
    
    mov bh, 0
    mov dx, word ptr [bp + arg2]
    mov cx, word ptr [bp + arg3]
    mov ax, word ptr [bp + arg4]
	add cx, si
    mov ah, 0ch
    int 10h
	
    dec si
	cmp si,0
	jne loop_horisontal
	
	mov sp, bp
    pop bp
    ret
_draw_line_x endp  
    
	
	
_draw_line_y proc near
	push bp
    mov bp, sp
	mov si, word ptr [bp + arg1]
loop_vertical:
    ; Отображение пикселей
    
    mov bh, 0
    mov dx, word ptr [bp + arg2]
    mov cx, word ptr [bp + arg3]
    mov ax, word ptr [bp + arg4]
	add dx, si
    mov ah, 0ch
    int 10h
	
    dec si
	cmp si,0
	jne loop_vertical
	
	mov sp, bp
    pop bp
    ret
_draw_line_y endp  
	
	
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
    
	
	mov dx, 0Eh ; color
    push dx
    mov dx, 25; x
    push dx
    mov dx, 25 ; y
    push dx
	mov dx, k ; Количесвто
	push dx
	call _draw_line_x
	add sp, 8
	
	mov di, 0
	
	mov dx, 0Eh ; color
    push dx
    mov dx, 25; x
    push dx
    mov dx, 25 ; y
    push dx
	mov dx, k ; Количесвто
	push dx
	call _draw_line_y
	add sp, 8
	
	
    call _getchar
  
    ; Переходим в текстовый режим 80х25
    mov dx, 02h
    push dx
    call _setmode
    add sp, 2
    
    call _exit0
code ends

end start