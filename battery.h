unsigned int battery_size=685;
unsigned char battery[] = {
0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,0x00,0x00,0x00,0x0d,0x49,0x48,0x44,
0x52,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x10,0x08,0x06,0x00,0x00,0x00,0x1f,
0xf3,0xff,0x61,0x00,0x00,0x00,0x01,0x73,0x52,0x47,0x42,0x00,0xae,0xce,0x1c,
0xe9,0x00,0x00,0x00,0x06,0x62,0x4b,0x47,0x44,0x00,0xff,0x00,0xff,0x00,0xff,
0xa0,0xbd,0xa7,0x93,0x00,0x00,0x00,0x09,0x70,0x48,0x59,0x73,0x00,0x00,0x0b,
0x13,0x00,0x00,0x0b,0x13,0x01,0x00,0x9a,0x9c,0x18,0x00,0x00,0x00,0x07,0x74,
0x49,0x4d,0x45,0x07,0xdc,0x0c,0x07,0x10,0x1d,0x23,0xb0,0x22,0x1d,0x52,0x00,
0x00,0x02,0x2d,0x49,0x44,0x41,0x54,0x38,0xcb,0xad,0x93,0xcd,0x4b,0x54,0x51,
0x18,0xc6,0x7f,0xe7,0xde,0x99,0xd0,0xa2,0x9c,0x19,0x67,0x2c,0xb5,0x54,0x82,
0x10,0xb2,0x45,0xd4,0x46,0x8a,0x16,0x7d,0x2c,0x24,0x48,0x28,0x12,0xc2,0xa0,
0x55,0x45,0x7f,0x40,0xfb,0xcc,0x16,0x2e,0x0a,0x21,0x09,0x8a,0x56,0x25,0xe5,
0x22,0x29,0xb2,0x4d,0x41,0x04,0x41,0x64,0x3a,0xb8,0x49,0x30,0x1a,0x43,0x9c,
0x34,0x63,0x9c,0x0f,0x9d,0x71,0xee,0x9d,0x19,0xc7,0x7b,0xcf,0xdb,0x62,0xb0,
0x34,0xc7,0x55,0x3d,0x9b,0xf7,0x9c,0xf7,0xe1,0xf9,0x71,0x5e,0x78,0x0f,0xfc,
0xa3,0xd4,0xdf,0x8d,0x8e,0x0e,0x18,0x1c,0x84,0x17,0x97,0xa8,0x37,0x0c,0x2e,
0x22,0x18,0x5a,0xd1,0x7f,0xee,0x11,0x3f,0x57,0xbd,0xb2,0xea,0xea,0x2a,0xd5,
0xf3,0x7b,0x68,0x1e,0xea,0x3d,0xdd,0x33,0x72,0xaf,0x55,0xb2,0xb3,0x03,0x92,
0x9d,0x1d,0x90,0xd1,0xfb,0x47,0xa5,0xff,0xd6,0x89,0x9e,0xce,0xbd,0x34,0x03,
0x5c,0x3d,0xbc,0x09,0xa4,0xef,0x72,0xdd,0xcd,0xe9,0xb1,0x5e,0x71,0xe7,0x9e,
0x4b,0xf8,0x46,0x50,0xeb,0xcf,0x77,0x45,0x8f,0xf7,0x49,0xb8,0xbb,0x56,0x27,
0x26,0x1e,0xcb,0xd7,0x4f,0x77,0xa4,0xfb,0x42,0xcd,0xed,0x4d,0x47,0x78,0xf9,
0xa0,0x53,0xda,0x8f,0xb4,0x0a,0x86,0x47,0x2d,0x24,0xe3,0xcc,0x4d,0x86,0x71,
0xb5,0x26,0xd0,0x70,0x90,0xc6,0xc6,0x06,0x44,0xbb,0x32,0xf4,0x71,0x54,0x9d,
0xbd,0xf6,0xe4,0x77,0xce,0xb3,0x16,0x50,0x69,0x2f,0xe2,0x06,0x0e,0x28,0x53,
0x29,0xfc,0x9e,0xad,0x04,0xaa,0x83,0x25,0xc3,0xbb,0x1d,0x76,0x34,0x92,0xc8,
0xd8,0x6a,0x31,0xfa,0x8c,0x37,0x27,0x51,0x6d,0xef,0x90,0x0d,0x00,0xb4,0xc6,
0x7d,0xd5,0x86,0xd9,0xfe,0x1a,0xb5,0xad,0x1e,0xc9,0xc7,0xc9,0xe5,0x97,0x59,
0xfa,0xf1,0x9d,0xe8,0xf8,0x43,0xa6,0x27,0x46,0xd1,0xfe,0x43,0x98,0xc6,0x9f,
0xc8,0x3a,0xc0,0xac,0xdb,0xc4,0x92,0xb9,0x9b,0x90,0x15,0x45,0xb2,0x33,0x48,
0x7c,0x8c,0x5c,0xc6,0x26,0x9d,0x4a,0xe3,0x2c,0x2d,0x90,0x37,0x83,0x4c,0x15,
0xf7,0x11,0xcd,0xa7,0x80,0xa9,0x8d,0x80,0x14,0x8d,0x3c,0x5d,0xb9,0xce,0xa9,
0x6c,0x13,0xde,0x82,0x97,0x42,0x51,0x93,0x71,0x72,0xcc,0x14,0x2d,0x22,0x59,
0x87,0x2f,0x8b,0x16,0xb5,0x35,0x55,0xc4,0x76,0x1d,0x2b,0x0f,0x70,0xb5,0xb0,
0xc5,0x70,0x48,0x58,0x82,0xe3,0xec,0x24,0xed,0x78,0xb1,0x75,0x8e,0x79,0x27,
0x86,0xad,0xe7,0xf1,0xa8,0x0c,0xae,0x76,0x51,0xb8,0xe5,0x47,0xd0,0x5a,0xa3,
0x14,0xd8,0xb6,0xbd,0xe9,0xda,0xb9,0x8e,0xc3,0xf0,0xf0,0x7b,0x0f,0xb0,0x02,
0x60,0xac,0xf5,0x45,0x34,0x22,0x25,0x10,0x08,0x4a,0x6d,0x58,0x54,0x5c,0x57,
0x93,0x4c,0xce,0xd7,0xad,0xde,0xd7,0x01,0x92,0xa9,0x14,0xc1,0x60,0x08,0x11,
0x41,0x04,0x44,0x04,0x28,0x9d,0xb5,0x68,0xfc,0x3e,0x3f,0x96,0x65,0x51,0x2c,
0x16,0x8b,0xab,0x19,0x73,0xfd,0x0b,0x8d,0x11,0xd7,0x71,0xce,0x84,0x42,0xa1,
0x0a,0xbf,0xbf,0x8a,0xca,0x8a,0x4a,0x0c,0xd3,0xa0,0x50,0x58,0x26,0x67,0xe7,
0x89,0xc7,0x13,0xd9,0xc9,0xc9,0x6f,0x57,0x62,0xb1,0x58,0x18,0xd0,0x65,0x3f,
0x13,0xa0,0x5a,0xf6,0xb7,0xb4,0x05,0xaa,0x03,0xc7,0x1d,0xc7,0xa9,0x06,0x94,
0x61,0x98,0xe9,0x64,0x32,0xf1,0x21,0x12,0x89,0xbc,0xf5,0xf9,0x7c,0x56,0x3a,
0x9d,0xe6,0xbf,0xe9,0x17,0xdd,0x75,0x0e,0x26,0x58,0x87,0xe2,0xf9,0x00,0x00,
0x00,0x00,0x49,0x45,0x4e,0x44,0xae,0x42,0x60,0x82
};
