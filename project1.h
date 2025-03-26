#ifndef PROJECT1_H
#define PROJECT1_H

// Structs
typedef struct {
    int length;
    int height;
} Dimensions;

typedef struct  {
    int num_channels; // 1 = grayscale, 3 = RGB, 4 = RGBA
} channels;

typedef struct {
    Dimensions size;
    channels color_info;
    float **data; // 2D array of pixel values
} imagematrix;

// Function Declarations
imagematrix *creatematrix(int length, int height, int num_channels);
void free_image(imagematrix *img);

imagematrix *add_matrices(imagematrix *img1, imagematrix *img2);
imagematrix *subtract_matrices(imagematrix *img1, imagematrix *img2);
imagematrix *scale_matrix(imagematrix *img, float scalar);
imagematrix *multiplymatrices(imagematrix *img1, imagematrix *img2);

#endif // PROJECT1_H
