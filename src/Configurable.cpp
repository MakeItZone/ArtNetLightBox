#include "Configurable.h"

void Configurable::Start()
{
    running = true;
}

void Configurable::Stop ()
{
    running = false;
}

Configurable::~Configurable() {
    delete configItems; //just in case it hasn't been cleaned up yet
}