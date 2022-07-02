#include <ImageConverter.h>

ImageConverter::ImageConverter(std::string imagePath, ConversionParams params) 
: imagePath(imagePath), params(params)
{ }

void ImageConverter::ConvertToText(void)
{
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    std::ofstream file;
    
    if(!image.empty())
    {
        file.open(outputFile);

        if(params.settings & SETT_DIMENSION)
            ConvertWithDimensions(image, file);

        else if(params.settings & SETT_SIZE)
            ConvertWithCharSize(image, file);
        
        else
            ConvertSimple(image, file);

        file.close();
    }
    else 
        throw "Couldn't convert image";
}

void ImageConverter::ConvertSimple(cv::Mat image, std::ofstream& file)
{
    int channels = image.channels();
    int rows = image.rows;
    int cols = image.cols * channels;
    
    uint8_t pixelValue;
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            pixelValue = image.at<uint8_t>(i,j);
            int temp = std::round((pixelValue * (params.characters.length() - 1)) / 255);
            file << params.characters[temp];
        }
        file << std::endl;
    }
}

void ImageConverter::ConvertWithDimensions(cv::Mat image, std::ofstream& file)
{
    int channels = image.channels();
    int rows = image.rows;
    int cols = image.cols * channels;
    
    uint8_t pixelValue;
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            pixelValue = image.at<uint8_t>(i,j);
            int temp = std::round((pixelValue * (params.characters.length() - 1)) / 255);
            file << params.characters[temp];
        }
        file << std::endl;
    }
}

void ImageConverter::ConvertWithCharSize(cv::Mat image, std::ofstream& file)
{
    int channels = image.channels();
    int rows = image.rows;
    int cols = image.cols * channels;
    
    uint8_t pixelValue;
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            pixelValue = image.at<uint8_t>(i,j);
            int temp = std::round((pixelValue * (params.characters.length() - 1)) / 255);
            file << params.characters[temp];
        }
        file << std::endl;
    }
}
