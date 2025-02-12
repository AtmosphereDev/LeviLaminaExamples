#include "Event.h"

// You should include events you wanna use
// Search them from this scope ll/api/event/ on github
#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/event/player/PlayerSneakEvent.h>

// include if you wanna use something from ServerPlayer
#include <mc/server/ServerPlayer.h>

// Register basic events
void EventListener::registerEvents() {
  EventBus& bus = EventBus::getInstance();

  // register player joining event
  auto playerJoinPtr = bus.emplaceListener<PlayerJoinEvent>([](PlayerJoinEvent& ev) {
    ServerPlayer& player = ev.self();
    player.sendMessage("Hello from example!");
  });

  // register player sneaking event
  auto playerSneakPtr = bus.emplaceListener<PlayerSneakingEvent>([](PlayerSneakingEvent& ev) {
    ServerPlayer& player = ev.self();
    player.sendMessage("Yo why are you sneaking?");
  });

  // save pointers to vector to unregister them in future
  listeners.emplace_back(playerJoinPtr);
  listeners.emplace_back(playerSneakPtr);
}

// Unregister events for clear and safe unloading (helps if you wanna reload your mod)
void EventListener::unregisterEvents() {
  EventBus& bus = EventBus::getInstance();
  for (ListenerPtr ptr : listeners) {
    bus.removeListener(ptr);
  }
}