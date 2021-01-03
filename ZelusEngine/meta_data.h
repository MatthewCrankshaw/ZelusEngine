#pragma once
#include <string>

enum class EntityType {
	DEFERRED_LIGHTING,
	DEFERRED_GEOMETRY,
	HDR_PASS,
	REGULAR,
	SKYBOX,
	AXIS
};

class MetaData
{
private:
	int mId;
	std::string mName;
	EntityType mType;

	static int mNextId;
public:
	MetaData(std::string name, EntityType type);

	inline int GetId() {
		return mId;
	}

	inline std::string GetName() {
		return mName;
	}

	inline EntityType GetType() {
		return mType;
	}
};
