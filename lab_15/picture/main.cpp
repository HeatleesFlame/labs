#include <iostream>
#include <fstream>
#include "main.h"
#include <vector>

void color_amp(RGBQUAD** pixel_array, char quater, char color, int widght, int height, float amp) {
    if (quater == 4){
        for(int i = 0; i < height/2 + 1;i++){
            for(int j = 0; j < widght/2 +1; j++){
                switch (color)
                {
                case 'R':
                    pixel_array[i][j].rgbRed *= amp;
                case 'G':
                    pixel_array[i][j].rgbGreen *= amp;
                case 'B':
                    pixel_array[i][j].rgbBlue *= amp;
                default:
                    break;
                }
            }   
        }
    }
    if (quater == 3){
        for(int i = 0 ; i < height/2 + 1;i++){
            for(int j = widght/2+1; j < widght; j++){
                switch (color)
                {
                case 'R':
                    pixel_array[i][j].rgbRed *= amp;
                case 'G':
                    pixel_array[i][j].rgbGreen *= amp;
                case 'B':
                    pixel_array[i][j].rgbBlue *= amp;
                default:
                    break;
                }
            }   
        }
    }
    if (quater == 2){
        for(int i = height/2+1; i < height;i++){
            for(int j = widght/2+1; j < widght; j++){
                switch (color)
                {
                case 'R':
                    pixel_array[i][j].rgbRed *= amp;
                case 'G':
                    pixel_array[i][j].rgbGreen *= amp;
                case 'B':
                    pixel_array[i][j].rgbBlue *= amp;
                default:
                    break;
                }
            }   
        }
    }
    if (quater == 1){
       for(int i = height/2+1; i < height;i++){
            for(int j = 0; j < widght/2 +1; j++){
                switch (color)
                {
                case 'R':
                    pixel_array[i][j].rgbRed *= amp;
                case 'G':
                    pixel_array[i][j].rgbGreen *= amp;
                case 'B':
                    pixel_array[i][j].rgbBlue *= amp;
                default:
                    break;
                }
            }   
        }
    }
    
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " file_name" << std::endl;
        return 0;
    }
 
    char *fileName = argv[1];
 
    // открываем файл
    std::ifstream fileStream(fileName, std::ifstream::binary);
    if (!fileStream) {
        std::cout << "Error opening file '" << fileName << "'." << std::endl;
        return 0;
    }
 
    // заголовк изображения
    BITMAPFILEHEADER fileHeader;
    read(fileStream, fileHeader.bfType, sizeof(fileHeader.bfType));
    read(fileStream, fileHeader.bfSize, sizeof(fileHeader.bfSize));
    read(fileStream, fileHeader.bfReserved1, sizeof(fileHeader.bfReserved1));
    read(fileStream, fileHeader.bfReserved2, sizeof(fileHeader.bfReserved2));
    read(fileStream, fileHeader.bfOffBits, sizeof(fileHeader.bfOffBits));
 
    if (fileHeader.bfType != 0x4D42) {
        std::cout << "Error: '" << fileName << "' is not BMP file." << std::endl;
        return 0;
    }
 
    // информация изображения
    BITMAPINFOHEADER fileInfoHeader;
    read(fileStream, fileInfoHeader.biSize, sizeof(fileInfoHeader.biSize));
 
    // bmp core
    if (fileInfoHeader.biSize >= 12) {
        read(fileStream, fileInfoHeader.biWidth, sizeof(fileInfoHeader.biWidth));
        read(fileStream, fileInfoHeader.biHeight, sizeof(fileInfoHeader.biHeight));
        read(fileStream, fileInfoHeader.biPlanes, sizeof(fileInfoHeader.biPlanes));
        read(fileStream, fileInfoHeader.biBitCount, sizeof(fileInfoHeader.biBitCount));
    }
 
    // получаем информацию о битности
    int colorsCount = fileInfoHeader.biBitCount >> 3;
    if (colorsCount < 3) {
        colorsCount = 3;
    }
 
    int bitsOnColor = fileInfoHeader.biBitCount / colorsCount;
    int maskValue = (1 << bitsOnColor) - 1;
 
    // bmp v1
    if (fileInfoHeader.biSize >= 40) {
        read(fileStream, fileInfoHeader.biCompression, sizeof(fileInfoHeader.biCompression));
        read(fileStream, fileInfoHeader.biSizeImage, sizeof(fileInfoHeader.biSizeImage));
        read(fileStream, fileInfoHeader.biXPelsPerMeter, sizeof(fileInfoHeader.biXPelsPerMeter));
        read(fileStream, fileInfoHeader.biYPelsPerMeter, sizeof(fileInfoHeader.biYPelsPerMeter));
        read(fileStream, fileInfoHeader.biClrUsed, sizeof(fileInfoHeader.biClrUsed));
        read(fileStream, fileInfoHeader.biClrImportant, sizeof(fileInfoHeader.biClrImportant));
    }
 
    // bmp v2
    fileInfoHeader.biRedMask = 0;
    fileInfoHeader.biGreenMask = 0;
    fileInfoHeader.biBlueMask = 0;
 
    if (fileInfoHeader.biSize >= 52) {
        read(fileStream, fileInfoHeader.biRedMask, sizeof(fileInfoHeader.biRedMask));
        read(fileStream, fileInfoHeader.biGreenMask, sizeof(fileInfoHeader.biGreenMask));
        read(fileStream, fileInfoHeader.biBlueMask, sizeof(fileInfoHeader.biBlueMask));
    }
 
    // если маска не задана, то ставим маску по умолчанию
    if (fileInfoHeader.biRedMask == 0 || fileInfoHeader.biGreenMask == 0 || fileInfoHeader.biBlueMask == 0) {
        fileInfoHeader.biRedMask = maskValue << (bitsOnColor * 2);
        fileInfoHeader.biGreenMask = maskValue << bitsOnColor;
        fileInfoHeader.biBlueMask = maskValue;
    }
 
    // bmp v3
    if (fileInfoHeader.biSize >= 56) {
        read(fileStream, fileInfoHeader.biAlphaMask, sizeof(fileInfoHeader.biAlphaMask));
    } else {
        fileInfoHeader.biAlphaMask = maskValue << (bitsOnColor * 3);
    }
 
    // bmp v4
    if (fileInfoHeader.biSize >= 108) {
        read(fileStream, fileInfoHeader.biCSType, sizeof(fileInfoHeader.biCSType));
        read(fileStream, fileInfoHeader.biEndpoints, sizeof(fileInfoHeader.biEndpoints));
        read(fileStream, fileInfoHeader.biGammaRed, sizeof(fileInfoHeader.biGammaRed));
        read(fileStream, fileInfoHeader.biGammaGreen, sizeof(fileInfoHeader.biGammaGreen));
        read(fileStream, fileInfoHeader.biGammaBlue, sizeof(fileInfoHeader.biGammaBlue));
    }
 
    // bmp v5
    if (fileInfoHeader.biSize >= 124) {
        read(fileStream, fileInfoHeader.biIntent, sizeof(fileInfoHeader.biIntent));
        read(fileStream, fileInfoHeader.biProfileData, sizeof(fileInfoHeader.biProfileData));
        read(fileStream, fileInfoHeader.biProfileSize, sizeof(fileInfoHeader.biProfileSize));
        read(fileStream, fileInfoHeader.biReserved, sizeof(fileInfoHeader.biReserved));
    }
 
    // проверка на поддерку этой версии формата
    if (fileInfoHeader.biSize != 12 && fileInfoHeader.biSize != 40 && fileInfoHeader.biSize != 52 &&
        fileInfoHeader.biSize != 56 && fileInfoHeader.biSize != 108 && fileInfoHeader.biSize != 124) {
        std::cout << "Error: Unsupported BMP format." << std::endl;
        return 0;
    }
 
    if (fileInfoHeader.biBitCount != 16 && fileInfoHeader.biBitCount != 24 && fileInfoHeader.biBitCount != 32) {
        std::cout << "Error: Unsupported BMP bit count." << std::endl;
        return 0;
    }
 
    if (fileInfoHeader.biCompression != 0 && fileInfoHeader.biCompression != 3) {
        std::cout << "Error: Unsupported BMP compression." << std::endl;
        return 0;
    }
 
    // rgb info
    RGBQUAD **rgbInfo = new RGBQUAD*[fileInfoHeader.biHeight];
 
    for (unsigned int i = 0; i < fileInfoHeader.biHeight; i++) {
        rgbInfo[i] = new RGBQUAD[fileInfoHeader.biWidth];
    }
 
    // определение размера отступа в конце каждой строки
    int linePadding = ((fileInfoHeader.biWidth * (fileInfoHeader.biBitCount / 8)) % 4) & 3;
 
    // чтение
    unsigned int bufer;
 
    for (unsigned int i = 0; i < fileInfoHeader.biHeight; i++) {
        for (unsigned int j = 0; j < fileInfoHeader.biWidth; j++) {
            read(fileStream, bufer, fileInfoHeader.biBitCount / 8);
            rgbInfo[i][j].rgbRed = bitextract(bufer, fileInfoHeader.biRedMask);
            rgbInfo[i][j].rgbGreen = bitextract(bufer, fileInfoHeader.biGreenMask);
            rgbInfo[i][j].rgbBlue = bitextract(bufer, fileInfoHeader.biBlueMask);
            rgbInfo[i][j].rgbReserved = bitextract(bufer, fileInfoHeader.biAlphaMask);
        }
        fileStream.seekg(linePadding, std::ios_base::cur);
    }
 
    // редактирование
    color_amp(rgbInfo, 2, 'R', fileInfoHeader.biWidth, fileInfoHeader.biHeight, 1.5);

    // запись в файл
    std::ofstream output;
    output.open("res.bmp", std::ios::binary);
    
    output.write(reinterpret_cast<const char*>(&fileHeader.bfType), sizeof(fileHeader.bfType));
    output.write(reinterpret_cast<const char*>(&fileHeader.bfSize), sizeof(fileHeader.bfSize));
    output.write(reinterpret_cast<const char*>(&fileHeader.bfReserved1), sizeof(fileHeader.bfReserved1));
    output.write(reinterpret_cast<const char*>(&fileHeader.bfReserved2), sizeof(fileHeader.bfReserved2));
    output.write(reinterpret_cast<const char*>(&fileHeader.bfOffBits), sizeof(fileHeader.bfOffBits));
    
    output.write(reinterpret_cast<const char*>(&fileInfoHeader.biSize), sizeof(fileInfoHeader.biSize));
    if (fileInfoHeader.biSize >= 12) {
        output.write(reinterpret_cast<const char*>(&fileInfoHeader.biWidth), sizeof(fileInfoHeader.biWidth));
        output.write(reinterpret_cast<const char*>(&fileInfoHeader.biHeight), sizeof(fileInfoHeader.biHeight));
        output.write(reinterpret_cast<const char*>(&fileInfoHeader.biPlanes), sizeof(fileInfoHeader.biPlanes));
        output.write(reinterpret_cast<const char*>(&fileInfoHeader.biBitCount), sizeof(fileInfoHeader.biBitCount));
    }
    if (fileInfoHeader.biSize >= 40) {
        output.write(reinterpret_cast<const char*>(&fileInfoHeader.biCompression), sizeof(fileInfoHeader.biCompression));
        output.write(reinterpret_cast<const char*>(&fileInfoHeader.biSizeImage), sizeof(fileInfoHeader.biSizeImage));
        output.write(reinterpret_cast<const char*>(&fileInfoHeader.biXPelsPerMeter), sizeof(fileInfoHeader.biXPelsPerMeter));
        output.write(reinterpret_cast<const char*>(&fileInfoHeader.biYPelsPerMeter), sizeof(fileInfoHeader.biYPelsPerMeter));
        output.write(reinterpret_cast<const char*>(&fileInfoHeader.biClrUsed), sizeof(fileInfoHeader.biClrUsed));
        output.write(reinterpret_cast<const char*>(&fileInfoHeader.biClrImportant), sizeof(fileInfoHeader.biClrImportant));
    }


    std::vector<char> padding(4, 0); 
    int paddingSize = (4 - (fileInfoHeader.biWidth * 3) % 4) % 4; 

    for (unsigned int i = 0; i < fileInfoHeader.biHeight; i++) {
        for (unsigned int j = 0; j < fileInfoHeader.biWidth; j++) {
            output.put(rgbInfo[i][j].rgbBlue);
            output.put(rgbInfo[i][j].rgbGreen);
            output.put(rgbInfo[i][j].rgbRed);
        }
        output.write(padding.data(), paddingSize);
    }


    output.close();
    return 0;
}
 
unsigned char bitextract(const unsigned int byte, const unsigned int mask) {
    if (mask == 0) {
        return 0;
    }
 
    // определение количества нулевых бит справа от маски
    int
        maskBufer = mask,
        maskPadding = 0;
 
    while (!(maskBufer & 1)) {
        maskBufer >>= 1;
        maskPadding++;
    }
 
    // применение маски и смещение
    return (byte & mask) >> maskPadding;
}

