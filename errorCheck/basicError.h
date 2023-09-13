#ifndef _errorCheck_basicError_h_
#define _errorCheck_basicError_h_

#include "../Global.h"

//* if the code is negative then returns false otherwhise true
//errorMessage is optional, if added it will print the included mesage
bool negError(int code, const char* errorMessage = NULL);



#endif