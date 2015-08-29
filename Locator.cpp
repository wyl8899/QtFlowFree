#include "Locator.h"

namespace instanceLocater {

LocatorRegistry* LocatorRegistry::singleton = nullptr;

LocatorRegistry *LocatorRegistry::instance() {
    if (singleton == nullptr)
        singleton = new LocatorRegistry;
    return singleton;
}

bool LocatorRegistry::hasRegistered(LocatorRegistry::Key key) {
    return registry.find(key) != registry.end();
}

void LocatorRegistry::__register(LocatorRegistry::Key key, void *value) {
    assert(!hasRegistered(key));
    registry[key] = value;
}

void LocatorRegistry::__unregister(LocatorRegistry::Key key) {
    assert(hasRegistered(key));
    registry.erase(key);
}

void *LocatorRegistry::__get(LocatorRegistry::Key key) {
    assert(hasRegistered(key));
    return registry[key];
}

}
