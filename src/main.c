
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#define LEDPORT (GPIOA)
#define LEDPIN (GPIO_Pin_5)
#define ENABLE_GPIO_CLOCK (RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE))

/* timing is not guaranteed :) */
void simple_delay(uint32_t us)
{
	/* simple delay loop */
	for (uint32_t i = us; i > 0; i--){
        asm volatile ("nop");
    }
}

/* system entry point */
int main(void)
{
	/* gpio init struct */
	GPIO_InitTypeDef gpio;
	/* reset rcc */
	RCC_DeInit();
	/* enable clock GPIO */
	ENABLE_GPIO_CLOCK;
	/* use LED pin */
	gpio.GPIO_Pin = LEDPIN;
	/* mode: output */
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	/* output type: push-pull */
	gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	/* apply configuration */
	GPIO_Init(LEDPORT, &gpio);
	/* main program loop */
	for (;;) {
		/* set led on */
		GPIO_SetBits(LEDPORT, LEDPIN);
		/* delay */
		simple_delay(1000000);
		/* clear led */
		GPIO_ResetBits(LEDPORT, LEDPIN);
		/* delay */
		simple_delay(1000000);
	}

	/* never reached */
	return 0;
}