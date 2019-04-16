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

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;
import java.util.concurrent.ConcurrentHashMap;

public class BeaconInteractor implements BeaconListener, BeaconConfigurationListener{
    private BeaconManager mBeaconManager;
    private List<Beacon> beaconList = new ArrayList<>();
    private BeaconCallback mBeaconCallback;
    private boolean scanning;
    private Beacon sBeacon;
    private Context context;

    public void init(Context context, BeaconCallback beaconCallback){
          this.context = context;
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
              mBeaconCallback.beaconFound(beacon);
          }
        }
    }

    @Override
    public void bluetoothIsNotEnabled() {
        //"Please activate your Bluetooth connection"
    }

    @Override
    public void onFailedToUpdateFirmware(int i) {

    }

    public void connectToBeacon(Beacon beacon, String password){
      //if(beaconList != null && beaconList.size() > 0){
          //Beacon beacon = beaconList.get(beaconIndex);
          //if(beacon.getDevice().getName().equals(beaconName)){
            if(beacon.getBeaconType() == BeaconType.S_BEACON){
                sBeacon = (SBeacon)beacon;
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
            }
          //}

          if(mBeacon.getBeaconType()==BeaconType.I_BEACON){
               //Toast.makeText(getActivity(),((IBeacon)mBeacon).getUuid(),Toast.LENGTH_LONG).show();
               //Toast.makeText(getActivity(),String.valueOf(((IBeacon)mBeacon).getMajor()),Toast.LENGTH_LONG).show();
               //Toast.makeText(getActivity(), String.valueOf(((IBeacon) mBeacon).getMinor()), Toast.LENGTH_LONG).show();
          }

          if(mBeacon.getBeaconType()==BeaconType.EDDYSTONE_URL_BEACON){
               //Toast.makeText(getActivity(),((EddystoneURLBeacon)mBeacon).getURL(),Toast.LENGTH_LONG).show();
           }
      //}
    }

    public void disconnectBeacon(Beacon beacon){
      //if(beaconList != null && beaconList.size() > 0){
          //Beacon beacon = beaconList.get(beaconIndex);
          if(beacon.getDevice().getBondState() == BluetoothDevice.BOND_BONDED){
              ((SBeacon)beacon).disconnect();
          }
        //}
    }

    @Override
    public void onConnect(boolean connected, boolean authenticated) {
        if(connected && authenticated){
            ((SBeacon)sBeacon).alert(true, true);
            ConfigurableBeacon configurableBeacon = (ConfigurableBeacon)sBeacon;
            configurableBeacon.readIBeaconUUID();
            mBeaconCallback.updateConnectionState(State.CONNECTED);
        }else{
            mBeaconCallback.updateConnectionState(State.CONNECTION_FAIL);
        }

    }


    @Override
    public void onDisconnect() {
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
