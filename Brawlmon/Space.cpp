#include "Space.h"

Space::Space()
{
	dynamicActors.clear();
	staticActors.clear();
}

void Space::update() 
{
	for (auto const& actor : dynamicActors) 
	{
		actor->sweep(staticActors);
	}
}