#include "gpio.h"

GPIO gpio;

void been_init()
{
	gpio_init(F_beer,GPO,GPIO_LOW,GPO_PUSH_PULL);
}

void citie_init(void)
{
	gpio_init(citie,GPO,GPIO_LOW,GPO_PUSH_PULL);
}


void user_gpio_init()
{
	gpio_init(D4,GPI,GPIO_HIGH,GPI_PULL_UP);
	gpio_init(D27,GPI,GPIO_HIGH,GPI_PULL_UP);
	gpio_init(C31,GPI,GPIO_HIGH,GPI_PULL_UP);
	gpio_init(C27,GPI,GPIO_HIGH,GPI_PULL_UP);
	gpio_init(C26,GPI,GPIO_HIGH,GPI_PULL_UP);
	gpio_init(C4,GPI,GPIO_HIGH,GPI_PULL_UP);
	
	been_init();
	
	citie_init();
}

void read_boma()
{
	gpio.boma[0] = gpio_get_level(D4);
	gpio.boma[1] = gpio_get_level(D27);
}

void read_key()
{
	if(!gpio_get_level(C31))
	{
		system_delay_ms(20);
		if(!gpio_get_level(C31))
		{
			gpio.key[0]=!gpio.key[0];
			system_delay_ms(500);
		}
	}
	if(!gpio_get_level(C27))
	{
		system_delay_ms(20);
		if(!gpio_get_level(C27))
		{
			gpio.key[1]=!gpio.key[1];
			system_delay_ms(500);
		}
	}
	if(!gpio_get_level(C26))
	{
		system_delay_ms(20);
		if(!gpio_get_level(C26))
		{
			gpio.key[2]=!gpio.key[2];
			system_delay_ms(500);
		}
	}
	if(!gpio_get_level(C4))
	{
		system_delay_ms(20);
		if(!gpio_get_level(C4))
		{
			gpio.key[3]=!gpio.key[3];
			system_delay_ms(500);
		}
	}
}


