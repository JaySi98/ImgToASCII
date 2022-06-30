#include <iostream>
#include <memory>
#include <fstream>

#include <Poco/URIStreamOpener.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <Poco/MD5Engine.h>
#include <Poco/DigestStream.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPRequest.h>

class ImageDownloader
{
public:
    bool DownloadImage(std::string url, std::string filePath);

private:

};