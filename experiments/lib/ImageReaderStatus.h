#ifndef IMAGEREADER_CODE_H_
#define IMAGEREADER_CODE_H_

namespace imagereader {

enum ImageReaderStatus {
  kImageRead = 0,
  kNotDone = 1,
  kZeroByte = -1,
  kEmptyInvalidFrame = -2,
  kWarning = -3
};

} // namespace imagereader

#endif /* end of include guard: IMAGEREADER_CODE_H_ */
