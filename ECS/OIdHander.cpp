#include "pch.h"
#include "OIdHander.h"

OIdHander oIdHander = OIdHander();
extern const unsigned int MAX_OBJECTS;

OIdHander::OIdHander()
{
	{
		for (unsigned int i = 0; i < MAX_OBJECTS; ++i)
		{
			mAvailableIds.push(i);
		}
	}
}
