#include <iostream> 
#include <opencv2/core/core.hpp>
#include <cstddef>
#include <stdexcept>
#include <opencv2/highgui/highgui.hpp>
#include <unistd.h>

#define VERSION VERSION_STR(EXT_VER)
#define VERSION_STR(X) _VERSION_STR(X)
#define _VERSION_STR(X) #X
#define DATETIME __DATE__ " " __TIME__
struct options {
  bool use_url = 0;
  std::string url;
  bool use_camera = 0;
  int camera_id = 0;
  bool view_camera = 0;
  bool verbose = 0;
};

std::string version = "Version ("  VERSION  ") Created on: "  DATETIME; 

std::string help_text = "\t-u <url>: read from url\n" \
	"\t-c <camera-id>: use camera_id\n" \
	"\t-o: view camera output\n" \
	"\t-v: verbose mode\n" \
	"\t-h: view this help text\n"
	"\t-V: view version\n";
	

struct options get_and_set_options(int argc, char* argv[])
{
  struct options options;
  int c;
  while((c = getopt(argc, argv, "hu:c:ovV")) != -1) 
  {
    switch(c)
    {
      case 'u':
        options.use_url = true;
        options.url = optarg;
        break;
      case 'c':
        options.use_camera = true;
        try
        {
           options.camera_id = std::stoi(optarg);
        }
        catch (std::invalid_argument& e) 
        {
           std::cerr << "ERROR: invalid argument given: " << e.what() << std::endl;
           exit(EXIT_FAILURE);
        }
        catch (std::out_of_range& e) 
        {
           std::cerr << "ERROR: out of range argument given: " << e.what() << std::endl;
           exit(EXIT_FAILURE);
        }
        break;
      case 'o':
        options.view_camera = true;
        break;
      case 'v':
        options.verbose = true;
        std::clog << "Verbose logging enabled" << std::endl;
        break;
      case 'V':
        std::clog << version << std::endl;
        exit(EXIT_SUCCESS);
        break;
      case 'h':
        std::clog << version << std::endl;
        std::clog << help_text << std::endl;
        exit(EXIT_SUCCESS);
        break;
      case '?':
        std::cerr << help_text << std::endl;
        exit(EXIT_FAILURE);
        break;
      default:
        abort();
        break;
     }
   }
   if (options.use_camera && options.use_url)
   {
     std::cerr << "ERROR: You can only use camera or url, not both. Exiting..." << std::endl;
     exit(EXIT_FAILURE);
   }
   return options;
}

int main(int argc, char* argv[])
{
  struct options options = get_and_set_options(argc, argv);
  if (options.verbose) {
    std::clog << "Exiting..." << std::endl;
  }
  return EXIT_SUCCESS;
}
