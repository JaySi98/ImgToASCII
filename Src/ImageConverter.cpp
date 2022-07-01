#include <ImageConverter.h>

ImageConverter::ImageConverter(std::string imagePath, ConversionParams params) 
: imagePath(imagePath), params(params)
{ }

bool ImageConverter::ConvertToText(void)
{
    if(params.keepDimensions)
    {
        return ConvertWithDimensions();
    }
    else
    {
        return ConvertSimple();
    }
}

bool ImageConverter::ConvertSimple(void)
{
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    
    if(!image.empty())
    {
        std::ofstream file;
        file.open(outputFile);

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

        file.close();
        return true;
    }
    else 
        throw "Couldn't open image";
}

bool ImageConverter::ConvertWithDimensions(void)
{

}