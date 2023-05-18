#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma pack(1)

typedef struct DIBHeader {
    unsigned short ID;
    unsigned int file_size;
    unsigned short unused1;
    unsigned short unused2;
    unsigned int pixel_offset;
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short color_planes;
    unsigned short bits_per_pixel;
    unsigned int BI_RGB;
    unsigned int data_size;
    unsigned int pwidth;
    unsigned int pheight;
    unsigned int colors_count;
    unsigned int imp_colors_count;
} DIBHeader;

typedef struct BMPFile {
    DIBHeader bhdr;
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
