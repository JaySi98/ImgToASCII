#pragma once

#include <string>
#include <fstream>
#include <stdint.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <CommandParser.h>
class ImageConverter
{
public:
    ImageConverter(std::string imagePath, ConversionParams params);
    bool ConvertToText(void);
    
private:
    bool ConvertSimple(void);
    bool ConvertWithDimensions(void);

    std::string imagePath;
    ConversionParams params;
    const std::string outputFile = "output.txt";
};