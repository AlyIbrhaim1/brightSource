#include "servo.h"
void initServoMotor(void)
{
	/* start servo motor on PORTC PIN6 , PIN 7 */
	/* enable portc clock */
	setBit(SYSCTL->RCGCGPIO , 2 );
	/* enable digital output on port c pin6 and pin7 */
	setBit(GPIOC->DEN,PIN6);
	setBit(GPIOC->DEN,PIN7);
	/* set direction as output on pin6 and pin7 */
	setBit(GPIOC->DIR,PIN6);
	setBit(GPIOC->DIR,PIN7);
	/* clear data on pin6 and pin7 on portc */
	clearBit(GPIOC->DATA,PIN6);
	clearBit(GPIOC->DATA,PIN7);
	
}
/* goto angle */
void servoGotoAngle(uint8_t angle)
{
	uint8_t counter ;
	/* get the delay time according to angle */ 
	uint16_t delaytime = getTime(angle);
	/* for loop to goto position and stuck there */
	for(counter = 0 ; counter < 50 ; counter++)
	{
		/* generate the pwm wave */
		setBit(GPIOC->DATA , PIN6 );
		delay_us(delaytime);
		clearBit(GPIOC->DATA,PIN6);
		delay_us(20000-delaytime);
	
	}

}
/* goto angle vertical angle */
void servoGotoVerticalAngle(uint8_t verticalAngle)
{
	uint8_t counter ;
	//uint16_t delaytime = (750 +(STEPSIZE * verticalAngle ));
	uint16_t delaytime = getTime(verticalAngle);
	for(counter = 0 ; counter < 50 ; counter++)
	{
		
		setBit(GPIOC->DATA , PIN6 );
		delay_us(delaytime);
		clearBit(GPIOC->DATA,PIN6);
		delay_us(20000-delaytime);
	
	}
}
/* goto horizontal angle */
void servoGotoHorizontalAngle(uint8_t horizontalAngle)
{
	uint8_t counter ;
	uint16_t delaytime = getTime(horizontalAngle);
	for(counter = 0 ; counter < 50 ; counter++)
	{
		
		setBit(GPIOC->DATA , PIN7 );
		delay_us(delaytime);
		clearBit(GPIOC->DATA,PIN7);
		delay_us(20000-delaytime);
	
	}
}
/* goto both angles together */
void servoGotoVH(uint8_t verticalAngle,uint8_t horizontalAngle)
{
	servoGotoHorizontalAngle(horizontalAngle);
	servoGotoVerticalAngle(verticalAngle);
}
/* check for angle value limitations and return calculated delay time according to angle */
uint16_t getTime(uint8_t angle)
{
	uint16_t newAngle ;
	
	if(angle < 0 )
	{
			newAngle = 0 ;
	}
	else if( angle > 180 )
	{
		newAngle = 180 ;
	}
	else
	{
		newAngle = angle ;
	}
	return (750 +(STEPSIZE * newAngle ));
}
