#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include "utils.h"

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

std::string format( std::vector<std::string> input)
{
	auto format = boost::format(*input.begin());

	for (auto iter = input.begin() + 1; iter != input.end(); ++iter)
		format = format % *iter;

	return format.str();
}

boost::tokenizer<boost::char_separator<char>> tokenize(std::string input, std::string sep)
{
	return boost::tokenizer<boost::char_separator<char>>(input, boost::char_separator<char>(sep.c_str()));
}

int getTokensCount(boost::tokenizer<boost::char_separator<char>>& tokens)
{
	int n = 0;
	for (auto iter = tokens.begin(); iter != tokens.end(); ++iter)
		++n;
	return n;
}

bool checkFields(rapidjson::Document& doc, std::vector<std::string> fields)
{
	for ( auto fieldIter = fields.begin(); fieldIter != fields.end(); ++fieldIter )
		if (!doc.HasMember((*fieldIter).c_str()))
			return false;

	return true;
}

}

}

#endif /* UTILS_UTILS_H_ */
