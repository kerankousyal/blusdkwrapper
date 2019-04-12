package com.bluvision.beacons.plugin;

import android.content.Context;
import com.bluvision.beeks.sdk.util.BeaconManager;

public class BluVisionManagerHandler {
    private static BluVisionManagerHandler mBluVisionManagerHandler;
    private BeaconManager mBeaconManager;

    private BluVisionManagerHandler(Context context){
        createManager(context);
    }

    public static getInstance(Context context){
        if (mBluVisionManagerHandler == null){
            mBluVisionManagerHandler = new BluVisionManagerHandler(context);
        }
        return mBluVisionManagerHandler;
      }

    private void createManager(Context context) {
        mBeaconManager = new BeaconManager(context);
    }

    public void stopManager() {
        mBeaconManager.stop();
    }

    public BeaconManager getBeaconManager() {
        return mBeaconManager;
    }
}
