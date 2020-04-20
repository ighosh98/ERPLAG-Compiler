extern malloc
extern printf
extern scanf
extern exit

SECTION .data
bound_error_str: db 'RUNTIME ERROR: Array Index Out of Bounds',10,0
input_arr_int: db 'Input: Enter %d array elemts of integer type for range %d to %d',10,0
input_arr_boolean: db 'Input: Enter %d array elemts of boolean type for range %d to %d',10,0
input_str_int: db 'Input: Enter an integer value',10,0
input_str_boolean: db 'Input: Enter a boolean value',10,0
input_format_int: db '%d',0
true_output: db 'Output: true',10,0
false_output: db 'Output: false',10,0
integer_output: db 'Output: %d',10,0
output_str: db 'Output: ',0
single_int: db '%d ',0
single_false: db 'false ',0
single_true: db 'true ',0
nextline: db 10,0

SECTION .text
bits 32
global main

main:
	sub esp,36  ;allocating space on the stack
	mov ebp, esp	;ebp accesses upwards, while stack grows downwards
	pushad
	push dword 20
	call malloc
	mov [ebp+0],eax	;store the allocated memory pointer
	pop eax
	mov edi,[ebp+0]	;base pointer to the array
	mov [edi], dword 1
	mov [edi+4], dword 3
	popad
	pushad
	push dword 20
	call malloc
	mov [ebp+4],eax	;store the allocated memory pointer
	pop eax
	mov edi,[ebp+4]	;base pointer to the array
	mov [edi], dword 1
	mov [edi+4], dword 3
	popad
	pushad
	push dword 20
	call malloc
	mov [ebp+8],eax	;store the allocated memory pointer
	pop eax
	mov edi,[ebp+8]	;base pointer to the array
	mov [edi], dword 1
	mov [edi+4], dword 3
	popad
	mov edx, 5
	mov [ebp+24], edx   ;assign value to a variable
	mov edx, 9
	mov [ebp+28], edx   ;assign value to a variable
	pushad
	push dword input_str_int
	call printf
	pop eax
	popad
	pushad
	mov eax, ebp
	add eax, 12
	push eax
	push dword input_format_int
	call scanf
	add esp, 8
	popad
	pushad
	push dword input_str_int
	call printf
	pop eax
	popad
	pushad
	mov eax, ebp
	add eax, 16
	push eax
	push dword input_format_int
	call scanf
	add esp, 8
	popad
	mov edx, [ebp+12]
	push edx 
	mov edx, [ebp+16]
	push edx 
	mov edx, [ebp+28]
	pop eax
	imul edx	;eax*edx stored in edx:eax 
	mov edx, eax    ;truncated result moved to edx 
	push edx 
	mov edx, [ebp+24]
	push edx 
	mov edx, [ebp+28]
	pop eax
	sub eax, edx    ;perform (eax - edx) subtraction
	mov edx, eax    ;store result of subtraction in edx
	push edx 
	mov edx, [ebp+16]
	pop eax
	imul edx	;eax*edx stored in edx:eax 
	mov edx, eax    ;truncated result moved to edx 
	push edx 
	mov edx, [ebp+24]
	push edx 
	mov edx, 2
	pop eax
	imul edx	;eax*edx stored in edx:eax 
	mov edx, eax    ;truncated result moved to edx 
	push edx 
	mov edx, [ebp+28]
	push edx 
	mov edx, [ebp+12]
	pop eax
	imul edx	;eax*edx stored in edx:eax 
	mov edx, eax    ;truncated result moved to edx 
	pop eax
	sub eax, edx    ;perform (eax - edx) subtraction
	mov edx, eax    ;store result of subtraction in edx
	pop eax
	add edx, eax
	pop eax
	add edx, eax
	pop eax
	add edx, eax
	mov [ebp+20], edx   ;assign value to a variable
	mov edx, [ebp+20]
	pushad
	push edx
	push dword integer_output
	call printf
	add esp, 8
	popad
exit_main:  call exit

BOUND_ERROR:
	pushad
	push dword bound_error_str
	call printf
	pop eax
	popad
	call exit
