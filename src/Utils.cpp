//
// Created by stefan on 7/25/21.
//

#include "Utils.h"

namespace Utils
{
    std::string getEnv(const std::string &strName, const std::string &strDefault)
    {
        std::string strResult;
        const char *envValue = std::getenv(strName.c_str());

        return envValue ? envValue : strDefault;
        return strResult;
    }
}