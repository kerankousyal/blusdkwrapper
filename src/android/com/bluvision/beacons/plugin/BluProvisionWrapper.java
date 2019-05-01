package com.bluvision.beacons.plugin;

import com.bluvision.sdk.beacons.Beacon;
import com.bluvision.sdk.cloud.Error;
import com.bluvision.sdk.cloud.Template;
import com.bluvision.sdk.cloud.User;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.PluginResult;
import org.apache.cordova.PluginResult.Status;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.content.Context;

import java.util.Date;
import java.util.List;

/**
 * This class echoes a string called from JavaScript.
 */
public class BluProvisionWrapper extends CordovaPlugin implements BeaconInteractorCallback{

    private BeaconInteractor mBeaconInteractor;

    // private Context applicationContext;
    // private BluvisionCallback callback;
    // private MainActivity activity;

    // public BluProvisionWrapper(Context applicationContext, MainActivity activity) {
    //     this.applicationContext = applicationContext;
    //     this.callback = activity;
    //     this.activity = activity;
    // }
    private CallbackContext scanCallbackContext;
    private CallbackContext connectionCallbackContext;
    private CallbackContext templateCallbackContext;

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        if (action.equals("init")) {
            this.init(callbackContext);
            //this.init();
            return true;
        } else if (action.equals("signIn")) {
            String token = args.getString(0);
            this.signIn(callbackContext, token);
            //this.signIn(token);
            return true;
        } else if (action.equals("getTemplate")) {
            String beacon = args.getString(0);
            this.getTemplates(callbackContext, beacon);
            //this.getTemplates(beacon);
            return true;
        } else if (action.equals("provision")) {
            JSONObject data = args.getJSONObject(0);
            String beacon = data.getString("address");
            String beaconName = data.getString("name");
            int template = data.getInt("templateId");
            this.provisionBeacon(callbackContext, beacon, template, beaconName);
            //this.provisionBeacon(beacon, template);
            return true;
        } else if (action.equals("startScan")) {
            this.startScan(callbackContext);
            //this.startScan();
            return true;
        } else if (action.equals("stopScan")) {
            this.stopScan();
            return true;
        }
        return false;
    }

    private void init(CallbackContext callbackContext) {
    //private void init() {
        Context context = this.cordova.getActivity().getApplicationContext();
        Activity activity = this.cordova.getActivity();
        mBeaconInteractor = new BeaconInteractor();
        mBeaconInteractor.init(context, this, activity);
    }

    private void provisionBeacon(CallbackContext callbackContext, String beacon, int template, String beaconName) {
    //private void provisionBeacon(String beacon, int template) {
        connectionCallbackContext = callbackContext;
        mBeaconInteractor.provisionBeacon(beacon, template, beaconName);
    }
    private void getTemplates(CallbackContext callbackContext, String address) {
    //private void getTemplates(String address) {
        templateCallbackContext = callbackContext;
        mBeaconInteractor.loadTemplates(address);
    }

    private void signIn(CallbackContext callbackContext, String token) {
    //private void signIn(String token) {
        scanCallbackContext = callbackContext;
        mBeaconInteractor.signIn(token);
    }

    private void startScan(CallbackContext callbackContext) {
    //private void startScan() {
      scanCallbackContext = callbackContext;
      mBeaconInteractor.startScan();
    }

    private void stopScan() {
        scanCallbackContext = null;
        mBeaconInteractor.stopScan();
    }

    @Override
    public void beaconFound(Beacon beacon){
        JSONObject result = new JSONObject();
        try {
            result.put("code",  "Beacon_Found");
            result.put("name",  beacon.getBluetoothDevice().getName());
            result.put("address",  beacon.getBluetoothDevice().getAddress());
            result.put("type",  beacon.getTypeString());
            //callback.wrapperResults("BEACON", result.toString());
        } catch (JSONException e) {
            e.printStackTrace();
        }
         PluginResult pr = new PluginResult(Status.OK, result);
         pr.setKeepCallback(true);
         if (this.scanCallbackContext != null) {
             this.scanCallbackContext.sendPluginResult(pr);
         }
    }

    @Override
    public void beaconLost(Beacon beacon) {
        JSONObject result = new JSONObject();
        try {
            result.put("code",  "Beacon_Lost");
            result.put("name",  beacon.getBluetoothDevice().getName());
            result.put("address",  beacon.getBluetoothDevice().getAddress());
            result.put("type",  beacon.getTypeString());
            //callback.wrapperResults("BEACON", result.toString());
        } catch (JSONException e) {
            e.printStackTrace();
        }
         PluginResult pr = new PluginResult(Status.OK, result);
         pr.setKeepCallback(true);
         if (this.scanCallbackContext != null) {
             this.scanCallbackContext.sendPluginResult(pr);
         }
    }

    @Override
    public void signInSuccess(User user) {
        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("code", "SignIn_Success");
            jsonObject.put("user_name", user.getUsername());
            jsonObject.put("user_email", user.getEmail());
            jsonObject.put("project_id", user.getProjectId());
            jsonObject.put("project_name", user.getProjectName());
            jsonObject.put("current_project", user.getCurrentProject());
            //callback.wrapperResults("SIGIN", jsonObject.toString());
        } catch (JSONException e) {
            e.printStackTrace();
        }
         PluginResult pr = new PluginResult(Status.OK, jsonObject);
         pr.setKeepCallback(true);
         if (this.scanCallbackContext != null) {
             this.scanCallbackContext.sendPluginResult(pr);
         }
    }

    @Override
    public void signInFailure(Error error) {
        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("Fail", "SignIn_Failed");
            jsonObject.put("error_code", error.getCode());
            jsonObject.put("error_message", error.getMessage());
            //callback.wrapperResults("SIGNINFAIL", jsonObject.toString());
        } catch (JSONException e) {
            e.printStackTrace();
        }
         PluginResult pr = new PluginResult(Status.ERROR, jsonObject);
         pr.setKeepCallback(false);
         if (this.scanCallbackContext != null) {
             this.scanCallbackContext.sendPluginResult(pr);
             scanCallbackContext = null;
         }
    }

    @Override
    public void enableBluetooth() {
        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("Fail", "Bluetooth");
            //callback.wrapperResults("ENABLEBT", jsonObject.toString());
        } catch (JSONException e) {
            e.printStackTrace();
        }
         PluginResult pr = new PluginResult(Status.ERROR, jsonObject);
         pr.setKeepCallback(false);
         if (this.scanCallbackContext != null) {
             this.scanCallbackContext.sendPluginResult(pr);
             scanCallbackContext = null;
         }
    }

    @Override
    public void requestLocationPermissions() {
        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("Fail", "Location");
            //callback.wrapperResults("ENABLELOCATION", jsonObject.toString());
        } catch (JSONException e) {
            e.printStackTrace();
        }
         PluginResult pr = new PluginResult(Status.ERROR, jsonObject);
         pr.setKeepCallback(false);
         if (this.scanCallbackContext != null) {
             this.scanCallbackContext.sendPluginResult(pr);
             scanCallbackContext = null;
         }
    }

    @Override public void loadTemplateSucess(List<? extends Template> list) {
      JSONObject resultJson = new JSONObject();
        try {
            JSONArray jsonArray = new JSONArray();
            for(Template template: list) {
                JSONObject jsonObject = new JSONObject();
                jsonObject.put("templateId", template.getTemplateId());
                jsonObject.put("name", template.getName());
//                jsonObject.put("description", template.getDescription());
//                jsonObject.put("configType", template.getConfigType());
//                jsonObject.put("iBeacon", template.hasIBeacon());
//                jsonObject.put("sBeacon", template.hasSBeacon());
//                jsonObject.put("dateCreated", template.getDateCreated().toString());
//                jsonObject.put("dateUpdated", template.getDateUpdated().toString());
//                jsonObject.put("projectId", template.getProjectId());
//                jsonObject.put("BLUFI_TEMPLATE_SECURITY_OPEN", 0);
//                jsonObject.put("BLUFI_TEMPLATE_SECURITY_WEP", 1);
//                jsonObject.put("BLUFI_TEMPLATE_SECURITY_WPA2", 2);
//                jsonObject.put("BLUFI_TEMPLATE_SECURITY_ENTERPRISE", 3);
                jsonArray.put(jsonObject);
            }
            resultJson.put("templates", jsonArray);
            //callback.wrapperResults("TEMPLATE", resultJson.toString());
        } catch (JSONException e) {
            e.printStackTrace();
        }
         PluginResult pr = new PluginResult(Status.OK, resultJson);
         pr.setKeepCallback(false);
         if (this.templateCallbackContext != null) {
             this.templateCallbackContext.sendPluginResult(pr);
             templateCallbackContext = null;
         }
    }

    @Override public void loadTemplateError(String s) {
        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("Template_Fail", s);
            //callback.wrapperResults("TEMPLATEFAIL", jsonObject.toString());
        } catch (JSONException e) {
            e.printStackTrace();
        }
         PluginResult pr = new PluginResult(Status.ERROR, jsonObject);
         pr.setKeepCallback(false);
         if (this.templateCallbackContext != null) {
             this.templateCallbackContext.sendPluginResult(pr);
             templateCallbackContext = null;
         }
    }

    @Override public void provisionSuccess() {
        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("code", "Provision_Sucess");
        } catch (JSONException e) {
            e.printStackTrace();
        }
         PluginResult pr = new PluginResult(Status.OK, jsonObject);
         pr.setKeepCallback(false);
         if (this.connectionCallbackContext != null) {
             this.connectionCallbackContext.sendPluginResult(pr);
             connectionCallbackContext = null;
         }
    }

    @Override public void provisionError(String message) {
        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("result", "ERROR");
            jsonObject.put("reason", message);
        } catch (JSONException e) {
            e.printStackTrace();
        }
         PluginResult pr = new PluginResult(Status.ERROR, jsonObject);
         pr.setKeepCallback(false);
         if (this.connectionCallbackContext != null) {
             this.connectionCallbackContext.sendPluginResult(pr);
             connectionCallbackContext = null;
         }
    }

    @Override public void provisionStatusChange(String s) {
        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("code", "Status_Changed");
            jsonObject.put("result", s);
        } catch (JSONException e) {
            e.printStackTrace();
        }
         PluginResult pr = new PluginResult(Status.OK, jsonObject);
         pr.setKeepCallback(true);
         if (this.connectionCallbackContext != null) {
             this.connectionCallbackContext.sendPluginResult(pr);
         }
    }

    @Override public void provisiondescriptionChange(String s) {
        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("code", "Desc_Changed");
            jsonObject.put("result", s);
        } catch (JSONException e) {
            e.printStackTrace();
        }
         PluginResult pr = new PluginResult(Status.OK, jsonObject);
         pr.setKeepCallback(true);
         if (this.connectionCallbackContext != null) {
             this.connectionCallbackContext.sendPluginResult(pr);
         }
    }
}
