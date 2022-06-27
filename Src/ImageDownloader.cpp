#include <ImageDownloader.h>

bool ImageDownloader::DownloadImage(std::string url, std::string filePath)
{
   HTTPStreamFactory::registerFactory(); // Must register the HTTP factory to stream using HTTP
   FTPStreamFactory::registerFactory(); // Must register the FTP factory to stream using FTP

   // Create and open a file stream
   std::ofstream fileStream;
   fileStream.open(filePath, std::ios::out | std::ios::trunc | std::ios::binary);

   // Create the URI from the URL to the file.
   URI uri(url);

   // Open the stream and copy the data to the file. 
   std::unique_ptr<std::istream> pStr(URIStreamOpener::defaultOpener().open(uri));
   StreamCopier::copyStream(*pStr.get(), fileStream);

   fileStream.close();

   return true;
}
