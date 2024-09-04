using Cxx = import "./include/c++.capnp";
$Cxx.namespace("cereal");

using Car = import "car.capnp";

@0xb526ba661d550a59;

# custom.capnp: a home for empty structs reserved for custom forks
# These structs are guaranteed to remain reserved and empty in mainline
# cereal, so use these if you want custom events in your fork.

# you can rename the struct, but don't change the identifier
struct FrogPilotCarControl @0x81c2f05a394cf4af {
  alwaysOnLateralActive @0 :Bool;
  fcwEventTriggered @1 :Bool;
  noEntryEventTriggered @2 :Bool;
  resumePressed @3 :Bool;
  steerSaturatedEventTriggered @4 :Bool;
}

struct FrogPilotCarState @0xaedffd8f31e7b55d {
  struct ButtonEvent {
    enum Type {
      lkas @0;
    }
  }

  alwaysOnLateralDisabled @0 :Bool;
  brakeLights @1 :Bool;
  dashboardSpeedLimit @2 :Float32;
  distanceLongPressed @3 :Bool;
  ecoGear @4 :Bool;
  hasMenu @5 :Bool;
  sportGear @6 :Bool;
  trafficModeActive @7 :Bool;
}

struct FrogPilotDeviceState @0xf35cc4560bbf6ec2 {
  freeSpace @0 :Int16;
  usedSpace @1 :Int16;
}

struct FrogPilotNavigation @0xda96579883444c35 {
  approachingIntersection @0 :Bool;
  approachingTurn @1 :Bool;
  navigationSpeedLimit @2 :Float32;
}

struct FrogPilotPlan @0x80ae746ee2596b11 {
  accelerationJerk @0 :Float32;
  accelerationJerkStock @1 :Float32;
  adjustedCruise @2 :Float32;
  dangerJerk @3 :Float32;
  desiredFollowDistance @4 :Float32;
  experimentalMode @5 :Bool;
  forcingStop @6 :Bool;
  frogpilotEvents @7: List(Car.CarEvent);
  lateralCheck @8 :Bool;
  laneWidthLeft @9 :Float32;
  laneWidthRight @10 :Float32;
  maxAcceleration @11 :Float32;
  minAcceleration @12 :Float32;
  redLight @13 :Bool;
  safeObstacleDistance @14 :Int32;
  safeObstacleDistanceStock @15 :Int32;
  slcOverridden @16 :Bool;
  slcOverriddenSpeed @17 :Float32;
  slcSpeedLimit @18 :Float32;
  slcSpeedLimitOffset @19 :Float32;
  speedJerk @20 :Float32;
  speedJerkStock @21 :Float32;
  speedLimitChanged @22 :Bool;
  stoppedEquivalenceFactor @23 :Int32;
  tFollow @24 :Float32;
  unconfirmedSlcSpeedLimit @25 :Float32;
  vCruise @26 :Float32;
  vtscControllingCurve @27 :Bool;
}

struct CustomReserved5 @0xa5cd762cd951a455 {
}

struct CustomReserved6 @0xf98d843bfd7004a3 {
}

struct CustomReserved7 @0xb86e6369214c01c8 {
}

struct CustomReserved8 @0xf416ec09499d9d19 {
}

struct CustomReserved9 @0xa1680744031fdb2d {
}
