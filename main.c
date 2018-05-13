#include <stdio.h>
#include <stdlib.h>
#include "sregion.h"
#include "movefunc.h"

#define FILE_TO_OPEN "image.bmp"
#define HEIGHT_OF_IMAGE 480 // the height of image is 480px
#define WIDTH_OF_IMAGE 852 // the width of image is 852px


////////////////////////////////////////////////////////////
void moveRight(int row, int column,
				int intBitArray[row][WIDTH_OF_IMAGE],
				int label, struct SRegion* pSRegion)
	{
		//checking and mark cells in the right direction
		int neighbourRight = column + 1;
		while(intBitArray[row][neighbourRight] == 1	&& neighbourRight < WIDTH_OF_IMAGE)
		{
			intBitArray[row][neighbourRight] = label;
			pSRegion->area++;
			moveDown(row, neighbourRight, intBitArray, label, pSRegion);
			neighbourRight++;
		}
	}

////////////////////////////////////////////////////////////
void moveDownRight(int row, int column,
					int intBitArray[row][WIDTH_OF_IMAGE],
					int label, struct SRegion* pSRegion)
	{
		//checking and mark cells in the down-right direction
		int neighbourDown = row + 1;
		int neighbourRight = column + 1;
		while(intBitArray[neighbourDown][neighbourRight] == 1
						&& neighbourDown < HEIGHT_OF_IMAGE
						&& neighbourRight < WIDTH_OF_IMAGE)
		{
			intBitArray[neighbourDown][neighbourRight] = label;
			pSRegion->area++;
			moveDown(neighbourDown, neighbourRight, intBitArray, label, pSRegion);
			moveRight(neighbourDown, neighbourRight, intBitArray, label, pSRegion);
			moveLeft(neighbourDown, neighbourRight, intBitArray, label, pSRegion);
			neighbourDown++;
			neighbourRight++;
		}
	}

////////////////////////////////////////////////////////////
void moveDown(int row, int column, int intBitArray[row][WIDTH_OF_IMAGE],
				int label, struct SRegion* pSRegion)
	{
		//checking and mark cells in the down direction
		int neighbourDown = row + 1;
		while(intBitArray[neighbourDown][column] == 1 && neighbourDown < HEIGHT_OF_IMAGE)
		{
			intBitArray[neighbourDown][column] = label;
			pSRegion->area++;
			neighbourDown++;
		}
	}

////////////////////////////////////////////////////////////	
void moveDownLeft(int row, int column, 
					int intBitArray[row][WIDTH_OF_IMAGE],
					int label, struct SRegion* pSRegion)
	{
		//checking and mark cells in the down-left direction
		int neighbourDown = row + 1;
		int neighbourLeft = column - 1;
		while(intBitArray[neighbourDown][neighbourLeft] == 1
						&& neighbourDown < HEIGHT_OF_IMAGE
						&& neighbourLeft >= 0)
		{
			intBitArray[neighbourDown][neighbourLeft] = label;
			pSRegion->area++;
			moveDown(neighbourDown, neighbourLeft, intBitArray, label, pSRegion);
			moveLeft(neighbourDown, neighbourLeft, intBitArray, label, pSRegion);
			moveRight(neighbourDown, neighbourLeft, intBitArray, label, pSRegion);
			moveDownRight(neighbourDown, neighbourLeft, intBitArray, label, pSRegion);
			neighbourDown++;
			neighbourLeft--;
		}
	}

////////////////////////////////////////////////////////////
void moveLeft(int row, int column, 
				int intBitArray[row][WIDTH_OF_IMAGE],
				int label, struct SRegion* pSRegion)
	{
		//checking and mark cells in the left direction
		int neighbourLeft = column - 1;
		while(intBitArray[row][neighbourLeft] == 1	&& neighbourLeft >= 0 )
		{
			intBitArray[row][neighbourLeft] = label;
			pSRegion->area++;
			moveDown(row, neighbourLeft, intBitArray, label, pSRegion);
			neighbourLeft--;
		}
	}

////////////////////////////////////////////////////////////
void fillBitArrayWithZeros(int row, int column,
							int intBitArray[row][WIDTH_OF_IMAGE])
	{
		// fill the array with 0s to delete a possible garbage
		for(int i = 0; i < row; i++)
		{
			for(int j = 0; j < column; j++)
			{
				intBitArray[i][j] = 0;			
			}
		}
	}

