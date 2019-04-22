package com.bluvision.beacons.plugin;

import com.bluvision.beeks.sdk.domainobjects.Beacon;

public interface BeaconCallback {
   public void beaconFound(Beacon beacon);
   public void updateConnectionState(State state);
   public void updateBeaconMetaData(String uuid);
}
