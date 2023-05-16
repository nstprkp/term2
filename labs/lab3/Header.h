#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma pack(1)
/*typedef struct BMPHeader {
    unsigned char ID[2]; //magic identifier
    unsigned int file_size; //size of file
    unsigned char unused[4]; //unused char
    unsigned int pixel_offset; //offset where the pixel array
} BMPHeader;*/

typedef struct DIBHeader {
    unsigned short ID; //magic identifier
    unsigned int file_size; //size of file
    unsigned short unused1; //unused char
    unsigned short unused2;
    unsigned int pixel_offset; //offset where the pixel array
    unsigned int header_size; //number of bytes in the DIBHeader (from this point)
    unsigned int width; //width in pixel
    unsigned int height; //height in pixel
    unsigned short color_planes; //number of color plane
    unsigned short bits_per_pixel; //number of bits per pixel
    unsigned int BI_RGB; //compression
    unsigned int data_size; //size of pixel in not compression
    unsigned int pwidth; //print resolution
    unsigned int pheight; //printf resolution
    unsigned int colors_count; //number of colors in palette
    unsigned int imp_colors_count; //number of important colors
} DIBHeader;

typedef struct BMPFile {
    DIBHeader bhdr;
    //DIBHeader dhdr;
    unsigned char* data;
} BMPFile;
#pragma pop

typedef struct RGB_pix {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB_pix;

void menu();
void menu_for_gamma_and_median();
char* get_str(char *s, int k);
void output_information(BMPFile* bmp_file);
void out_BMPPixels(BMPFile*  bmp_file);
int check_header(BMPFile* bmp_file);
BMPFile* load_BMPFile(char* fname);
void saveBMP(const BMPFile* bmp_file, char* fname);
static int get_position(const DIBHeader * header, int x, int y);
RGB_pix get_pixel(BMPFile * bmp, int x, int y);
void set_pixel(BMPFile * bmp, int x, int y, RGB_pix rgb);
void set_BW(BMPFile* bmp);
void negative(BMPFile* bmp);
void gamma_correction(BMPFile * bmp);
void map_image_to_array(BMPFile* bmp, RGB_pix* pixels);
int comparator(const void *a, const void *b);
void median_filter(BMPFile* bmp, RGB_pix* pixels);
void free_BMPFile(BMPFile* bmp_file);