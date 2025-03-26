#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== Struct Definitions =====
typedef struct {
    int length;
    int height;
} Dimensions;

typedef struct {
    int num_channels;
} channels;

typedef struct {
    Dimensions size;
    channels color_info;
    float **data;
} imagematrix;

// ===== Function Declarations =====
imagematrix *creatematrix(int length, int height, int num_channels);
void free_image(imagematrix *img);
imagematrix *checkDimensions(imagematrix *img1, imagematrix *img2);
imagematrix *add_matrices(imagematrix *img1, imagematrix *img2);
imagematrix *subtract_matrices(imagematrix *img1, imagematrix *img2);
imagematrix *scale_matrix(imagematrix *img, float scalar);
imagematrix *multiplymatrices(imagematrix *img1, imagematrix *img2);

// ===== Implementations =====

imagematrix *creatematrix(int length, int height, int num_channels) {
    imagematrix *img = (imagematrix *)malloc(sizeof(imagematrix));
    if (!img) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    img->size.length = length;
    img->size.height = height;
    img->color_info.num_channels = num_channels;

    img->data = (float **)malloc(height * sizeof(float *));
    if (!img->data) {
        printf("Memory allocation failed for image data rows.\n");
        free(img);
        return NULL;
    }

    for (int i = 0; i < height; i++) {
        img->data[i] = (float *)malloc(length * num_channels * sizeof(float));
        if (!img->data[i]) {
            printf("Memory allocation failed for image row %d.\n", i);
            for (int j = 0; j < i; j++) {
                free(img->data[j]);
            }
            free(img->data);
            free(img);
            return NULL;
        }
    }
    return img;
}

void free_image(imagematrix *img) {
    if (!img) return;
    for (int i = 0; i < img->size.height; i++) {
        free(img->data[i]);
    }
    free(img->data);
    free(img);
}

imagematrix *checkDimensions(imagematrix *img1, imagematrix *img2) {
    if (img1->size.length != img2->size.length ||
        img1->size.height != img2->size.height ||
        img1->color_info.num_channels != img2->color_info.num_channels) {
        printf("Error: image matrices do not match for addition or subtraction.\n");
        return NULL;
    }

    imagematrix *result = creatematrix(img1->size.length, img1->size.height, img1->color_info.num_channels);
    if (!result) return NULL;

    return result;
}

imagematrix *add_matrices(imagematrix *img1, imagematrix *img2) {
    if (!checkDimensions(img1, img2)) return NULL;

    imagematrix *result = creatematrix(img1->size.length, img1->size.height, img1->color_info.num_channels);
    if (!result) return NULL;

    for (int i = 0; i < img1->size.height; i++) {
        for (int j = 0; j < img1->size.length * img1->color_info.num_channels; j++) {
            result->data[i][j] = img1->data[i][j] + img2->data[i][j];
        }
    }
    return result;
}

imagematrix *subtract_matrices(imagematrix *img1, imagematrix *img2) {
    if (!checkDimensions(img1, img2)) return NULL;

    imagematrix *result = creatematrix(img1->size.length, img1->size.height, img1->color_info.num_channels);
    if (!result) return NULL;

    for (int i = 0; i < img1->size.height; i++) {
        for (int j = 0; j < img1->size.length * img1->color_info.num_channels; j++) {
            result->data[i][j] = img1->data[i][j] - img2->data[i][j];
        }
    }
    return result;
}

imagematrix *scale_matrix(imagematrix *img, float scalar) {
    if (!img) {
        printf("Error: image is NULL\n");
        return NULL;
    }

    imagematrix *result = creatematrix(img->size.length, img->size.height, img->color_info.num_channels);
    if (!result) return NULL;

    for (int i = 0; i < img->size.height; i++) {
        for (int j = 0; j < img->size.length * img->color_info.num_channels; j++) {
            result->data[i][j] = img->data[i][j] * scalar;
        }
    }
    return result;
}

imagematrix *multiplymatrices(imagematrix *img1, imagematrix *img2) {
    if (img1->color_info.num_channels != 1 || img2->color_info.num_channels != 1) {
        printf("Error: Matrix multiplication is only supported for grayscale images.\n");
        return NULL;
    }

    if (img1->size.length != img2->size.height) {
        printf("Error: Image dimensions are not compatible for matrix multiplication.\n");
        return NULL;
    }

    imagematrix *result = creatematrix(img2->size.length, img1->size.height, 1);
    if (!result) return NULL;

    for (int i = 0; i < img1->size.height; i++) {
        for (int j = 0; j < img2->size.length; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < img1->size.length; k++) {
                result->data[i][j] += img1->data[i][k] * img2->data[k][j];
            }
        }
    }

    return result;
}

// ===== Helper to Fill Image Data =====
void fill_image(imagematrix *img, float value) {
    for (int i = 0; i < img->size.height; i++) {
        for (int j = 0; j < img->size.length * img->color_info.num_channels; j++) {
            img->data[i][j] = value;
        }
    }
}

// ===== Main Function =====
int main() {
    int operation;
    float scalar;

    printf("Image Matrix Operations\n");
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
