//First byte description:
//Bit 7 - Color or B&W mode. If 0 - B&W; If 1 - color.
//Bit 6 - Palette mode. If 0 - no palette; If 1 - with palette.
//Bit 5 - Palette size if bit 6 is 1. If 0 - 256 colors (8 bit); If 1 - 4096 colors (12 bit).
//Bit 4 - Transparency. If 0 - NO; If 1 - YES and last pixel in array is transparent color.
//Bits 3...0 - color depth. From 1 (1 bit/pixel) till 9 (24 b/p).
//Possible color depth values are - 1, 2, 3, 4, 6, 8, 12, 16 and 24 bit/pixel.

const unsigned char logo1_black[] = { 
0x01, //B&W mode. No palette. Without transparency. Gray scale 1 Bit/Pixel.
0x3c, 0x00, 0x3c, 0x00,//Picture dimension 60 x 60 (width x height).
0x00, 
0x00, 
0x08, 
0x00, 
0x01, 
0x00, 
0x00, 
0x00, 
0x00, 
0x00, 
0x14, 
0x00, 
0x02, 
0x80, 
0x00, 
0x00, 
0x00, 
0x00, 
0x0a, 
0x00, 
0x05, 
0x00, 
0x00, 
0x00, 
0x00, 
0x00, 
0x45, 
0x7f, 
0xea, 
0x20, 
0x00, 
0x00, 
0x00, 
0x00, 
0xa2, 
0xa0, 
0x54, 
0x50, 
0x00, 
0x00, 
0x00, 
0x00, 
0x51, 
0x50, 
0xa8, 
0xa0, 
0x00, 
0x00, 
0x00, 
0x02, 
0x2a, 
0xa9, 
0x55, 
0x44, 
0x00, 
0x00, 
0x00, 
0x05, 
0x14, 
0x56, 
0xa2, 
0x8a, 
0x00, 
0x00, 
0x00, 
0x02, 
0x8a, 
0x29, 
0x45, 
0x14, 
0x00, 
0x00, 
0x00, 
0x11, 
0x55, 
0x10, 
0x8a, 
0xa8, 
0x00, 
0x00, 
0x00, 
0x28, 
0xa2, 
0x80, 
0x14, 
0x50, 
0x40, 
0x00, 
0x00, 
0x14, 
0x51, 
0x40, 
0x28, 
0xa0, 
0xa0, 
0x00, 
0x00, 
0x8a, 
0xa8, 
0x80, 
0x11, 
0x51, 
0x40, 
0x00, 
0x01, 
0x45, 
0x14, 
0x00, 
0x02, 
0x8a, 
0x88, 
0x00, 
0x00, 
0xa2, 
0x8a, 
0x00, 
0x05, 
0x05, 
0x14, 
0x00, 
0x00, 
0x55, 
0x44, 
0x00, 
0x02, 
0x0a, 
0x28, 
0x00, 
0x08, 
0x28, 
0xa0, 
0x00, 
0x00, 
0x15, 
0x51, 
0x00, 
0x14, 
0x14, 
0x50, 
0x00, 
0x00, 
0x28, 
0xa2, 
0x80, 
0x0a, 
0x2a, 
0x20, 
0x00, 
0x00, 
0x51, 
0x45, 
0x00, 
0x45, 
0x45, 
0x00, 
0x00, 
0x00, 
0x22, 
0xaa, 
0x20, 
0xa2, 
0x82, 
0x80, 
0x00, 
0x00, 
0x05, 
0x14, 
0x50, 
0x51, 
0x41, 
0x00, 
0x00, 
0x00, 
0x0a, 
0x28, 
0xa0, 
0x2a, 
0xa0, 
0x00, 
0x00, 
0x00, 
0x04, 
0x55, 
0x40, 
0x14, 
0x50, 
0x00, 
0x00, 
0x00, 
0x00, 
0xa2, 
0x80, 
0x0a, 
0x28, 
0x00, 
0x00, 
0x00, 
0x01, 
0x45, 
0x00, 
0x05, 
0x10, 
0x00, 
0x00, 
0x00, 
0x00, 
0x8a, 
0x00, 
0x06, 
0x80, 
0x00, 
0x00, 
0x00, 
0x00, 
0x16, 
0x00, 
0x05, 
0x40, 
0x00, 
0x00, 
0x00, 
0x00, 
0x2a, 
0x00, 
0x04, 
0x80, 
0x00, 
0x00, 
0x00, 
0x00, 
0x12, 
0x00, 
0x04, 
0x00, 
0x00, 
0x00, 
0x00, 
0x00, 
0x02, 
0x00, 
0x04, 
0x00, 
0x00, 
0x00, 
0x00, 
0x00, 
0x02, 
0x00, 
0x04, 
0x80, 
0x00, 
0x00, 
0x00, 
0x00, 
0x12, 
0x00, 
0x05, 
0x40, 
0x00, 
0x00, 
0x00, 
0x00, 
0x2a, 
0x00, 
0x06, 
0x80, 
0x00, 
0x00, 
0x00, 
0x00, 
0x16, 
0x00, 
0x05, 
0x10, 
0x00, 
0x00, 
0x00, 
0x00, 
0x8a, 
0x00, 
0x0a, 
0x28, 
0x00, 
0x00, 
0x00, 
0x01, 
0x45, 
0x00, 
0x14, 
0x50, 
0x00, 
0x00, 
0x00, 
0x00, 
0xa2, 
0x80, 
0x2a, 
0xa2, 
0x00, 
0x00, 
0x00, 
0x04, 
0x55, 
0x40, 
0x51, 
0x45, 
0x00, 
0x00, 
0x00, 
0x0a, 
0x28, 
0xa0, 
0xa2, 
0x8a, 
0x00, 
0x00, 
0x00, 
0x05, 
0x14, 
0x50, 
0x45, 
0x54, 
0x00, 
0x00, 
0x00, 
0x22, 
0xaa, 
0x20, 
0x0a, 
0x28, 
0x20, 
0x00, 
0x00, 
0x51, 
0x45, 
0x00, 
0x14, 
0x50, 
0x50, 
0x00, 
0x00, 
0x28, 
0xa2, 
0x80, 
0x08, 
0xa8, 
0xa0, 
0x00, 
0x01, 
0x15, 
0x51, 
0x00, 
0x01, 
0x45, 
0x44, 
0x00, 
0x02, 
0x8a, 
0x28, 
0x00, 
0x02, 
0x82, 
0x8a, 
0x00, 
0x01, 
0x45, 
0x14, 
0x00, 
0x01, 
0x05, 
0x14, 
0x00, 
0x00, 
0xaa, 
0x88, 
0x00, 
0x00, 
0x0a, 
0xa8, 
0x80, 
0x10, 
0x51, 
0x40, 
0x00, 
0x00, 
0x14, 
0x51, 
0x40, 
0x28, 
0x28, 
0xa0, 
0x00, 
0x00, 
0x28, 
0xa2, 
0x80, 
0x14, 
0x54, 
0x40, 
0x00, 
0x00, 
0x11, 
0x55, 
0x10, 
0x8a, 
0x8a, 
0x00, 
0x00, 
0x00, 
0x02, 
0x8a, 
0x29, 
0x45, 
0x05, 
0x00, 
0x00, 
0x00, 
0x05, 
0x14, 
0x50, 
0xa2, 
0x82, 
0x00, 
0x00, 
0x00, 
0x02, 
0x2a, 
0xa0, 
0x55, 
0x40, 
0x00, 
0x00, 
0x00, 
0x00, 
0x51, 
0x7f, 
0xe8, 
0xa0, 
0x00, 
0x00, 
0x00, 
0x00, 
0xa2, 
0x80, 
0x14, 
0x50, 
0x00, 
0x00, 
0x00, 
0x00, 
0x45, 
0x00, 
0x0a, 
0x20, 
0x00, 
0x00, 
0x00, 
0x00, 
0x0a, 
0x00, 
0x05, 
0x00, 
0x00, 
0x00, 
0x00, 
0x00, 
0x14, 
0x00, 
0x02, 
0x80, 
0x00, 
0x00, 
0x00, 
0x00, 
0x08, 
0x00, 
0x01, 
0x00, 
0x00, 
0x00, 
};