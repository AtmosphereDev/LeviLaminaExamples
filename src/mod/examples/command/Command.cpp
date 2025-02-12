#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/command/CommandHandle.h>

#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/server/commands/CommandSelector.h>
#include <mc/server/commands/CommandSelectorResults.h>

#include <mc/world/actor/player/Player.h>

#include "../../examples/form/Form.h"

// make us not necessary to write ll::command for every namespace member
using namespace ll::command;

struct ExampleParams {
  CommandSelector<Player> player; // player argument
  enum class FormEnum { simple, modal, custom } form; // enum argument
  bool open = false;
};

void registerCommands() {
  CommandRegistrar& cmdRegistrar = CommandRegistrar::getInstance();

  // create command
  auto& exampleCmd = cmdRegistrar.getOrCreateCommand("example", "example description.");

  // register command
  exampleCmd.overload().execute([](CommandOrigin const& origin, CommandOutput& output) {
    output.success("Hello from example command!");
  });

  // register second command variant with exampleparams
  // required(<name of argument>) means command cannot be runned without this argument
  // optional(<name of argument>) means it could be skipped when executing so you need to check if it not null. Better to not making enums optional
  exampleCmd.overload<ExampleParams>().required("player").required("form").optional("open").execute([](CommandOrigin const& origin, CommandOutput& output, ExampleParams const& args) {
    std::string data;
    auto iterator = args.player.results(origin).data;
    // get all selected players, all because of @a, @s and etc
    for (Player* player : *iterator) {
      data += " " + player->getRealName();
    }

    // open form or not
    if (!args.open) {
      output.success("Hello from example command with enum " + std::to_string((int)args.form) + " with" + data);
    } else {
      Player* player = static_cast<Player*>(origin.getEntity());
      switch (args.form) {
        case ExampleParams::FormEnum::simple:
          sendSimpleForm(player); // test simple form
          break;
        case ExampleParams::FormEnum::modal:
          sendModalForm(player); // test modal form
          break;
        case ExampleParams::FormEnum::custom:
          sendCustomForm(player); // test custom form
          break;
      }
      output.success("Hello from example command with enum " + std::to_string((int)args.form) + " with" + data);
    }
  });
}