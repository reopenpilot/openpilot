#include "selfdrive/frogpilot/ui/qt/offroad/sounds_settings.h"

FrogPilotSoundsPanel::FrogPilotSoundsPanel(FrogPilotSettingsWindow *parent) : FrogPilotListWidget(parent) {
  const std::vector<std::tuple<QString, QString, QString, QString>> soundsToggles {
    {"AlertVolumeControl", tr("Alert Volume Controller"), tr("Control the volume level for each individual sound in openpilot."), "../frogpilot/assets/toggle_icons/icon_mute.png"},
    {"DisengageVolume", tr("Disengage Volume"), tr("Related alerts:\n\nAdaptive Cruise Disabled\nParking Brake Engaged\nBrake Pedal Pressed\nSpeed too Low"), ""},
    {"EngageVolume", tr("Engage Volume"), tr("Related alerts:\n\nNNFF Torque Controller loaded\nopenpilot engaged"), ""},
    {"PromptVolume", tr("Prompt Volume"), tr("Related alerts:\n\nCar Detected in Blindspot\nSpeed too Low\nSteer Unavailable Below 'X'\nTake Control, Turn Exceeds Steering Limit"), ""},
    {"PromptDistractedVolume", tr("Prompt Distracted Volume"), tr("Related alerts:\n\nPay Attention, Driver Distracted\nTouch Steering Wheel, Driver Unresponsive"), ""},
    {"RefuseVolume", tr("Refuse Volume"), tr("Related alerts:\n\nopenpilot Unavailable"), ""},
    {"WarningSoftVolume", tr("Warning Soft Volume"), tr("Related alerts:\n\nBRAKE!, Risk of Collision\nTAKE CONTROL IMMEDIATELY"), ""},
    {"WarningImmediateVolume", tr("Warning Immediate Volume"), tr("Related alerts:\n\nDISENGAGE IMMEDIATELY, Driver Distracted\nDISENGAGE IMMEDIATELY, Driver Unresponsive"), ""},

    {"CustomAlerts", tr("Custom Alerts"), tr("Enable custom alerts for openpilot events."), "../frogpilot/assets/toggle_icons/icon_green_light.png"},
    {"GreenLightAlert", tr("Green Light Alert"), tr("Get an alert when a traffic light changes from red to green."), ""},
    {"LeadDepartingAlert", tr("Lead Departing Alert"), tr("Get an alert when the lead vehicle starts departing when at a standstill."), ""},
    {"LoudBlindspotAlert", tr("Loud Blindspot Alert"), tr("Enable a louder alert for when a vehicle is detected in the blindspot when attempting to change lanes."), ""},
  };

  for (const auto &[param, title, desc, icon] : soundsToggles) {
    AbstractControl *soundsToggle;

    if (param == "AlertVolumeControl") {
      FrogPilotParamManageControl *alertVolumeControlToggle = new FrogPilotParamManageControl(param, title, desc, icon);
      QObject::connect(alertVolumeControlToggle, &FrogPilotParamManageControl::manageButtonClicked, [this]() {
        showToggles(alertVolumeControlKeys);
      });
      soundsToggle = alertVolumeControlToggle;
    } else if (alertVolumeControlKeys.find(param) != alertVolumeControlKeys.end()) {
      if (param == "WarningImmediateVolume") {
        soundsToggle = new FrogPilotParamValueControl(param, title, desc, icon, 25, 100, "%");
      } else {
        soundsToggle = new FrogPilotParamValueControl(param, title, desc, icon, 0, 100, "%");
      }

    } else if (param == "CustomAlerts") {
      FrogPilotParamManageControl *customAlertsToggle = new FrogPilotParamManageControl(param, title, desc, icon);
      QObject::connect(customAlertsToggle, &FrogPilotParamManageControl::manageButtonClicked, [this]() {
        std::set<QString> modifiedCustomAlertsKeys = customAlertsKeys;

        if (!hasBSM) {
          modifiedCustomAlertsKeys.erase("LoudBlindspotAlert");
        }

        showToggles(modifiedCustomAlertsKeys);
      });
      soundsToggle = customAlertsToggle;

    } else {
      soundsToggle = new ParamControl(param, title, desc, icon);
    }

    addItem(soundsToggle);
    toggles[param.toStdString()] = soundsToggle;

    tryConnect<ToggleControl>(soundsToggle, &ToggleControl::toggleFlipped, this, updateFrogPilotToggles);
    tryConnect<FrogPilotParamManageControl>(soundsToggle, &FrogPilotParamManageControl::manageButtonClicked, this, &FrogPilotSoundsPanel::openParentToggle);
    tryConnect<FrogPilotParamValueControl>(soundsToggle, &FrogPilotParamValueControl::valueChanged, this, updateFrogPilotToggles);

    QObject::connect(soundsToggle, &AbstractControl::showDescriptionEvent, [this]() {
      update();
    });
  }

  QObject::connect(parent, &FrogPilotSettingsWindow::closeParentToggle, this, &FrogPilotSoundsPanel::hideToggles);
  QObject::connect(uiState(), &UIState::offroadTransition, this, &FrogPilotSoundsPanel::updateCarToggles);
}

void FrogPilotSoundsPanel::updateCarToggles() {
  auto carParams = params.get("CarParamsPersistent");
  if (!carParams.empty()) {
    AlignedBuffer aligned_buf;
    capnp::FlatArrayMessageReader cmsg(aligned_buf.align(carParams.data(), carParams.size()));
    cereal::CarParams::Reader CP = cmsg.getRoot<cereal::CarParams>();

    hasBSM = CP.getEnableBsm();
  } else {
    hasBSM = true;
  }

  hideToggles();
}

void FrogPilotSoundsPanel::showToggles(std::set<QString> &keys) {
  setUpdatesEnabled(false);

  for (auto &[key, toggle] : toggles) {
    toggle->setVisible(keys.find(key.c_str()) != keys.end());
  }

  setUpdatesEnabled(true);
  update();
}

void FrogPilotSoundsPanel::hideToggles() {
  for (auto &[key, toggle] : toggles) {
    bool subToggles = alertVolumeControlKeys.find(key.c_str()) != alertVolumeControlKeys.end() ||
                      customAlertsKeys.find(key.c_str()) != customAlertsKeys.end();
    toggle->setVisible(!subToggles);
  }

  update();
}
