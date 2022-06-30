#include <ImageDownloader.h>

bool ImageDownloader::DownloadImage(std::string url, std::string filePath)
{
   bool result = true;
   
   try
   {
      Poco::URI uri(url);
      std::string path(uri.getPathAndQuery());

      const Poco::Net::Context::Ptr context = new Poco::Net::Context(
         Poco::Net::Context::CLIENT_USE, "", "", "",
         Poco::Net::Context::VERIFY_NONE, 9, false,
         "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");

      Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), context);
      Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, path, Poco::Net::HTTPMessage::HTTP_1_1);
      Poco::Net::HTTPResponse response;

      session.sendRequest(request);
      std::istream &rs = session.receiveResponse(response);
      std::cout << response.getStatus() << " " << response.getReason() << std::endl;
      
      if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED) 
      {
         std::ofstream ofs(filePath, std::fstream::binary);
         Poco::StreamCopier::copyStream(rs, ofs);
      }
   }
   catch(const std::exception& e)
   {
      std::cerr << e.what() << '\n';
      result = false;
   }
   
   return result;
}
