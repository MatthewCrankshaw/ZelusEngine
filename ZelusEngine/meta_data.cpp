#include "meta_data.h"

int MetaData::mNextId = 0;

MetaData::MetaData(std::string name, EntityType type)
{
	mName = name;
	mType = type;
	mId = mNextId;
	mNextId++;
}