////////////////////////////////////////////////////////////
void convertingImageDataBytesToBitArray(unsigned char ucharBuffer[],
										int intBufferSizeInBytes,
										int row, int column,
										int intBitArray[row][WIDTH_OF_IMAGE])
	{
		// converts bytes from the last byte(intBufferSizeInBytes) till 61st byte 
		
		int bitArrayIndex=0;
		int flag = 108;
		
		for(int i = intBufferSizeInBytes - 1; i >= 61; i--)
		{
			for(int j = 0; j < 8; j++)
			{
				intBitArray[bitArrayIndex][flag * 8 - j] = (ucharBuffer[i] & (1 << j)) != 0;
			}
			
			flag--;
			
			if(flag == 0)
				/* if flag is equal to 0 this is mean that
				 *  we've read 108 bytes and we have to start
				 *  write next row of bits */
			{
				flag = 108;
				bitArrayIndex++;
			}			
		}
		
	}

////////////////////////////////////////////////////////////
int setRegionColor()
	{
		
		return rand()%255;
	}

////////////////////////////////////////////////////////////
void createColorImage(int row, int column, int intBitArray[row][WIDTH_OF_IMAGE],
						struct SRegion* pSRegionArray[])
	{
		puts("Create the color image....");
		int intRegionNumber = 0;
		
		FILE* pbmpColorFile = fopen("bmpColorFile.bmp", "wb+");
		
		#include "headerForColorImage.h" // connect header of image file
		for(int i = 0; i < 61; i++)
		{
			printf("%d[%x]  " ,i,bitmap[i]);
			fputc(bitmap[i], pbmpColorFile);
		}
		puts("\nHeader written");
		// Bytes are written in bottom to top pixel order
		// so i is starts from row and decreasing to 0
		for(int i = row - 1; i >= 0; i--)
		{
			//left to right order
			for(int j = 0; j < column; j++)
			{
				if(intBitArray[i][j] == 0)
				{
					// if cell of array is 0 then the color of pixel is black
					// write to the pbmpColorFile 0-bytes for each RGB color
					fputc(0x0, pbmpColorFile);
					fputc(0x0, pbmpColorFile);
					fputc(0x0, pbmpColorFile);
				}
				else
				{
					//// get the cell value and call structure 
					//// from the array of pointers by the value 
					//// to get values of colorReD colorGreen colorBlue values
					intRegionNumber = intBitArray[i][j];
					fputc(pSRegionArray[intRegionNumber]->ColorRed, pbmpColorFile); // RED COLOR
					fputc(pSRegionArray[intRegionNumber]->ColorBlue, pbmpColorFile); // BLUE COLOR
					fputc(pSRegionArray[intRegionNumber]->ColorGreen, pbmpColorFile); // GREEN COLOR
				}
			}
		}
		
		fclose(pbmpColorFile);
	}
	
