package com.bluvision.beacons.plugin;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;
import com.bluvision.beeks.sdk.domainobjects.Beacon;
import org.apache.cordova.PluginResult;
import org.apache.cordova.PluginResult.Status;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * This class echoes a string called from JavaScript.
 */
public class BluProvisionWrapper extends CordovaPlugin implements BeaconCallback{

    private BeaconInteractor mBeaconInteractor
    private CallbackContext scanCallbackContext;

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
      if (action.equals("init")) {
            JSONObject request = args.getString(0);
            this.init(request, callbackContext);
            return true;
      } else if (action.equals("updateScanRules")) {
            JSONObject request = args.getString(0);
            this.updateScanRules(request, callbackContext);
            return true;
        } else if (action.equals("startScan")) {
            JSONObject request = args.getString(0);
            this.startScan(request, callbackContext);
            return true;
        } else if (action.equals("setScanResults")) {
            JSONObject request = args.getString(0);
            this.setScanResults(request, callbackContext);
            return true;
        } else if (action.equals("connectToBeacon")) {
            JSONObject request = args.getString(0);
            this.connectToBeacon(request, callbackContext);
            return true;
        } else if (action.equals("disconnectBeacon")) {
            JSONObject request = args.getString(0);
            this.disconnectBeacon(request, callbackContext);
            return true;
        } else if (action.equals("configureBeacon")) {
            JSONObject request = args.getString(0);
            this.configureBeacon(request, callbackContext);
            return true;
        }
        return false;
    }

    private void init(String message, CallbackContext callbackContext) {
        Context context = this.cordova.getActivity().getApplicationContext();
        mBeaconInteractor = new BeaconInteractor();
        mBeaconInteractor.init(context, this);

    }
    private void coolMethod(String message, CallbackContext callbackContext) {
        if (message != null && message.length() > 0) {
            callbackContext.success(message);
        } else {
            callbackContext.error("Expected one non-empty string argument.");
        }
    }

    //1. Create a profile for scanning -> S-Beacon
    private void updateScanRules(JSONObject message, CallbackContext callbackContext) {

    }

    //2. Send scan result js BluProvisionWrapper
    private void startScan(JSONObject message, CallbackContext callbackContext) {
      scanCallbackContext = callbackContext;
      mBeaconInteractor.startScan();
    }

    //3. Send scan result js BluProvisionWrapper
    private void setScanResults(Beacon beacon) {
        JSONObject result = new JSONObject();
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
    private void connectToBeacon(JSONObject message, CallbackContext callbackContext) {

    }
    //4. update connection status to BluProvisionWrapper -> beacon statelistener -> update BluProvisionWrapper
    private void updateConnectionState(JSONObject message, CallbackContext callbackContext) {

    }
    //5. Disconnect the Beacon
    private void disconnectBeacon(JSONObject message, CallbackContext callbackContext) {
    }
    //6. Configure a beacon ->
    private void configureBeacon(JSONObject message, CallbackContext callbackContext) {
    }

    @Override
    public void beaconFound(Beacon beacon){
      setScanResults.(beacon);
    }
}
