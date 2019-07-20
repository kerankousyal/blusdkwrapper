package com.bluvision.beacons.plugin;

import com.bluvision.sdk.beacons.Beacon;
import com.bluvision.sdk.beacons.BeaconManager;
import com.bluvision.sdk.beacons.Blufi;
import com.bluvision.sdk.beacons.SBeacon;
import com.bluvision.sdk.cloud.Device;
import com.bluvision.sdk.cloud.Error;
import com.bluvision.sdk.cloud.Location;
import com.bluvision.sdk.cloud.Provisioner;
import com.bluvision.sdk.cloud.Template;
import com.bluvision.sdk.cloud.User;
import com.bluvision.sdk.cloud.callbacks.LocationListCallback;
import com.bluvision.sdk.cloud.callbacks.ProvisioningCallback;
import com.bluvision.sdk.cloud.callbacks.UserCallback;
import com.bluvision.sdk.constants.Distance;
import com.bluvision.sdk.utilities.ErrorCode;

import android.app.Activity;
import android.content.Context;
import android.util.Log;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class BeaconInteractor implements BeaconManager.BeaconListener {
    private BeaconManager mBeaconManager;
    private Map<String, Beacon> beaconList = new HashMap<>();
    private Map<String, Template> templateList = new HashMap<>();
    private BeaconInteractorCallback mBeaconCallback;
    private boolean scanning;
    private Context context;
    private Activity activity;

    public void init(Context context, BeaconInteractorCallback beaconCallback, Activity activity) {
        this.context = context;
        this.activity = activity;
        mBeaconCallback = beaconCallback;
    }

    public void startScan() {
        if(mBeaconManager == null) {
            mBeaconManager = BluVisionManagerHandler.getInstance(context, this);
        }
        if (mBeaconManager != null && !scanning) {
            mBeaconManager.startScanning();
            scanning = true;
        }
    }

    public void stopScan() {
        if (mBeaconManager != null && scanning) {
            mBeaconManager.stopScanning();
            scanning = false;
            BluVisionManagerHandler.destroyManager();
            mBeaconManager = null;
        }
    }

    @Override
    public void onFound(final Beacon beacon) {
        if (beacon instanceof SBeacon) {
            beaconList.put(((SBeacon) beacon).getIdentifier().toString(), beacon);
            if (mBeaconCallback != null) {
                mBeaconCallback.beaconFound(beacon);
            }
        }


    }

    @Override
    public void onLost(final Beacon beacon) {
        if (beacon instanceof SBeacon) {
            beaconList.remove(((SBeacon) beacon).getIdentifier().toString());
            if (mBeaconCallback != null) {
                mBeaconCallback.beaconLost(beacon);
            }
        }
    }

    @Override
    public void onChange(Beacon beacon, Distance distance) {

    }

    @Override
    public void onScanningFail(int errorCode) {
        if (errorCode == ErrorCode.BEACON_SCANNER_BLUETOOTH_NOT_ENABLED) {
            mBeaconCallback.enableBluetooth();
        }

        if (errorCode == ErrorCode.BEACON_SCANNER_INSUFFICIENT_PERMISSIONS) {
            mBeaconCallback.requestLocationPermissions();
        }
    }

    public void signIn(String token) {
        User.AuthenticateWithAPIToken(token, context, new UserCallback() {
            @Override
            public void onComplete(User user, Error error) {
                Log.i("authenticate", "User " + user + "error " + error);
                if (user != null) {
                    mBeaconCallback.signInSuccess(user);
                    startScan();
                } else {
                    mBeaconCallback.signInFailure(error);
                    Log.i("authenticate", error.getMessage());
                }
            }
        });
    }

    public void signOut() {
        User user = User.getCurrentUser();
        if(user != null){
            user.signOut();
            beaconList.clear();
        }
    }

    public void loadTemplates(String id) {
        SBeacon beacon = (SBeacon) beaconList.get(id);
        templateList = new HashMap<>();
        if (beacon != null) {
            if (beacon instanceof Blufi) {
                Template.getBlufiTemplates(callback);
            } else {
                Template.getBeaconTemplates(beacon.getIdentifier().toString(), callback);
            }
        }
    }

    private Template.TemplateListCallback callback = new Template.TemplateListCallback() {
        @Override
        public void onComplete(List<? extends Template> list, Error error) {
            if (error == null) {
                //There are no templates for this device, please create one to continue
                mBeaconCallback.loadTemplateSucess(list);
                for (Template template : list) {
                    templateList.put("" + template.getTemplateId(), template);
                }
            } else {
                if (error.getCode() > 50000) {
                    mBeaconCallback.loadTemplateError("This device cannot be provisioned. Please contact support for assistance.");

                    if (error.getCode() == 50404) {
                        mBeaconCallback.loadTemplateError("Device already Provisioned. This Device is already provisioned for use with " +
                                                          "another project.");
                    }
                } else {
                    mBeaconCallback.loadTemplateError(error.getMessage());
                    Log.e("templates", error.getMessage());
                }
            }
        }
    };

    private void getLocations(final String beacon, final int template, final String beaconName, final String notes) {
        User.getCurrentUser().getCurrentProject().getLocations(new LocationListCallback() {
            @Override
            public void onComplete(List<Location> list, Error error) {
                if (list == null || list.size() == 0) {
                    Log.e("error", "for this sample we need a location");
                    return;
                }
                provision(list.get(0), beacon, template, beaconName, notes);
            }
        });

    }

    private void provision(Location location, String beacon, int template, String beaconName, String notes) {
        SBeacon mDevice = (SBeacon) beaconList.get(beacon);
        Provisioner mProvisioner = new Provisioner(mDevice, template, activity);

        mProvisioner.setLocationIdentifier(location.getLocationId());
        mProvisioner.setLatitude(25.8); // Get this from a map marker
        mProvisioner.setLongitude(80.2);
        mProvisioner.setDeviceName(beaconName);
        mProvisioner.setNotes(notes);

        mProvisioner.startProvisioning(new ProvisioningCallback() {
            @Override
            public void onSuccess(Device device) {
                mBeaconCallback.provisionSuccess();
            }

            @Override
            public void onError(Error error) {
                mBeaconCallback.provisionError(error.getMessage());
            }

            @Override
            public void onStatusChange(String s) {
                mBeaconCallback.provisionStatusChange(s);
            }

            @Override
            public void onDescriptionChange(String s) {
                mBeaconCallback.provisiondescriptionChange(s);
            }
        });
    }

    public void provisionBeacon(String beacon, int template, String beaconName, String notes) {
        getLocations(beacon, template, beaconName, notes);
    }
}
