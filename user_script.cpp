#include <Mouse.h>
#include <Keyboard.h>

const DeviceDescriptor dDscr = D_DEVICE(0x00, 0x00, 0x00, 64, 0x1532 /*vid*/, 0x0043 /*pid*/, 0x100, IMANUFACTURER, IPRODUCT, ISERIAL, 1);
const uint8_t* dStr[3] = {"asd", "fgh", "jkl"};

int main(void)
{
	init();  // wiring.c
	USBDevice.attach(/*true, &dDscr, dStr*/);

	for (;;) 
	{
		if (serialEventRun) {serialEventRun();}
		
		/*
		Mouse.move(2,0,0);
		delay(1000);		
		Mouse.move(-2,0,0);
		delay(1000);
		*/
	}

	return 0;
}