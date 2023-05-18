#include "Header.h"

void menu()
{
    printf("Choose your option:\n");
    printf("1. Make your picture negative.\n");
    printf("2. Make your picture black and white.\n");
    printf("3. Median filtering.\n");
    printf("4. Gamma correction.\n");
    printf("0. Finish program.\n");
}

void menu_for_gamma_and_median()
{
    printf("1. Your picture.\n");
    printf("2. Negative picture.\n");
    printf("3. Black and white picture.\n");
}

char* get_str(char *s, int k)
{
    int c, i=0;
    while(--k > 0 && (c = getchar())!=EOF && c != '\n')
        s[i++] = c;
    s[i] = '\0';
    return s;
}

void output_information(BMPFile* bmp_file)
{
    printf("ID=%x\n",bmp_file->bhdr.ID);
    printf("file_size=%d\n", bmp_file->bhdr.file_size);
    printf("unused1=%x\n", bmp_file->bhdr.unused1);
    printf("unused2=%x\n", bmp_file->bhdr.unused2);
    printf("pixel_offset=%d\n", bmp_file->bhdr.pixel_offset);
    printf("header_size=%d\n", bmp_file->bhdr.header_size);
    printf("width=%d\n", bmp_file->bhdr.width);
    printf("height=%d\n", bmp_file->bhdr.height);
    printf("color_planes=%d\n", bmp_file->bhdr.color_planes);
    printf("bits_per_pixel=%d\n", bmp_file->bhdr.bits_per_pixel);
    printf("BI_RGB=%d\n", bmp_file->bhdr.BI_RGB);
    printf("data_size=%d\n", bmp_file->bhdr.data_size);
    printf("pwidth=%d\n", bmp_file->bhdr.pwidth);
    printf("pheight=%d\n", bmp_file->bhdr.pheight);
    printf("colors_count=%d\n", bmp_file->bhdr.colors_count);
    printf("imp_colors_count=%d\n", bmp_file->bhdr.imp_colors_count);
}

void out_BMPPixels(BMPFile*  bmp_file)
{
    for (int i=0; i<bmp_file->bhdr.data_size; i++) {
        if (i % 16 == 0) {
            printf("\n%04x: ", i);
        }
        printf("%02x ", bmp_file->data[i]);
    }
}

int check_header(BMPFile* bmp_file)
{
    return bmp_file->bhdr.ID == 0x4D42
        && bmp_file->bhdr.bits_per_pixel == 24
        && bmp_file->bhdr.color_planes == 1
        && bmp_file->bhdr.BI_RGB == 0
        && bmp_file->bhdr.colors_count == 0;
}

BMPFile* load_BMPFile(char* fname)
{
    FILE* fp = fopen(fname, "rb");
    if (!fp) {
        printf("Can't load file!\n");
        fclose(fp);
        exit(0);
    }
    BMPFile* bmp_file = (BMPFile*)malloc(sizeof(BMPFile));
    int check;
    check = fread(&bmp_file->bhdr, sizeof(DIBHeader), 1, fp);

    if (check!=1){
        printf("Can't read image.\n");
        fclose(fp);
        exit(-1);
    }

    if (!check_header(bmp_file)) {
        printf("Bad image!\n");
        fclose(fp);
        exit(-1);
    }

    bmp_file->data = (unsigned char*)malloc(bmp_file->bhdr.data_size);

    if (!bmp_file->data) {
        printf("Can't allocate %d bytes!\n", bmp_file->bhdr.data_size);
        fclose(fp);
        exit(-1);
    }

    fseek(fp, bmp_file->bhdr.pixel_offset, SEEK_SET);
    check = fread(bmp_file->data, bmp_file->bhdr.data_size, 1, fp);

    if (check!=1){
        printf("Can't read image.\n");
        fclose(fp);
        exit(-1);
    }

    out_BMPPixels(bmp_file);

    fclose(fp);
    return bmp_file;
}

