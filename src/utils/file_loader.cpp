//
// Created by blinku on 17.12.18.
//

#include "file_loader.h"

#include <iostream>
#include <fstream>

std::string LoadFile(const char* filePath) {
    FILE *file;
    file = fopen(filePath, "rt");
    if(!file) {
        std::cout << "Couldn't load the file!" << std::endl;
        return "Error!";
    }

    fseek(file, 0, SEEK_END);
    unsigned long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    auto src = new char[fileSize + 1];

    fread(src, sizeof(char), fileSize, file);
    src[fileSize] = 0;

    std::string result(src);

    delete[] src;

    return result;
}