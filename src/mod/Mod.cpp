#include "Mod.h"

#include <ll/api/mod/RegisterHelper.h>

#include "examples/event/Event.h"
#include "examples/command/Command.h"

namespace mainmod {

MainMod& MainMod::getInstance() {
    static MainMod instance;
    return instance;
}

bool MainMod::load() {
    mSelf.getLogger().info("Loaded!");
    return true;
}

bool MainMod::enable() {
    eventListenerPtr = new EventListener();
    eventListenerPtr->registerEvents();
    registerCommands();
    mSelf.getLogger().info("Enabled!");
    return true;
}

bool MainMod::disable() {
    eventListenerPtr->unregisterEvents();
    mSelf.getLogger().info("Disabled!");
    return true;
}

bool MainMod::unload() {
    mSelf.getLogger().info("Unloaded!");
    return true;
}

} // namespace plugin

LL_REGISTER_MOD(mainmod::MainMod, mainmod::MainMod::getInstance());