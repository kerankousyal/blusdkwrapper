package com.bluvision.beacons.plugin;

import com.bluvision.sdk.beacons.Beacon;
import com.bluvision.sdk.cloud.Error;
import com.bluvision.sdk.cloud.Template;
import com.bluvision.sdk.cloud.User;

import java.util.List;

public interface BeaconInteractorCallback {
    void beaconFound(Beacon beacon);

    void beaconLost(Beacon beacon);

    void signInSuccess(User user);

    void signInFailure(Error error);

    void enableBluetooth();

    void requestLocationPermissions();

    void loadTemplateSucess(List<? extends Template> list);

    void loadTemplateError(String s);

    void provisionSuccess();

    void provisionError(String message);

    void provisionStatusChange(String s);

    void provisiondescriptionChange(String s);
}
