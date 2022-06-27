#include <iostream>
#include <memory>
#include <fstream>

#include <Poco/URIStreamOpener.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <Poco/Net/HTTPStreamFactory.h>
#include <Poco/Net/FTPStreamFactory.h>

using Poco::URIStreamOpener;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;
using Poco::Net::HTTPStreamFactory;
using Poco::Net::FTPStreamFactory;

class ImageDownloader
{
public:
    bool DownloadImage(std::string url);

private:

};