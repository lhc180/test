#include "common.h"
#pragma pack(push)
#pragma pack(2)
typedef struct BMPFILEHEADER
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
}BMPFILEHEADER;

typedef struct BMPINFOHEADER
{
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
}BMPINFOHEADER;
#pragma pack(pop)

void ReadPic(char* file, uint8_t *rgb, int32_t *pwidth, int32_t *pheight)
{   
    BMPFILEHEADER bmpheader;
    BMPINFOHEADER bmpinfo;

    FILE *fp;

    char szFilename[1024];
    sprintf(szFilename, file, NULL);
    fp = fopen(szFilename, "rb");
    if (fp == NULL)
    {
        return;
    }
 //   fread(&bmpheader, sizeof(bmpheader), 1, fp);
 //   fread(&bmpinfo, sizeof(bmpinfo), 1, fp);
	fread(&bmpheader, sizeof(bmpheader.bfOffBits), 1, fp);

    *pwidth = bmpinfo.biWidth;
    *pheight = bmpinfo.biHeight;

    int32_t width = *pwidth;
    int32_t height = *pheight;
    //    int32_t linesize = (((width * 24) + 31) & (~31)) / 8;
    int32_t linesize = width *3;
    fread(rgb, linesize * height, 1, fp);

    fclose(fp);

}

typedef unsigned short int WORD; 
typedef unsigned int DWORD;  
typedef int LONG; 

struct tagRGBQUAD { 
    unsigned char rgbBlue; 
    unsigned char rgbGreen; 
    unsigned char rgbRed; 
    unsigned char rgbReserved; 
}__attribute__((packed)); 

typedef struct tagRGBQUAD RGBQUAD; 

struct tagBITMAPFILEHEADER { 
    WORD    bfType; 
    DWORD   bfSize; 
    WORD    bfReserved1; 
    WORD    bfReserved2; 
    DWORD   bfOffBits; 
}__attribute__((packed)); 
typedef struct tagBITMAPFILEHEADER BITMAPFILEHEADER; 

struct tagBITMAPINFOHEADER{ 
    DWORD   biSize; 
    LONG    biWidth; 
    LONG    biHeight; 
    WORD    biPlanes; 
    WORD    biBitCount; 
    DWORD   biCompression; 
    DWORD   biSizeImage; 
    LONG    biXPelsPerMeter; 
    LONG    biYPelsPerMeter; 
    DWORD   biClrUsed; 
    DWORD   biClrImportant; 
}__attribute__((packed));

typedef struct tagBITMAPINFOHEADER BITMAPINFOHEADER; 


int read_bmp_file(char* filename, char * const buffer, 
         char** data, int* width, int* height, int* depth) 
{ 
    FILE*           fd; 
    int             rt; 
    int             channel; 
    char*  bits; 

    BITMAPFILEHEADER bmfh; 
    BITMAPINFOHEADER bmih; 

    fd = fopen(filename, "rb"); 
    if(fd == NULL) { 
        printf("NO such file %s. \n", filename); 
        return -1; 
    } 

    rt = fread(buffer, 1, 2*1024*1024, fd); 
    printf("read image ->%d. \n", rt); 
    fclose(fd); 

    printf("sizeof(bmfh)->%d. \n", sizeof(bmfh)); 
    printf("sizeof(bmih)->%d. \n", sizeof(bmih)); 

    memcpy(&bmfh, buffer, sizeof(bmfh)); 
    memcpy(&bmih, buffer + sizeof(bmfh), sizeof(bmih)); 
    if(bmfh.bfType != 19778) { 
        return -1; 
    } 
    bits = (char*) (buffer+bmfh.bfOffBits); 

    channel = bmih.biBitCount/8; 
    *depth = bmih.biBitCount; 
    *width = bmih.biWidth; 
    *height = bmih.biHeight; 

    *data = bits; 
    printf(".   size(%dx%d) channel:%d --- \n", *width, *height, channel); 
    return 0; 
} 


inline void RGB2ARGB(uint8_t *src, uint8_t *dest, int32_t width, int32_t height)
{
    int32_t i = 0;
    int32_t j = 0;
    for(i = 0; i<height ; i++)
    {
        for (j = 0; j < width; j++)
        {
            *dest++ = *src++; /* blue */
            *dest++ = *src++; /* green */
            *dest++ = *src++; /* red */
            *dest++ = 0;        /*a*/
        }
    }
}
