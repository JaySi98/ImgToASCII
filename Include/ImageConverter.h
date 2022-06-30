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
    ImageConverter(std::string imagePath, ConversionSettings settings);
    bool ConvertToText(void);

private:
    std::string imagePath;
    ConversionSettings settings;
    const std::string characters = "@%W&Q0m$B#RbUOXG496PKdq|Y]{CoxZv/\\TL*rs!<+\";,:_. ";
};