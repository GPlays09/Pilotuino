/*
  PluggableUSB.cpp
  Copyright (c) 2015 Arduino LLC

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "USBAPI.h"
#include "PluggableUSB.h"
 
#if defined(USBCON)	
#ifdef PLUGGABLE_USB_ENABLED

extern uint8_t _initEndpoints[];

int PluggableUSB_::getInterface(uint8_t* interfaceCount)
{
	int sent = 0;
	PluggableUSBModule* node;
	for (node = rootNode; node; node = node->next) {
		int res = node->getInterface(interfaceCount);
		if (res < 0)
			return -1;
		sent += res;
	}
	return sent;
}

int PluggableUSB_::getDescriptor(USBSetup& setup)
{
	PluggableUSBModule* node;
	for (node = rootNode; node; node = node->next) {
		int ret = node->getDescriptor(setup);
		// ret!=0 -> request has been processed
		if (ret)
			return ret;
	}
	return 0;
}

void PluggableUSB_::getShortName(char *iSerialNum)
{
	PluggableUSBModule* node;
	for (node = rootNode; node; node = node->next) {
		iSerialNum += node->getShortName(iSerialNum);
	}
	*iSerialNum = 0;
}

bool PluggableUSB_::setup(USBSetup& setup)
{
	PluggableUSBModule* node;
	for (node = rootNode; node; node = node->next) {
		if (node->setup(setup)) {
			return true;
		}
	}
	return false;
}

bool PluggableUSB_::plug(PluggableUSBModule *node)
{
	if ((lastEp + node->numEndpoints) > USB_ENDPOINTS) {
		return false;
	}

	if (!rootNode) {
		rootNode = node;
	} else {
		PluggableUSBModule *current = rootNode;
		while (current->next) {
			current = current->next;
		}
		current->next = node;
	}

	node->pluggedInterface = lastIf;
	node->pluggedEndpoint = lastEp;
	lastIf += node->numInterfaces;
	for (uint8_t i = 0; i < node->numEndpoints; i++) {
		_initEndpoints[lastEp] = node->endpointType[i];
		lastEp++;
	}
	return true;
	// restart USB layer???
}

void PluggableUSB_::sie(uint8_t If, uint8_t Ep)
{
	this->lastIf = If;
	this->lastEp = Ep;
}

PluggableUSB_& PluggableUSB()
{
	static PluggableUSB_ obj;
	return obj;
}

void setIfEp(uint8_t If, uint8_t Ep)
{
	PluggableUSB().sie(If, Ep);
}


PluggableUSB_::PluggableUSB_() : lastIf(0), lastEp(0), rootNode(NULL)
{
	// Empty
}

#endif

#endif /* if defined(USBCON) */
