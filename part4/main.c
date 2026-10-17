#include <stdint.h>
int main(void)
{
	__asm__ volatile (
		"movw r0, #:lower16:0x4002104C\n\t"
		"movt r0, #:upper16:0x4002104C\n\t"
		"ldr r1, [r0]\n\t"
		"orr r1, r1, #2\n\t"
		"str r1, [r0]\n\t"
		"movw r0, #:lower16:0x48000400\n\t"
		"movt r0, #:upper16:0x48000400\n\t"
		"ldr r1, [r0]\n\t"
		"bic r1, r1, #0xC000\n\t"
		"orr r1, r1, #0x4000\n\t"
		"str r1, [r0]\n\t"
		"ldr r1, [r0, #4]\n\t"
		"bic r1, r1, #0x80\n\t"
		"str r1, [r0, #4]\n\t"
		"mov r1, #0x80\n\t"
		"str r1, [r0, #0x18]\n\t"
		::: "r0", "r1", "memory"
	);
	while (1);
}
