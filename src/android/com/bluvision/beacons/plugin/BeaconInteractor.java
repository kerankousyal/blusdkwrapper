package com.bluvision.beacons.plugin;

import com.bluvision.beeks.sdk.constants.BeaconType;
import com.bluvision.beeks.sdk.domainobjects.Beacon;
import com.bluvision.beeks.sdk.interfaces.BeaconListener;
import com.bluvision.beeks.sdk.util.BeaconManager;

import android.content.Context;

import java.util.ArrayList;
import java.util.List;

public class BeaconInteractor implements BeaconListener{
    private BeaconManager mBeaconManager;
    private List<Beacon> beaconList = new ArrayList<>();
    private BeaconCallback mBeaconCallback;

    public init(Context context, BeaconCallback beaconCallback){
      mBeaconManager = BluVisionManagerHandler.getInstance(context).getBeaconManager();
      mBeaconManager.addBeaconListener(this);
      mBeaconManager.addRuleToIncludeScanByType(BeaconType.S_BEACON);
      mBeaconCallback = beaconCallback;
    }

    public void startScan(){
      mBeaconManager.startScan();
      scanning = true;
    }

    public void stopScan() {
        if (scanning) {
            mBeaconManager.stopScan();
            scanning = false;
        }
    }

    @Override
    public void onBeaconFound(final Beacon beacon) {
        if (beacon != null) {
          beaconList.add(beacon);
          if (mBeaconCallback != null){
              mBeaconCallback.beaconFound(beacon)
          }
        }
    }

    @Override
    public void bluetoothIsNotEnabled() {
        //"Please activate your Bluetooth connection"
    }

    //When BeaconInteractor is being destroyed
    public void clear() {
       mBeaconManager.removeBeaconListener(this);
    }

}
