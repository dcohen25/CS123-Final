#include "utils.h"

Utils::Utils()
{
}

Utils::~Utils(){

}

float Utils::getRandomValue(){
    return (float) rand() / RAND_MAX;
}
