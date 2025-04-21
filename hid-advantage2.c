/*
 *  HID driver for Kinesis Advantage2
 *
 *  Copyright (c) 2021 Nikolay Yakimov <root@livid.pp.ru>
 */

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include <linux/device.h>
#include <linux/hid.h>
#include <linux/module.h>

//#include <linux/drivers/hid/hid-ids.h>
#define USB_VENDOR_ID_KINESIS           0x29EA
#define USB_DEVICE_ID_ADVANTAGE2	0x0102

static const __u8 *advantage2_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	if (*rsize == 0x41 && rdesc[0]==0x05 && rdesc[1] == 0x01 && rdesc[2] == 0x09 && rdesc[3] == 0x06) {
		hid_info(hdev, "Fixing up Kinesis Advantage2 report descriptor %x\n", rdesc[0x35]);
		rdesc[0x35] = 0xFF;
	}
	return rdesc;
}

static const struct hid_device_id kinesis_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOR_ID_KINESIS, USB_DEVICE_ID_ADVANTAGE2)},
	{ }
};
MODULE_DEVICE_TABLE(hid, kinesis_devices);

static struct hid_driver kinesis_driver = {
	.name = "kinesis-advantage2",
	.id_table = kinesis_devices,
	.report_fixup = advantage2_report_fixup,
};
module_hid_driver(kinesis_driver);

MODULE_LICENSE("GPL");
