#include <stdint.h>
#define R(x) (*(volatile uint32_t *)(x))
#define RCC 0x4002104C
#define GA 0x48000000
#define GB 0x48000400
#define GC 0x48000800
static void cfg(uint32_t p, int n)
{
	R(p) = (R(p) & ~(3u << (2*n))) | (1u << (2 * n));
	R(p+4) &= ~(1u << n);
	R(p + 0xC) &= ~(3u<<(2 * n));
}
static void wait(void)
{
	volatile uint32_t i = 300000;
	while (i) i--;
}
int main(void)
{
	R(RCC) |= 7;
	cfg(GC, 7);
	cfg(GB, 7);
	cfg(GA,9);
	while (1) {
		R(GA + 0x18) = 1u << 25;
		R(GC + 0x18) = 1u << 7;
		wait();
		R(GC+0x18) = 1u << 23;
		R(GB + 0x18) = 1u<<7;
		wait();
		R(GB + 0x18) = 1u << 23;
		R(GA + 0x18) =1u << 9;
		wait();
	}
}
