#include "BMPFile.h"

BMPHeader& BMPFile::GetBMPHeader() {
    return bmp_header_;
}

DIBHeader& BMPFile::GetDIBHeader() {
    return dib_header_;
}