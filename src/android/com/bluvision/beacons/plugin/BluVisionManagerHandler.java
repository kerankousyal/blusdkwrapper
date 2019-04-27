package com.bluvision.beacons.plugin;

import com.bluvision.sdk.beacons.BeaconManager;

import android.content.Context;

public class BluVisionManagerHandler {
    private static BeaconManager mBeaconManager;

    public static BeaconManager getInstance(Context context, BeaconManager.BeaconListener listener){
        if (mBeaconManager == null){
            mBeaconManager = new BeaconManager(context, listener);
        }
        return mBeaconManager;
    }
}
