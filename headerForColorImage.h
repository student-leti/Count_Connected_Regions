	unsigned char bitmap[61];
	
	
/*-- FILE HEADER 14 bytes--*/
	
	/*bitmap signature*/
	bitmap[0] = 'B';
	bitmap[1] = 'M';
	
	/*file size*/
	bitmap[2] = 0xBE;
	bitmap[3] = 0xB8;
	bitmap[4] = 0x12;
	bitmap[5] = 0;
	
	/*reserved field (in hex. 00 00 00 00)*/
	bitmap[6] = 0;
	bitmap[7] = 0;
	bitmap[8] = 0;
	bitmap[9] = 0;
		
	/* offset of pixel data inside the image
	 * The offset, i.e. starting address, of the byte where the bitmap
	 * image data (pixel array) can be found
	 * here 62 (BITMAP HEADER) + (FILE HEADER)*/
	 bitmap[10] = 0x3e;
	 bitmap[11] = 0;
	 bitmap[12] = 0;
	 bitmap[13] = 0;
	 	 
	 /*--BITMAP HEADER - 40 bytes--*/
	 
	 /*header size*/
	 bitmap[14] = 0x28;/*40 in hex*/
	 bitmap[15] = 0;
	 bitmap[16] = 0;
	 bitmap[17] = 0;
	 	 
	 /*width of the image in pixels Left to right order!!*/
	 bitmap[18] = 0x54;
	 bitmap[19] = 0x3;
	 bitmap[20] = 0;
	 bitmap[21] = 0;
	 	 
	 /*height of the image in pixels Positive for bottom to top pixel order!!*/
	 bitmap[22] = 0xE0;
	 bitmap[23] = 0x1;
	 bitmap[24] = 0;
	 bitmap[25] = 0;
	 	 
	 /*no of color planes, must be 1*/
	 bitmap[26] = 1;
	 bitmap[27] = 0;
	 
	 /*number of bits per pixel, which is the color depth of image. (1,4,8,16,24,32)*/
	 bitmap[28] = 24;
	 bitmap[29] = 0;
	 
	 /*compression method (no compression here)*/
	 bitmap[30] = 0;
	 bitmap[31] = 0;
	 bitmap[32] = 0;
	 bitmap[33] = 0;
	 	 
	 /*size of pixel data in bytes. The image size. This is the size of raw bitmap data
	 * a dummy 0 can be given for BI_RGB bitmaps*/
	 bitmap[34] = 0x80;
	 bitmap[35] = 0xB8;
	 bitmap[36] = 0x12;
	 bitmap[37] = 0;
	 
	 /*horizontal resolution of the image - pixel per meter (2835)*/
	 bitmap[38] = 0x6D;
	 bitmap[39] = 0x62;
	 bitmap[40] = 0;
	 bitmap[41] = 0;
	 
	 /*vertical resolution of the image - pixel per meter (2835)*/
	 bitmap[42] = 0x45;
	 bitmap[43] = 0x62;
	 bitmap[44] = 0;
	 bitmap[45] = 0;
	 
	 /*color pallete information*/
	 bitmap[46] = 0;
	 bitmap[47] = 0;
	 bitmap[48] = 0;
	 bitmap[49] = 0;
	 
	 /*number of important colors
	  * if 0 then all colors are important - generally ignored*/
	 bitmap[50] = 0;
	 bitmap[51] = 0;
	 bitmap[52] = 0;
	 bitmap[53] = 0;
	 
	 
	 /*null bytes*/
	 bitmap[54] = 0;
	 bitmap[55] = 0;
	 bitmap[56] = 0;
	 bitmap[57] = 0;
	 bitmap[58] = 0xFF;
	 bitmap[59] = 0xFF;
	 bitmap[60] = 0xFF;
