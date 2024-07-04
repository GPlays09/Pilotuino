// test includes (not necessary)
#include <Mouse.h>
#include <Keyboard.h>

const DeviceDescriptor dDscr = D_DEVICE(0x00, 0x00, 0x00, 64, 0x1532 /*vid*/, 0x0043 /*pid*/, 0x100, IMANUFACTURER, IPRODUCT, ISERIAL, 1);
const uint8_t* dStr[3] = {"Manufacturer", "Product", "SerialNumber"}; // device descriptor strings

int main(void) {
	init();  // wiring.c
	USBDevice.attach(/*true, &dDscr, dStr*/);
	// comport enabled, device descriptor ptr, const char array of arrays ptr
	// default: true, vid: 0x2341 pid: 0x8036, "Arduino_LLC" "USB_IO_Board" "..."
	
	// adding or initializing of user-defined descriptors must happen after .attach();
	
	for (;;) {
		if (serialEventRun) {serialEventRun();}
	}

	return 0;
}