void saveBMP(const BMPFile* bmp_file, char* fname)
{
    FILE* fp = fopen(fname, "wb");
    rewind(fp);
    fwrite(&bmp_file->bhdr, sizeof (DIBHeader), 1, fp);
    fseek(fp, bmp_file->bhdr.pixel_offset, SEEK_SET);
    fwrite(bmp_file->data, bmp_file->bhdr.data_size, 1, fp);
    fclose(fp);
}

static int get_position(const DIBHeader * header, int x, int y) {
    int padding = (4 - (abs(header->width) * 3) % 4) %4;
    int bytes_per_row = abs(header->width) * 3;
    int row_size = bytes_per_row + padding;
    int j = (abs(header->height) - y - 1) * row_size;
    int i = x * 3;

    return i + j;
}

RGB_pix get_pixel(BMPFile * bmp, int x, int y) {
    if (x < 0 || x >= abs(bmp->bhdr.width)) {
        printf("Error. X should be [%d, %d), but %d\n", 0, abs(bmp->bhdr.width), x);
        RGB_pix rgb;
        rgb.b=0; rgb.g=0; rgb.r=0;
        return rgb;
    }

    if (y < 0 || y >= abs(bmp->bhdr.height)) {
        printf("Error. Y should be [%d, %d), but %d\n", 0, abs(bmp->bhdr.height), y);
        RGB_pix rgb;
        rgb.b=0; rgb.g=0; rgb.r=0;
        return rgb;
    }

    int pos = get_position(&bmp->bhdr, x, y);
    RGB_pix rgb = {
            bmp->data[pos + 2],
            bmp->data[pos + 1],
            bmp->data[pos + 0],
    };
    return rgb;
}

void set_pixel(BMPFile * bmp, int x, int y, RGB_pix rgb) {
    if (x < 0 || x >= abs(bmp->bhdr.width)) {
        printf("Error. X should be [%d, %d), but %d\n", 0, abs(bmp->bhdr.width), x);
        return;
    }

    if (y < 0 || y >= abs(bmp->bhdr.height)) {
        printf("Error. Y should be [%d, %d), but %d\n", 0, abs(bmp->bhdr.height), y);
        return;
    }

    int pos = get_position(&bmp->bhdr, x, y);
    bmp->data[pos + 2] = rgb.r;
    bmp->data[pos + 1] = rgb.g;
    bmp->data[pos + 0] = rgb.b;
}

void set_BW(BMPFile* bmp) {
    for (int y = 0; y < abs(bmp->bhdr.height); y++) {
        for (int x = 0; x < abs(bmp->bhdr.width); x++) {
            RGB_pix pixel = get_pixel(bmp, x, y);
            int rgb = (int) ( (pixel.r + pixel.g + pixel.b) / 3);
            pixel.r = rgb;
            pixel.g = rgb;
            pixel.b = rgb;
            set_pixel(bmp, x, y, pixel);
        }
    }
}

void negative(BMPFile* bmp)
{
    for (int y = 0; y < abs(bmp->bhdr.height); y++) {
        for (int x = 0; x < abs(bmp->bhdr.width); x++) {
            RGB_pix pixel = get_pixel(bmp, x, y);
            pixel.r = 255 - pixel.r;
            pixel.g = 255 - pixel.g;
            pixel.b = 255 - pixel.b;
            set_pixel(bmp, x, y, pixel);
        }
    }
}

void gamma_correction(BMPFile * bmp)
{
    float gammaCoef;
    printf("Choose gamma coefficent:\n");
    scanf("%f", &gammaCoef);
    for (int j = 0; j < abs(bmp->bhdr.height); j++) {
        for (int i = 0; i < abs(bmp->bhdr.width); i++) {
            RGB_pix pixel = get_pixel(bmp, i, j);
            int r = (int) (255 * pow((pixel.r / 255.0f), gammaCoef));
            int g = (int) (255 * pow((pixel.g / 255.0f), gammaCoef));
            int b = (int) (255 * pow((pixel.b / 255.0f), gammaCoef));
            if (r > 255) { r = 255;}
            if (g > 255) { g = 255;}
            if (b > 255) { b = 255;}
            pixel.r = r; pixel.g = g; pixel.b = b;
            set_pixel(bmp, i, j, pixel);
        }
    }
}

