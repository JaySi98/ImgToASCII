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
    void ConvertToText(void);
    
private:
    void ConvertSimple(cv::Mat& image, std::ofstream& file);
    void ConvertWithCharSize(cv::Mat& image, std::ofstream& file);
    int GetAvgBrightness(cv::Mat& image, int row, int col);
    
    std::string imagePath;
    ConversionParams params;
    const std::string outputFile = "output.txt";
};