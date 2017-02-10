import cv2
import sys
import numpy as np

class ImageReaderStatus:
    ImageRead, NotDone, ZeroByte, EmptyInvalidFrame, Warning = range(5)

class ImageReader:
    def __init__(self):
        self.data = ""
        self.skip = True
        self.imgready = False
        self.ff = False
        self.readbytes = -1
        self.print_flag = False
        self.data_buffer_size = 10240
        self.status = ImageReaderStatus.NotDone

    def decode(self):
        output = []
        data_buffer = []
        self.status = ImageReaderStatus.NotDone
        if self.readbytes != 0:
            data_buffer = sys.stdin.read(self.data_buffer_size)
            for i in range(0, len(data_buffer)):
                c = data_buffer[i]
                #print type(c)
                if self.print_flag == True:
                    sys.stdout.write(c)

                if self.ff and (ord(c) == 0xd8):
                    self.skip = False
                    self.data += chr(0xff)

                if self.ff and (ord(c) == 0xd9):
                    self.imgready = True
                    self.data += chr(0xd9)
                    self.skip = True

                self.ff = (ord(c) == 0xff)
                if not self.skip:
                    self.data += (c)

                if self.imgready:
                    if len(self.data) > 0:
                        npdata = np.fromstring(self.data, np.uint8)
                        output = cv2.imdecode(npdata, 1)

                        if len(output) > 0:
                            self.status = ImageReaderStatus.ImageRead
                        else:
                            self.status = ImageReaderStatus.EmptyInvalidFrame
                    else:
                        self.status = Warning

                    self.imgready = False
                    self.skip = True
                    self.data = ""
        else:
            self.status = ImageReaderStatus.ZeroByte
        data_buffer = ""
        return (self.status == ImageReaderStatus.ImageRead), output
