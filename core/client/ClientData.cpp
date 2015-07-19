#include "ClientData.h"

namespace core
{

ClientData::ClientData()
		: Id(-1), Username(""), Channel(""), RequestId(0)
{

}

ClientData::ClientData(std::string username, long id)
		: Id(id), Username(username), Channel(""), RequestId(0)
{

}

ClientData::~ClientData()
{

}

bool ClientData::operator==(const ClientData& d) const
{
	return this->Id == d.Id;
}

bool ClientData::operator<(const ClientData& d) const
{
	return this->Id > d.Id;
}

}
;
