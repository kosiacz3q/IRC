#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <string>
#include <vector>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

#include "../rapidjson/document.h"

namespace core
{

namespace utils
{

std::string format( std::vector<std::string> input);

boost::tokenizer<boost::char_separator<char>> tokenize(std::string input, std::string sep);

int getTokensCount(boost::tokenizer<boost::char_separator<char>>& tokens);

bool checkFields(rapidjson::Document& doc, std::vector<std::string> fields);

}

}

#endif /* UTILS_UTILS_H_ */
