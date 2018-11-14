#include <RASLib/inc/common.h> 
#include <RASLib/inc/gpio.h> 
#include <RASLib/inc/time.h> 
#include <RASLib/inc/motor.h>
#include <RASLib/inc/adc.h>


static tMotor *leftMotor;
static tMotor *rightMotor;

static tADC *light[3];

tBoolean blink_on = true;


void blink(void) 
{
    SetPin(PIN_F3, blink_on);
    blink_on = !blink_on;
}


int main(void) 
{

	
	leftMotor = InitializeServoMotor(PIN_B6, true);
	rightMotor = InitializeServoMotor(PIN_B7, true);
	light[0] = InitializeADC(PIN_D1);
	light[1] = InitializeADC(PIN_D2);
	light[2] = InitializeADC(PIN_D3);


	int direction = 1;

	float speedl = 0;
	float speedr = 0;

	while(speedr <= 1)
	{
		speedr += .1;
		speedl -= .1;
		SetMotor(leftMotor,speedr);
		SetMotor(rightMotor,speedl);
		Wait(.25);
	}

	while(1)
	{
		float leftReading = ADCRead(light[0]);
		float centerReading = ADCRead(light[1]);
		float rightReading = ADCRead(light[2]);

		if (rightReading < .5)
		{
		    	CallEvery(blink, 0, 0.5);
			while(speedl > -.1)
			{
				speedl -= .1;
				SetMotor(leftMotor, speedl);
				Wait(.25);
			}
		}
		else if (leftReading < .5)
		{

			while(speedl > -.1)
			{
				speedl -= .1;
				SetMotor(leftMotor, speedl);
				Wait(.25);
			}

		}
		else if (centerReading < .5)
		{

			SetMotor(leftMotor, -1*speedl);
			SetMotor(rightMotor, -1*speedr); 
			Wait(.25);
			SetMotor(leftMotor, -1*speedl);
			SetMotor(rightMotor, speedr); 
			Wait(1);
		}
		/*
		if (//in range)
		{
			while(speedl <= 1)
			{
				speedl += .1;
				SetMotor(leftMotor, speedl);
				Wait(.25);
			}

		}
		*/


	}



	
}

