#!/usr/bin/env python3
from typing import Optional


class Service:
  def __init__(self, should_log: bool, frequency: float, decimation: Optional[int] = None):
    self.should_log = should_log
    self.frequency = frequency
    self.decimation = decimation


_services: dict[str, tuple] = {
  # service: (should_log, frequency, qlog decimation (optional))
  # note: the "EncodeIdx" packets will still be in the log
  "gyroscope": (True, 104., 104),
  "gyroscope2": (True, 100., 100),
  "accelerometer": (True, 104., 104),
  "accelerometer2": (True, 100., 100),
  "magnetometer": (True, 25.),
  "lightSensor": (True, 100., 100),
  "temperatureSensor": (True, 2., 200),
  "temperatureSensor2": (True, 2., 200),
  "gpsNMEA": (True, 9.),
  "deviceState": (True, 2., 1),
  "can": (True, 100., 2053),  # decimation gives ~3 msgs in a full segment
  "controlsState": (True, 100., 10),
  "pandaStates": (True, 10., 1),
  "peripheralState": (True, 2., 1),
  "radarState": (True, 20., 5),
  "roadEncodeIdx": (False, 20., 1),
  "liveTracks": (True, 20.),
  "sendcan": (True, 100., 139),
  "logMessage": (True, 0.),
  "errorLogMessage": (True, 0., 1),
  "liveCalibration": (True, 4., 4),
  "liveTorqueParameters": (True, 4., 1),
  "androidLog": (True, 0.),
  "carState": (True, 100., 10),
  "carControl": (True, 100., 10),
  "carOutput": (True, 100., 10),
  "longitudinalPlan": (True, 20., 10),
  "procLog": (True, 0.5, 15),
  "gpsLocationExternal": (True, 10., 10),
  "gpsLocation": (True, 1., 1),
  "ubloxGnss": (True, 10.),
  "qcomGnss": (True, 2.),
  "gnssMeasurements": (True, 10., 10),
  "clocks": (True, 0.1, 1),
  "ubloxRaw": (True, 20.),
  "livePose": (True, 20., 4),
  "liveLocationKalman": (True, 20.),
  "liveParameters": (True, 20., 5),
  "cameraOdometry": (True, 20., 10),
  "thumbnail": (True, 0.2, 1),
  "onroadEvents": (True, 1., 1),
  "carParams": (True, 0.02, 1),
  "roadCameraState": (True, 20., 20),
  "driverCameraState": (True, 20., 20),
  "driverEncodeIdx": (False, 20., 1),
  "driverStateV2": (True, 20., 10),
  "driverMonitoringState": (True, 20., 10),
  "wideRoadEncodeIdx": (False, 20., 1),
  "wideRoadCameraState": (True, 20., 20),
  "drivingModelData": (True, 20., 10),
  "modelV2": (True, 20.),
  "managerState": (True, 2., 1),
  "uploaderState": (True, 0., 1),
  "navInstruction": (True, 1., 10),
  "navRoute": (True, 0.),
  "navThumbnail": (True, 0.),
  "qRoadEncodeIdx": (False, 20.),
  "userFlag": (True, 0., 1),
  "microphone": (True, 10., 10),

  # debug
  "uiDebug": (True, 0., 1),
  "testJoystick": (True, 0.),
  "roadEncodeData": (False, 20.),
  "driverEncodeData": (False, 20.),
  "wideRoadEncodeData": (False, 20.),
  "qRoadEncodeData": (False, 20.),
  "livestreamWideRoadEncodeIdx": (False, 20.),
  "livestreamRoadEncodeIdx": (False, 20.),
  "livestreamDriverEncodeIdx": (False, 20.),
  "livestreamWideRoadEncodeData": (False, 20.),
  "livestreamRoadEncodeData": (False, 20.),
  "livestreamDriverEncodeData": (False, 20.),
  "customReservedRawData0": (True, 0.),
  "customReservedRawData1": (True, 0.),
  "customReservedRawData2": (True, 0.),

  # dp
  "controlsStateExt": (False, 100., 10),
  "longitudinalPlanExt": (False, 20., 5),
  "teToo": (False, 5),
  "lateralPlan": (False, 20., 5),
}
SERVICE_LIST = {name: Service(*vals) for
                idx, (name, vals) in enumerate(_services.items())}


def build_header():
  h = ""
  h += "/* THIS IS AN AUTOGENERATED FILE, PLEASE EDIT services.py */\n"
  h += "#ifndef __SERVICES_H\n"
  h += "#define __SERVICES_H\n"

  h += "#include <map>\n"
  h += "#include <string>\n"

  h += "struct service { std::string name; bool should_log; int frequency; int decimation; };\n"
  h += "static std::map<std::string, service> services = {\n"
  for k, v in SERVICE_LIST.items():
    should_log = "true" if v.should_log else "false"
    decimation = -1 if v.decimation is None else v.decimation
    h += '  { "%s", {"%s", %s, %d, %d}},\n' % \
         (k, k, should_log, v.frequency, decimation)
  h += "};\n"

  h += "#endif\n"
  return h


if __name__ == "__main__":
  print(build_header())