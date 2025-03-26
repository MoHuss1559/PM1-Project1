#include <stdio.h>
#include "project1.c"  // Includes function definitions directly

// Fill an image matrix with a specific value for all pixels
void fill_image(imagematrix *img, float value) {
    for (int i = 0; i < img->size.height; i++) {
        for (int j = 0; j < img->size.length * img->color_info.num_channels; j++) {
            img->data[i][j] = value;
        }
    }
}

int main() {
    int operation;
    float scalar;

    printf("🖼️  Image Matrix Operations\n");
    printf("---------------------------\n");
    printf("Choose an operation:\n");
    printf("1 - Add Images\n");
    printf("2 - Subtract Images\n");
    printf("3 - Scale Image\n");
    printf("4 - Multiply Matrices (Grayscale Only)\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &operation);

    imagematrix *img1, *img2, *result;

    if (operation == 3) {
        img1 = creatematrix(3, 3, 3);
        fill_image(img1, 100.0);
        printf("Enter scalar value to scale the image: ");
        scanf("%f", &scalar);

        result = scale_matrix(img1, scalar);
        if (result) {
            printf("Scaled Result [0][0]: %.2f\n", result->data[0][0]);
            free_image(result);
        }
        free_image(img1);

    } else if (operation == 4) {
        img1 = creatematrix(2, 3, 1);
        img2 = creatematrix(3, 2, 1);
        fill_image(img1, 1.0);
        fill_image(img2, 2.0);

        result = multiplymatrices(img1, img2);
        if (result) {
            printf("Multiplied Result [0][0]: %.2f\n", result->data[0][0]);
            free_image(result);
        }
        free_image(img1);
        free_image(img2);

    } else if (operation == 1 || operation == 2) {
        img1 = creatematrix(3, 3, 3);
        img2 = creatematrix(3, 3, 3);
        fill_image(img1, 100.0);
        fill_image(img2, 50.0);

        if (operation == 1) {
            result = add_matrices(img1, img2);
            if (result) {
                printf("Addition Result [0][0]: %.2f\n", result->data[0][0]);
            }
        } else {
            result = subtract_matrices(img1, img2);
            if (result) {
                printf("Subtraction Result [0][0]: %.2f\n", result->data[0][0]);
            }
        }

        if (result) free_image(result);
        free_image(img1);
        free_image(img2);

    } else {
        printf("Invalid operation selected.\n");
    }

    return 0;
}
