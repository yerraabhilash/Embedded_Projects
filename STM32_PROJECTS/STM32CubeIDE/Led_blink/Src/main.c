#include <stdint.h>

int delay(){
	for(uint32_t i=0;i<=100000;i++);
	return 0;
}
int main(void)
{
	uint32_t *ahb1enr_en =  (uint32_t*)0x40023830;
	*ahb1enr_en |= (1<<2);
	uint32_t *moder13 = (uint32_t*)0x40020800;
	*moder13 &= ~(1<<27);
	*moder13 |=(1<<26);

	uint32_t *odrio = (uint32_t*)0x40020814;
	while(1){
	delay();
	*odrio |=(1<<12);
	delay();
	delay();
	*odrio &= ~(1<<12);
	delay();
	delay();
	}
}