////////////////////////////////////////////////////////////
int main()
	{
	
	/* set the size for buffer to store a data read from the file
	*  the size is equal to file's size in bytes*/
	int intBufferSizeInBytes = 51902;
	
	unsigned char ucharBuffer[intBufferSizeInBytes];
	
	FILE* pbmpFileToRead = fopen(FILE_TO_OPEN, "rb"); // try to open the file
	
	if(!pbmpFileToRead)
	{
		puts("Cann't open the file.");
		return 1;
	}
	else
	{
		fread(&ucharBuffer, 1, intBufferSizeInBytes, pbmpFileToRead); //reads image data
	}
	
	fclose(pbmpFileToRead); // close file to free memory
	
	puts("\nFile was successfully read and closed.");
		
	/* create a two-dimension bit array for converting
	*  image data in bytes to sequence 0s and 1s.
	*  The number of rows and columns corresponds
	*  to image size in pixels (height x width)*/
	int row = HEIGHT_OF_IMAGE;
	int column = WIDTH_OF_IMAGE;
	int intBitArray [row][column];
		
	fillBitArrayWithZeros(row, column, intBitArray);
	
	convertingImageDataBytesToBitArray(ucharBuffer, 
										intBufferSizeInBytes,
										row, column,
										intBitArray);
	
	/*declaring an array to store the pointers 
	* the size of the array is 5000 elements
	* the first two elements are NULL*/
	struct SRegion* pSRegionArray[5000];
	pSRegionArray[0] = NULL;
	pSRegionArray[1] = NULL;
	
	/* every founded region will be mark by a number.
	 * the number will define the position in the 
	 * array of pointers to the region structure */
	
	int intRegionCounter = 1,
		intTemp = 0;
	
	// exploring the bit array
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < column; j++)
		{
			if(intBitArray[i][j] == 1)
			{
				/* first check the neighbours for mark
				 * if it is, then the active cell is connected
				 * to the region. Get label from the neighbour,
				 * set cells value equal to neighbour's value,
				 * increase area counter for 1 and check the neighbours
				 * on the other directions*/
				if(intBitArray[i][j + 1] > 1) // check the right neighbour
				{
					intBitArray[i][j] = intBitArray[i][j + 1];
					intTemp = intBitArray[i][j];
					moveDown(i, j, intBitArray, intBitArray[i][j], pSRegionArray[intTemp]);
				}
				else if(intBitArray[i + 1][j + 1] > 1) // check the down-right neighbour
				{
					intBitArray[i][j] = intBitArray[i + 1][j + 1];
					intTemp = intBitArray[i][j];
					moveDownLeft(i, j, intBitArray, intBitArray[i][j], pSRegionArray[intTemp]);
				}
				else if(intBitArray[i + 1][j - 1] > 1) // check the down-left neighbour
				{
					intBitArray[i][j] = intBitArray[i + 1][j - 1];
					intTemp = intBitArray[i][j];
					moveDownLeft(i, j, intBitArray, intBitArray[i][j], pSRegionArray[intTemp]);
				}
				else
				{
					/* if it's not, then it is the new region
					 * set the cells value to the new label
					 * alloc a memory for the region structure
					 * set the area to 1 for region
					 * set a color for the region  
					 * and check the neighbours*/
					intRegionCounter++;
					pSRegionArray[intRegionCounter] = (struct SRegion*)malloc(4*sizeof(int));
					pSRegionArray[intRegionCounter]->area = 1;
					pSRegionArray[intRegionCounter]->ColorRed = setRegionColor();
					pSRegionArray[intRegionCounter]->ColorGreen = setRegionColor(); 
					pSRegionArray[intRegionCounter]->ColorBlue = setRegionColor();
					intBitArray[i][j] = intRegionCounter;
					moveDown(i, j, intBitArray, intBitArray[i][j], pSRegionArray[intRegionCounter]);
					moveRight(i, j, intBitArray, intBitArray[i][j], pSRegionArray[intRegionCounter]);
					moveDownLeft(i, j, intBitArray, intBitArray[i][j], pSRegionArray[intRegionCounter]);
					moveDownRight(i, j, intBitArray, intBitArray[i][j], pSRegionArray[intRegionCounter]);
				}
			}
			else if(intBitArray[i][j] > 1) // if the cell is marked, just check neighbours
			{
				intTemp = intBitArray[i][j];
				moveDownLeft(i, j, intBitArray, intBitArray[i][j], pSRegionArray[intTemp]);
				moveDownRight(i, j, intBitArray, intBitArray[i][j], pSRegionArray[intTemp]);
			}
		}
		
	}
	
	printf("\nThere are %d regions on the picture\n", intRegionCounter - 1);
	createColorImage(row, column, intBitArray, pSRegionArray);
	puts("Done.");
	int inputFromUser = 0;
	do
	{
		puts("To get the area of any region type the number of the region from 1 till 4515:");
		puts("To EXIT type 0.");
		scanf("%d", &inputFromUser);
		if(inputFromUser == 0)
		{
			break;
		}
		else if(inputFromUser >= intRegionCounter)
		{
			puts("\nIncorrect input. Insert a number from 1 till 4515\n");
		}
		else
		{
			printf("\nThe area of the region number %d is %d pixels\n",
					inputFromUser, pSRegionArray[inputFromUser + 1]->area);
		}	
	}while(inputFromUser != 0);
		
	// free the used memory from structures
	for(int j = 2; j<intRegionCounter; j++)free(pSRegionArray[j]);
	
	return 0;
	}
