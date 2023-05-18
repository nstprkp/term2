#include "Header.h"

int main(void)
{
    int n=1000;
    char *fname_in = (char*)calloc(n, sizeof(char));
    printf("Enter name of file to work with:\n");
    get_str(fname_in, n+1);
    menu();
    int t=10;
    while (t!=0) {
        fflush(stdin);
        printf("\nChoose your option: ");
        BMPFile* bmpf = load_BMPFile(fname_in);
        scanf("%d", &t);
        switch (t) {
            case 0:
                printf("Thank you! Bye!\n");
                break;
            case 1:
                negative(bmpf);
                char fname1[19] = "ph_in_negative.bmp";
                saveBMP(bmpf, fname1);
                printf("Check it!\n");
                break;
            case 2:
                set_BW(bmpf);
                char fname2[26] = "ph_in_black_and_white.bmp";
                saveBMP(bmpf, fname2);
                printf("Check it!\n");
                break;
            case 3:
                printf("Choose picture you want to correct with median filter:\n");
                menu_for_gamma_and_median();
                RGB_pix* pixels = malloc((bmpf->bhdr.width * bmpf->bhdr.width + bmpf->bhdr.height) * sizeof(RGB_pix));

                fflush(stdin);
                int q;
                scanf("%d", &q);
                switch (q) {
                    case 1:
                        map_image_to_array(bmpf, pixels);
                        median_filter(bmpf, pixels);
                        char fname6[50] = "ph_with_filter.bmp";
                        saveBMP(bmpf, fname6);
                        printf("Check it!\n");
                        break;
                    case 2:
                        negative(bmpf);
                        map_image_to_array(bmpf, pixels);
                        median_filter(bmpf, pixels);
                        char fname7[40] = "ph_in_negative_filter.bmp";
                        saveBMP(bmpf, fname7);
                        printf("Check it!\n");
                        break;
                    case 3:
                        set_BW(bmpf);
                        map_image_to_array(bmpf, pixels);
                        median_filter(bmpf, pixels);
                        char fname8[40] = "ph_in_black_and_white_filter.bmp";
                        saveBMP(bmpf, fname8);
                        printf("Check it!\n");
                        break;
                }
                free(pixels);
                break;
            case 4:
                printf("Choose picture you want to correct with gamma correction:\n");
                menu_for_gamma_and_median();
                fflush(stdin);
                int p;
                scanf("%d", &p);
                switch (p) {
                    case 1:
                        gamma_correction(bmpf);
                        char fname3[23] = "ph_with_gam.bmp";
                        saveBMP(bmpf, fname3);
                        printf("Check it!\n");
                        break;
                    case 2:
                        negative(bmpf);
                        gamma_correction(bmpf);
                        char fname4[23] = "ph_in_negative_gam.bmp";
                        saveBMP(bmpf, fname4);
                        printf("Check it!\n");
                        break;
                    case 3:
                        set_BW(bmpf);
                        gamma_correction(bmpf);
                        char fname5[31] = "ph_in_black_and_white_gam.bmp";
                        saveBMP(bmpf, fname5);
                        printf("Check it!\n");
                        break;
                }
                break;
        }
        free_BMPFile(bmpf);
    }
    return 0;
}
