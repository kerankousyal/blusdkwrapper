package com.bluvision.beacons.plugin;

import com.bluvision.beeks.sdk.constants.BeaconType;
import com.bluvision.beeks.sdk.domainobjects.Beacon;
import com.bluvision.beeks.sdk.interfaces.BeaconListener;
import com.bluvision.beeks.sdk.util.BeaconManager;
import com.bluvision.beeks.sdk.constants.BeaconType;
import com.bluvision.beeks.sdk.domainobjects.Beacon;
import com.bluvision.beeks.sdk.domainobjects.ConfigurableBeacon;
import com.bluvision.beeks.sdk.domainobjects.EddystoneURLBeacon;
import com.bluvision.beeks.sdk.domainobjects.IBeacon;
import com.bluvision.beeks.sdk.domainobjects.SBeacon;
import com.bluvision.beeks.sdk.interfaces.BeaconConfigurationListener;
import com.bluvision.beeks.sdk.util.BeaconManager;

import android.content.Context;
import android.app.Activity;
import android.widget.Toast;

import java.util.HashMap;
import java.util.Map;
import java.util.UUID;
import java.util.concurrent.ConcurrentHashMap;

public class BeaconInteractor implements BeaconListener, BeaconConfigurationListener{
    private BeaconManager mBeaconManager;
    private Map<String, Beacon> beaconList = new HashMap<>();
    private BeaconCallback mBeaconCallback;
    private boolean scanning;
    private Beacon sBeacon;
    private Context context;

    public void init(Context context, BeaconCallback beaconCallback, Activity activity){
          this.context = context;
          this.activity = activity;
          mBeaconManager = BluVisionManagerHandler.getInstance(context).getBeaconManager();
          mBeaconManager.addBeaconListener(this);
          mBeaconManager.addRuleToIncludeScanByType(BeaconType.S_BEACON);
          mBeaconCallback = beaconCallback;
    }

    public void updateScanRules(String type){
      if(type.equals(BeaconType.I_BEACON.getStringType())){
        mBeaconManager.addRuleToIncludeScanByType(BeaconType.I_BEACON);
      } else if (type.equals(BeaconType.S_BEACON.getStringType())){
        mBeaconManager.addRuleToIncludeScanByType(BeaconType.S_BEACON);
      } else if (type.equals(BeaconType.CONFIGURABLE_BEACON.getStringType())){
        mBeaconManager.addRuleToIncludeScanByType(BeaconType.CONFIGURABLE_BEACON);
      } else if (type.equals(BeaconType.EDDYSTONE.getStringType())){
        mBeaconManager.addRuleToIncludeScanByType(BeaconType.EDDYSTONE);
      } else if (type.equals(BeaconType.EDDYSTONE_UID_BEACON.getStringType())){
        mBeaconManager.addRuleToIncludeScanByType(BeaconType.EDDYSTONE_UID_BEACON);
      } else if (type.equals(BeaconType.EDDYSTONE_TLM_BEACON.getStringType())){
        mBeaconManager.addRuleToIncludeScanByType(BeaconType.EDDYSTONE_TLM_BEACON);
      } else if (type.equals(BeaconType.EDDYSTONE_URL_BEACON.getStringType())){
        mBeaconManager.addRuleToIncludeScanByType(BeaconType.EDDYSTONE_URL_BEACON);
      } else {
        mBeaconManager.addRuleToIncludeScanByType(BeaconType.MOTION);
      }
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
      activity.runOnUiThread(new Runnable() {
          @Override
          public void run() {
              if (beacon != null) {
                  beaconList.put(beacon.getDevice().getAddress(), beacon);
                  if (mBeaconCallback != null){
                      mBeaconCallback.beaconFound(beacon);
                  }
              }
          }
      });
    }

    @Override
    public void bluetoothIsNotEnabled() {
        Toast.makeText(activity, "Please enable bluetooth",Toast.LENGTH_LONG).show();
    }

    @Override
    public void onFailedToUpdateFirmware(int i) {

    }

    public void connectToBeacon(String address, String type, String password){
          Beacon beacon = beaconList.get(address);
            if(type.equals(BeaconType.S_BEACON.getStringType())){
                sBeacon = (SBeacon)beacon;
            }
            ConcurrentHashMap<BeaconType,Beacon> beacons = beacon.getAssociations();
            for (Beacon beaconAssociated : beacons.values()){
                if(beaconAssociated.getBeaconType() == BeaconType.S_BEACON){
                    sBeacon = (SBeacon)beaconAssociated;
                }
            }
            if(sBeacon != null){
                ((SBeacon)sBeacon).setBeaconConfigurationListener(this);
                ((SBeacon)sBeacon).connect(context, password);
            }

          if(beacon.getBeaconType()==BeaconType.I_BEACON){
               Toast.makeText(activity, ((IBeacon)mBeacon).getUuid(),Toast.LENGTH_LONG).show();
               Toast.makeText(activity, String.valueOf(((IBeacon)mBeacon).getMajor()),Toast.LENGTH_LONG).show();
               Toast.makeText(activity, String.valueOf(((IBeacon) mBeacon).getMinor()), Toast.LENGTH_LONG).show();
          }

          if(beacon.getBeaconType()==BeaconType.EDDYSTONE_URL_BEACON){
               Toast.makeText(activity,((EddystoneURLBeacon)mBeacon).getURL(),Toast.LENGTH_LONG).show();
           }
    }

