#include <iostream>
#include <cmath>
#include <windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

int main() {
    int width, height, channels;
    unsigned char* img = stbi_load("images/image2.jpg", &width, &height, &channels, 3);

    if (!img) {
        std::cerr << "Failed to load image\n";
        return 1;
    }

    double scale = 100; // contruling the scale of Ascii Image (more is biger)
    
    double x = width/(52*(scale/100));
    double y = height/(20*(scale/100));

    int scale_x = x;  // skip every x pixels horizontally // 20
    int scale_y = y; // skip every y pixels vertically  // 52



    for (int y = 0; y < height; y += scale_y) {
        for (int x = 0; x < width; x += scale_x) {
            int idx = (y * width + x) * channels;
            unsigned char R = img[idx + 0];
            unsigned char G = (channels > 1) ? img[idx + 1] : R;
            unsigned char B = (channels > 2) ? img[idx + 2] : R;

            float brightness = 0.2126f*R + 0.7152f*G + 0.0722f*B;
            
            // Contrast adjustment
            float contrast = 1.4f;    // >1 = higher contrast, <1 = lower
            float midpoint = 228.0f;  // mid gray
            brightness = (brightness - midpoint) * contrast + midpoint;

            // Clamp to 0–255
            if (brightness < 0) brightness = 0;
            if (brightness > 255) brightness = 255;

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
