#include <iostream>
#include <cmath>
#include <windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

int main() {
    int width, height, channels;
    unsigned char* img = stbi_load("image2.jpg", &width, &height, &channels, 3);

    if (!img) {
        std::cerr << "Failed to load image\n";
        return 1;
    }

    int scale_x = 4; // skip every x pixels horizontally
    int scale_y = 8; // skip every y pixels vertically


    for (int y = 0; y < height; y += scale_y) {
        for (int x = 0; x < width; x += scale_x) {
            int idx = (y * width + x) * channels;
            unsigned char R = img[idx + 0];
            unsigned char G = (channels > 1) ? img[idx + 1] : R;
            unsigned char B = (channels > 2) ? img[idx + 2] : R;

            float brightness = 0.2126f*R + 0.7152f*G + 0.0722f*B;

            const char* gradient = " .'`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
            int grad_len = strlen(gradient);
            char c = gradient[(int)(brightness * (grad_len-1) / 255)];
            std::cout << c;
        }
        std::cout << "\n";
    }
    stbi_image_free(img);

    Sleep(10000);
    return 0;
}
