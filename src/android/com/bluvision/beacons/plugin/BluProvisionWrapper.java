package com.bluvision.beacons.plugin;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;
import com.bluvision.beeks.sdk.domainobjects.Beacon;
import org.apache.cordova.PluginResult;
import org.apache.cordova.PluginResult.Status;
import java.util.UUID;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * This class echoes a string called from JavaScript.
 */
public class BluProvisionWrapper extends CordovaPlugin implements BeaconCallback{

    private BeaconInteractor mBeaconInteractor;
    private CallbackContext scanCallbackContext;
    private CallbackContext connectionCallbackContext;

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        if (action.equals("init")) {
            this.init(callbackContext);
            return true;
          } else if (action.equals("startScan")) {
            this.startScan(callbackContext);
            return true;
          } else if (action.equals("stopScan")) {
            this.stopScan();
            return true;
          } else if (action.equals("connectToBeacon")) {
            JSONObject request = args.getJSONObject(0);
            this.connectToBeacon(request, callbackContext);
            return true;
          } else if (action.equals("disconnectBeacon")) {
            JSONObject request = args.getJSONObject(0);
            this.disconnectBeacon(request, callbackContext);
            return true;
          } else if (action.equals("configureBeacon")) {
            JSONObject request = args.getJSONObject(0);
            this.configureBeacon(request, callbackContext);
            return true;
        }
        return false;
    }

    private void init(CallbackContext callbackContext) {
        Context context = this.cordova.getActivity().getApplicationContext();
        mBeaconInteractor = new BeaconInteractor();
        mBeaconInteractor.init(context, this);
    }

    //1. Create a profile for scanning -> S-Beacon
    private void updateScanRules(JSONObject message, CallbackContext callbackContext) {

    }

    //2. Send scan result js BluProvisionWrapper
    private void startScan(CallbackContext callbackContext) {
      scanCallbackContext = callbackContext;
      mBeaconInteractor.startScan();
    }

    private void stopScan() {
        scanCallbackContext = null;
        mBeaconInteractor.stopScan();
    }

    //3. Send scan result js BluProvisionWrapper
    private void setScanResults(Beacon beacon) {
        JSONObject result = new JSONObject();
        convertBeaconToJsonObject(beacon);
        try {
            result.put("BEACON_FOUND",  beacon);
          } catch (JSONException e) {
              e.printStackTrace();
          }
          PluginResult pr = new PluginResult(Status.OK, result);
          pr.setKeepCallback(true);
          if (this.scanCallbackContext != null) {
              this.scanCallbackContext.sendPluginResult(pr);
          }
    }
    //3. Connect to a Beacon
    private void connectToBeacon(JSONObject message, CallbackContext callbackContext) throws JSONException{
      if (message != null && message.length() > 0) {
        connectionCallbackContext = callbackContext;
        //int beaconIndex = message.getInt(String.valueOf(0));
        //String beaconName = message.getString(String.valueOf(1));
        String password = message.getString(String.valueOf(1));
        Beacon beacon = new Gson().fromJson(message.getString(String.valueOf(0)), Beacon.class);
        mBeaconInteractor.connectToBeacon(beacon, password);
      }
    }

    //5. Disconnect the Beacon
    private void disconnectBeacon(JSONObject message, CallbackContext callbackContext) throws JSONException{
      if (message != null && message.length() > 0) {
        connectionCallbackContext = callbackContext;
        //int beaconIndex = message.getInt(String.valueOf(0));
        //String beaconName = message.getString(String.valueOf(1));
        Beacon beacon = new Gson().fromJson(message.getString(String.valueOf(0)), Beacon.class);
        mBeaconInteractor.disconnectBeacon(beacon);
      }
    }

    //6. Configure a beacon ->
    private void configureBeacon(JSONObject message, CallbackContext callbackContext) {
    }

    @Override
    public void beaconFound(Beacon beacon){
      setScanResults(beacon);
    }

    //4. update connection status to BluProvisionWrapper -> beacon statelistener -> update BluProvisionWrapper
    @Override
    public void updateConnectionState(State state){
      JSONObject result = new JSONObject();
      try {
          result.put("CONNECTION_UPDATE",  state.getStringState());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        PluginResult pr = new PluginResult(Status.OK, result);
        pr.setKeepCallback(true);
        if (this.connectionCallbackContext != null) {
            this.connectionCallbackContext.sendPluginResult(pr);
        }
    }

    @Override
    public void updateBeaconMetaData(UUID uuid){
      JSONObject result = new JSONObject();
      try {
          result.put("METADATA_UPDATE",  uuid.toString());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        PluginResult pr = new PluginResult(Status.OK, result);
        pr.setKeepCallback(true);
        if (this.connectionCallbackContext != null) {
            this.connectionCallbackContext.sendPluginResult(pr);
        }
    }

    public String convertBeaconToJsonObject(Beacon beacon){
        return new Gson().toJson(beacon);
    }
}
