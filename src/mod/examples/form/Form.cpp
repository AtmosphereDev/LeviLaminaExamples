#include "Form.h"

#include <ll/api/form/SimpleForm.h>
#include <ll/api/form/ModalForm.h>
#include <ll/api/form/CustomForm.h>

using namespace ll::form;

void sendSimpleForm(Player* player) {
  SimpleForm form = SimpleForm("Title example text", "Content example text");

  form.appendButton("example button without icon");

  form.appendButton("example button with path icon", "textures/items/diamond_shovel", "path");

  form.appendButton("example button with url icon", "https://wiki.bedrock.dev/assets/images/misc/dead_bush.png", "url");

  form.sendTo(*player, [](Player& formPlayer, int selected, FormCancelReason) {
    if (selected == -1) formPlayer.sendMessage("You closed form");
    else formPlayer.sendMessage("You selected " + std::to_string(selected));
  });
}

void sendModalForm(Player* player) {
  ModalForm form = ModalForm("Title example text", "Content example text", "up text", "down text");

  form.sendTo(*player, [](Player& formPlayer, ModalFormResult selected, FormCancelReason) {
    if (!selected) formPlayer.sendMessage("You closed form");
    else formPlayer.sendMessage("You selected " + (bool)selected);
  });
}

void sendCustomForm(Player* player) {
  CustomForm form = CustomForm("Title example text");

  form.appendLabel("label");
  form.appendInput("input1", "input");
  form.appendToggle("toggle", "toggle");
  form.appendSlider("slider", "slider", 0, 100, 1);
  form.appendStepSlider("stepSlider", "stepSlider", {"a", "b", "c"});
  form.appendDropdown("dropdown", "dropdown", {"a", "b", "c"});

  form.sendTo(*player, [](Player& formPlayer, CustomFormResult const& data, FormCancelReason) {
    if (!data) formPlayer.sendMessage("You closed form");
    else {
      std::string outputData = "You selected";
      for (auto [name, result] : *data) {
        static auto logDebugResult = [&](CustomFormElementResult const& var) {
            if (std::holds_alternative<uint64_t>(var)) {
              outputData += " name: " + name + " value: " + std::to_string(std::get<uint64_t>(var));
            } else if (std::holds_alternative<double>(var)) {
              outputData += " name: " + name + " value: " + std::to_string(std::get<double>(var));
            } else if (std::holds_alternative<std::string>(var)) {
              outputData += " name: " + name + " value: " + std::get<std::string>(var);
            }
        };
        formPlayer.sendMessage(outputData);
    }
    }
  });
}