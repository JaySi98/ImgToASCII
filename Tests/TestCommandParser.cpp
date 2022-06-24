#include <gtest/gtest.h>
#include <CommandParser.h>

TEST(CommandParserTest, TestResultConstructor) 
{
    CommandParser parser;
    EXPECT_EQ(parser.result, RESULT_ERROR);
}

TEST(CommandParserTest, TestUrlResult) 
{
    int argc = 3; 
    char* argv[] = {"./Template", "--u", "https://news.website.com/image.jpg"};

    CommandParser parser;
    parser.ParseCommands(argc, argv);

    EXPECT_EQ(parser.result, RESULT_OK_URL);
}

TEST(CommandParserTest, TestPathResult) 
{
    int argc = 3; 
    char* argv[] = {"./Template", "--p", "/image.jpg"};

    CommandParser parser;
    parser.ParseCommands(argc, argv);

    EXPECT_EQ(parser.result, RESULT_OK_PATH);
}

TEST(CommandParserTest, TestUrlImageFormat1) 
{
    int argc = 3; 
    char* argv[] = {"./Template", "--u", "https://news.website.com/image.jpg"};

    CommandParser parser;
    parser.ParseCommands(argc, argv);

    EXPECT_EQ(parser.GetFormat(), ".jpg");
}

TEST(CommandParserTest, TestPathImageFormat1) 
{
    int argc = 3; 
    char* argv[] = {"./Template", "--p", "/image.jpg"};

    CommandParser parser;
    parser.ParseCommands(argc, argv);

    EXPECT_EQ(parser.GetFormat(), ".jpg");
}

TEST(CommandParserTest, TestUrlImageFormat2) 
{
    int argc = 3; 
    char* argv[] = {"./Template", "--u", "https://news.website.com/image.png"};

    CommandParser parser;
    parser.ParseCommands(argc, argv);

    EXPECT_EQ(parser.GetFormat(), ".png");
}

TEST(CommandParserTest, TestPathImageFormat2) 
{
    int argc = 3; 
    char* argv[] = {"./Template", "--p", "/image.png"};

    CommandParser parser;
    parser.ParseCommands(argc, argv);

    EXPECT_EQ(parser.GetFormat(), ".png");
}