void map_image_to_array(BMPFile* bmp, RGB_pix* pixels)
{
    long arrayIndex;
    RGB_pix pixel;
    for (int j = 0; j < abs(bmp->bhdr.height); j++) {
        for (int i = 0; i < abs(bmp->bhdr.width); i++) {
            arrayIndex = j * abs(bmp->bhdr.width) + i;
            pixel = get_pixel(bmp, i, j);
            pixels[arrayIndex].r = pixel.r;
            pixels[arrayIndex].g = pixel.g;
            pixels[arrayIndex].b = pixel.b;
        }
    }
}

int comparator(const void *a, const void *b)
{
    int totalA = (((RGB_pix*)a)->r + ((RGB_pix*)a)->g + ((RGB_pix*)a)->b) / 3;
    int totalB = (((RGB_pix*)b)->r + ((RGB_pix*)b)->g + ((RGB_pix*)b)->b) / 3;
    return totalB - totalA;
}

void median_filter(BMPFile* bmp, RGB_pix* pixels)
{
    int mask;
    printf("Choose option for median filter(3/5/9 the best decision):\n");
    scanf("%d", &mask);
    int sq = 1;
    int offset = bmp->bhdr.width;
    long arrayLength = bmp->bhdr.height * bmp->bhdr.width;
    int maskSize = mask * mask;
    RGB_pix* maskArray = NULL;
    int maskOffsetFromStart = (mask / 2);

    while (offset < arrayLength) {
        for (int arrayIndex = offset, col = 0; col < bmp->bhdr.width; col++, arrayIndex++) {
            maskArray = (RGB_pix*) realloc(maskArray, maskSize * sizeof(RGB_pix));
            int maskStartingRow = 0;
            int t = offset / bmp->bhdr.width;
            if ( t - maskOffsetFromStart > maskStartingRow) {
                maskStartingRow = offset / bmp->bhdr.width - maskOffsetFromStart;
            }
            int maskStartingCol = 0;
            if (col - maskOffsetFromStart > maskStartingCol) {
                maskStartingCol = col - maskOffsetFromStart;
            }

            int i = 0;
            for (int maskRow = maskStartingRow, k = 0; k < mask && k < abs(bmp->bhdr.height); k++, maskRow++) {
                for (int maskCol = maskStartingCol, j = 0; j < mask && j < abs(bmp->bhdr.width); j++, maskCol++) {
                    long where = maskRow * abs(bmp->bhdr.width) + maskCol;
                    maskArray[i++] = pixels[where];
                }
            }
            qsort(maskArray, maskSize, sizeof(RGB_pix), comparator);
            RGB_pix new_value;
            new_value.r = 0; new_value.g = 0; new_value.b = 0;
            new_value.r = maskArray[maskSize / 2].r;
            new_value.g = maskArray[maskSize / 2].g;
            new_value.b = maskArray[maskSize / 2].b;
            pixels[arrayIndex].r = new_value.r;
            pixels[arrayIndex].g = new_value.g;
            pixels[arrayIndex].b = new_value.b;
        }
        sq += 1;
        offset = abs(bmp->bhdr.width) * sq;
    }
    for (int j = 0; j < abs(bmp->bhdr.height); j++) {
        for (int i = 0; i < abs(bmp->bhdr.width); i++) {
            set_pixel(bmp, i, j, pixels[j * abs(bmp->bhdr.width) + i]);
        }
    }
}

void free_BMPFile(BMPFile* bmp_file) {
    if (bmp_file) {
        free(bmp_file);
    }
}
