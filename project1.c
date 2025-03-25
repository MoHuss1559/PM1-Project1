#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int length;
    int height;
} Dimensions;

typedef struct  {
    int num_channels; //this should define how many colors there are in the image, 1 for greyscale, 3 RGB, 4 RGBA
} channels;

typedef struct {
    Dimensions size;
    channels color_info;
    float **data; //points to pixel data for an array for operations
} imagematrix; 

imagematrix *creatematrix (int length, int height, int num_channels){
    imagematrix *img = (imagematrix *)malloc (sizeof(imagematrix));
    if (!img) { //NULL check
    printf("Memory allocation failed. \n");
    return NULL;
    }

    img -> size.length = length;
    img -> size.height = height;
    img -> color_info.num_channels = num_channels;

    img->data = (float**)malloc(height * sizeof(float*));
    if (!img->data) {
        printf("Memory allocation failed for image data rows.\n");
        free(img);
        return NULL;
    }
for (int i = 0; i<height; i++){
    img->data[i] = (float *)malloc(length * num_channels * sizeof(float));
    if (!img->data[i]) {
        printf("Memory allocation failed for image row %d.\n", i);
        for (int j = 0; j < i; j++) {
            free(img->data[j]);
        }
        free (img->data);
        free (img);
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

imagematrix *checkDimensions (imagematrix *img1, imagematrix *img2){
    if (img1->size.length !=img2 -> size.length || img1->size.height !=img2->size.length || img1->color_info.num_channels !=img2->color_info.num_channels){
        printf("Error: image matrices do not match for addition or subtraction.\n");
        return NULL;
    }


imagematrix *result = creatematrix(img1->size.length, img1->size.height, img1->color_info.num_channels);
    if (!result) return NULL;
}

//addition
imagematrix *add_matrices(imagematrix *img1, imagematrix *img2) {
    if (!checkdimensions(img1, img2)) return NULL;

    imagematrix *result = creatematrix(img1->size.length, img1->size.height, img1->color_info.num_channels);
    if (!result) return NULL;

    for (int i = 0; i < img1->size.height; i++) {
        for (int j = 0; j < img1->size.length * img1->color_info.num_channels; j++) {
            result->data[i][j] = img1->data[i][j] + img2->data[i][j];
        }
    }
return result;
}
//subtraction
imagematrix *subtract_matrices(imagematrix *img1, imagematrix *img2) {
    if (!checkdimensions(img1, img2)) return NULL;

    imagematrix *result = creatematrix(img1->size.length, img1->size.height, img1->color_info.num_channels);
    if (!result) return NULL;

    for (int i = 0; i < img1->size.height; i++) {
        for (int j = 0; j < img1->size.length * img1->color_info.num_channels; j++) {
            result->data[i][j] = img1->data[i][j] - img2->data[i][j];
        }
    }

    return result;
}

//scaling matrices

imagematrix *scale_matrix (imagematrix *img, float scalar){
if (!img) {
    printf ("Error image is NULL\n");
}
//create new matrix for new image
imagematrix *result = creatematrix(img->size.length, img->size.height, img->color_info.num_channels);
if(!result) return NULL;

for (int i=0; i<img->size.length; i++){
    for (int j=0; j<img->size.height; j++){
        result->data[i][j] = img->data[i][j] *scalar;
    }
}
return result;
}

//multiplciation
imagematrix *multiplymatrices(imagematrix *img1, imagematrix *img2){
    if (img1->color_info.num_channels != 1 || img2->color_info.num_channels != 1) { //confirm the image in greyscale 
        printf("Error: Matrix multiplication is only supported for grayscale images.\n");
        return NULL;

}


if  (img1->size.length != img2->size.height) { //confirm the image is able to have matrix multiplication performed on it
    printf("Error: Image dimensions are not compatible for matrix multiplication.\n");
    return NULL;
}

imagematrix *result = creatematrix (img2->size.length, img1->size.height,1);
if (!result) return NULL;

//do the multiplcation
for (int i = 0; i < img1->size.height; i++) {
    for (int j = 0; j < img2->size.length; j++) {
        result->data[i][j] = 0; // Initialize value
        for (int k = 0; k < img1->size.length; k++) {
            result->data[i][j] += img1->data[i][k] * img2->data[k][j];
        }
    }
}

return result;
}
