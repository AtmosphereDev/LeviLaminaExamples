#pragma once

#include <ll/api/event/EventBus.h>

// make us not necessary to write ll::event for every namespace member
using namespace ll::event;

class EventListener {
private:
  std::vector<ListenerPtr> listeners; // holds pointers to listeners

public:
  void registerEvents();
  void unregisterEvents();
};