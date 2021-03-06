#pragma once
#include "Blob.hpp"
#include "Operator.hpp"
#include "tinyxml2/tinyxml2.h"

namespace ravenscript
{
namespace utils
{

BlobPtr LoadFile(const char* path);
std::shared_ptr<tinyxml2::XMLDocument> LoadXmlFile(const char* path);
std::string ValueOrEmpty(const char* str);
Operator CharToOperator(char c);
char OperatorToChar(Operator op);
int GetOperatorPriority(Operator op);

}
}
