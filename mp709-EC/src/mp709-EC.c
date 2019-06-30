/*	mp709-EC (Enchanced control), uses for separate control a few mp709 devices
    Copyright (C) 2012  Emil Limarenko aka ashwilliams

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

-lusb-1.0 -lpthread

    */
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>

#define DEV_VID 0x16C0
#define DEV_CONFIG 1
#define DEV_INTF 0

unsigned char COMMAND_1[8] = {0xE7,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char COMMAND_2[8] = {0xE7,0x19,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char COMMAND_3[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

int get_mp709_list(void);
int control (char *argv[]);

int main(int argc, char * argv[])
{
int erreport;
switch (argc)
	{
	case 1:
		get_mp709_list();
		break;
	case 3:
		erreport = control(argv);
		break;
	default :
		printf("Use command:[./mp709-EC] for get ID of mp709 connected to the system;\n");
		printf("Use command:[./mp709-EC 'on/off' 'ID'] for switch on/off the mp709");
		break;
	}
return 0;
}

int get_mp709_list(void)
{
libusb_device_handle * handle;
libusb_device ** list;
libusb_device * found = NULL;
libusb_context * ctx;
ssize_t count;
ssize_t i = 0;
uint8_t nobus,nodev;
int erreport;
libusb_init(&ctx);
if ((count = libusb_get_device_list(ctx, &list)) < 0)
	{
	printf("impossible error\n");
	return -1;
	}
for (i = 0; i < count; i++)
	{
	libusb_device * device = list[i];
	struct libusb_device_descriptor desc;
	libusb_get_device_descriptor(device, &desc);
	if ((desc.idVendor == DEV_VID))
		{
		found = device;
		nobus = libusb_get_bus_number(device);
		nodev = libusb_get_device_address(device);
		erreport = libusb_open(found, &handle);
		libusb_detach_kernel_driver(handle, DEV_INTF);
		libusb_claim_interface(handle,  DEV_INTF);
		erreport = libusb_control_transfer(handle, LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_IN, 0x9, 0x300, 0, COMMAND_3, 8, 100);     //--
		libusb_attach_kernel_driver(handle, DEV_INTF);
		libusb_close(handle);
		if ((COMMAND_3[0])==0x00)
			{
			printf("mp709 BUS:%u DEVICE: %u ID for control:%u Status:ON,just connected \n", nobus, nodev,i);
			}
		else
			{
			switch (COMMAND_3[1])
				{
				case 0x19: printf("mp709 BUS:%u DEVICE: %u ID for control:%u Status:ON\n", nobus, nodev,i); break;
				case 0x00: printf("mp709 BUS:%u DEVICE: %u ID for control:%u Status:OFF\n", nobus, nodev,i); break;
				default :  printf("mp709 BUS:%u DEVICE: %u ID for control:%u Status:'Unknown error'\n", nobus, nodev,i); break;
				}
			}
	}	}
libusb_free_device_list(list, 1);
return 0;
}

int control (char *argv[])
{
libusb_device_handle * handle;
libusb_device ** list;
libusb_device * found = NULL;
ssize_t count;
ssize_t i = 0;
libusb_context * ctx;
libusb_init(&ctx);
int erreport;
if ((count = libusb_get_device_list(ctx, &list)) < 0)
	{
	printf("impossible error\n");
	return -1;
	}
i=atoi(argv[2]);
libusb_device * device = list[i];
struct libusb_device_descriptor desc;
libusb_get_device_descriptor(device, &desc);
if ((desc.idVendor == DEV_VID))
	{
	found = device;
	erreport = libusb_open(found, &handle);
	libusb_detach_kernel_driver(handle, DEV_INTF);
	libusb_claim_interface(handle,  DEV_INTF);
	if(strcasecmp(argv[1], "off") == 0)
		{
		erreport = libusb_control_transfer(handle, LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_OUT, 0x9, 0x300, 0, COMMAND_1, 8, 100);     //--
		printf("OFF\n");
		libusb_attach_kernel_driver(handle, DEV_INTF);
		libusb_close(handle);
		}
	if(strcasecmp(argv[1], "on") == 0)
		{
		erreport = libusb_control_transfer(handle, LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_OUT, 0x9, 0x300, 0, COMMAND_2, 8, 100);      //--
		printf("ON\n");
		libusb_attach_kernel_driver(handle, DEV_INTF);
		libusb_close(handle);
		}
	}
libusb_free_device_list(list, 1);
return 0;
}