    public void disconnectBeacon(String address){
          Beacon beacon = beaconList.get(address);
          if(beacon.getDevice().getBondState() == BluetoothDevice.BOND_BONDED &&
            beacon.getBeaconType() == BeaconType.S_BEACON){
              ((SBeacon)beacon).disconnect();
          }
    }

    @Override
    public void onConnect(boolean connected, boolean authenticated) {
        if(connected && authenticated){
            ((SBeacon)sBeacon).alert(true, true);
            ConfigurableBeacon configurableBeacon = (ConfigurableBeacon)sBeacon;
            mBeaconCallback.updateBeaconMetaData(configurableBeacon.readIBeaconUUID());
            mBeaconCallback.updateBeaconMetaData(configurableBeacon.getDevice().getAddress());
            Toast.makeText(activity, "Connected "+sBeacon.getDevice().getName(),
                Toast.LENGTH_LONG).show();
            mBeaconCallback.updateConnectionState(State.CONNECTED);
        }else{
            Toast.makeText(activity, "Connection fail "+sBeacon.getDevice().getName(),
                Toast.LENGTH_LONG).show();
            mBeaconCallback.updateConnectionState(State.CONNECTION_FAIL);
        }

    }


    @Override
    public void onDisconnect() {
        Toast.makeText(activity, "disconnected "+sBeacon.getDevice().getName(),
            Toast.LENGTH_LONG).show();
        mBeaconCallback.updateConnectionState(State.DISCONNECTED);
    }

    @Override
    public void onCommandToNotConnectedBeacon() {

    }

    @Override
    public void onReadConnectionSettings(int i, int i1, int i2, int i3) {

    }

    @Override
    public void onSetConnectionSettings(int i, int i1, int i2, int i3) {

    }

    @Override
    public void onFailedToReadConnectionSettings() {

    }

    @Override
    public void onFailedToSetConnectionSettings() {

    }

    @Override
    public void onReadTemperature(double v) {

    }

    @Override
    public void onFailedToReadTemperature() {

    }

    @Override
    public void onConnectionExist() {

    }

    @Override
    public void onReadIBeaconUUID(UUID uuid) {
        mBeaconCallback.updateBeaconMetaData(uuid);
    }

    @Override
    public void onSetIBeaconUUID(UUID uuid) {

    }

    @Override
    public void onFailedToReadIBeaconUUID() {

    }

    @Override
    public void onFailedToSetIBeaconUUID() {

    }

    @Override
    public void onReadIBeaconMajorAndMinor(int i, int i1) {

    }

    @Override
    public void onSetIBeaconMajorAndMinor(int i, int i1) {

    }

    @Override
    public void onFailedToReadIBeaconMajorAndMinor() {

    }

    @Override
    public void onFailedToSetIBeaconMajorAndMinor() {

    }

    @Override
    public void onReadEddystoneUID(byte[] bytes, byte[] bytes1) {

    }

    @Override
    public void onSetEddystoneUID(byte[] bytes, byte[] bytes1) {

    }

    @Override
    public void onFailedToReadEddystoneUID() {

    }

    @Override
    public void onFailedToSetEddystoneUID() {

    }

    @Override
    public void onReadEddystoneURL(String s) {

    }

    @Override
    public void onSetEddystoneURL(String s) {

    }

    @Override
    public void onFailedToReadEddystoneURL() {

    }

    @Override
    public void onFailedToSetEddystoneURL() {

    }

    @Override
    public void onReadDeviceStatus(float v, float v1, short i) {

    }

    @Override
    public void onFailedToReadDeviceStatus() {

    }

    @Override
    public void onReadFrameTypeIntervalTxPower(byte b, byte b1, byte b2, float v, float v1) {

    }

    @Override
    public void onSetFrameTypeIntervalTxPower(byte b, byte b1, byte b2, float v, float v1) {

    }

    @Override
    public void onFailedToReadFrameTypeIntervalTxPower() {

    }

    @Override
    public void onFailedToSetFrameTypeIntervalTxPower() {

    }

    @Override
    public void onSetFrameTypeConnectionRates(byte b, byte b1, byte b2) {

    }

    @Override
    public void onReadFrameTypeConnectionRates(byte b, byte b1, byte b2) {

    }

    @Override
    public void onFailedToReadFrameTypeConnectionRates() {

    }

    @Override
    public void onFailedToSetFrameTypeConnectionRates() {

    }

    @Override
    public void onReadAdvertisementSettings(float v, float v1, float v2) {

    }

    @Override
    public void onSetAdvertisementSettings(float v, float v1, float v2) {

    }

    @Override
    public void onFailedToReadAdvertisementSettings() {

    }

    @Override
    public void onFailedToSetAdvertisementSettings() {

    }

    @Override
    public void onSetAccelerometerConfiguration() {

    }

    @Override
    public void onFailedToSetAccelerometerConfiguration() {

    }

    @Override
    public void onSetPassword(boolean b) {

    }

    @Override
    public void onUpdateFirmware(double v) {

    }

    //When BeaconInteractor is being destroyed
    public void clear() {
       mBeaconManager.removeBeaconListener(this);
    }

}
