#include <string>
#include <fstream>
#include <stdint.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class ImageToASCII
{
public:
    ImageToASCII(std::string imagePath);
    bool ConvertToText(void);

private:
    std::string imagePath;
    const std::string characters = "@%W&Q0m$B#RbUOXG496PKdq|Y]{CoxZv/\\TL*rs!<+\";,:_. ";
};