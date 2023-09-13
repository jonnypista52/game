#include "./basicError.h"

bool negError(int code, const char* errorMessage){
    if(code < 0){
        if(errorMessage != NULL){
            printf("ERROR: %s\n", errorMessage);
        }
        return false;
    }
    return true;
}