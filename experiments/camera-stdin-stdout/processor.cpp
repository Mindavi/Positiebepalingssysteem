#include "ImageReader.h"
#include "print_image.h"

int main(int argc, char* argv[])
{
  imagereader::ImageReader reader;
  cv::Mat image;
  while (1)
  {
    imagereader::ImageReaderStatus status = reader.TryDecode(image);
    switch(status)
    {
      case imagereader::ImageReaderStatus::kImageRead:
        break;
      case imagereader::ImageReaderStatus::kNotDone:
        continue;
      case imagereader::ImageReaderStatus::kZeroByte:
        //debug_print()
        exit(EXIT_SUCCESS);
      case imagereader::ImageReaderStatus::kEmptyInvalidFrame:
        //debug_print()
        exit(EXIT_FAILURE);
      case imagereader::ImageReaderStatus::kWarning:
        //debug_print()
        continue;
      default:
        //debug_print()
        exit(EXIT_FAILURE);
    }
    // image was read
    
  }
}
