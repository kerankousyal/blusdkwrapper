var exec = require('cordova/exec');

exports.init = function (arg0, successCallback, errorCallback) {
    exec(successCallback, errorCallback, 'BluProvisionWrapper', 'init', [arg0]);
};

exports.startScan = function (arg0, successCallback, errorCallback) {
    var errorCallback = function(obj) {
        onError(obj);
    };

    var successCallback = function(obj) {
        onSuccess(obj);
    };
    exec(successCallback, errorCallback, 'BluProvisionWrapper', 'startScan', [arg0]);
};

exports.stopScan = function (arg0, successCallback, errorCallback) {
    var errorCallback = function(obj) {
      onError(obj);
    };

    var successCallback = function(obj) {
      onSuccess(obj);
    };
    exec(successCallback, errorCallback, 'BluProvisionWrapper', 'startStop', [arg0]);
};

exports.connectToBeacon = function (arg0, successCallback, errorCallback) {
    var errorCallback = function(obj) {
      onError(obj);
    };

    var successCallback = function(obj) {
      onSuccess(obj);
    };
    exec(successCallback, errorCallback, 'BluProvisionWrapper', 'connectToBeacon', [arg0]);
};

exports.disconnectBeacon = function (arg0, successCallback, errorCallback) {
  var errorCallback = function(obj) {
      onError(obj);
  };

  var successCallback = function(obj) {
      onSuccess(obj);
  };
    exec(successCallback, errorCallback, 'BluProvisionWrapper', 'disconnectBeacon', [arg0]);
};

exports.configureBeacon = function (arg0, successCallback, errorCallback) {
    var errorCallback = function(obj) {
      onError(obj);
    };

    var successCallback = function(obj) {
      onSuccess(obj);
    };
    exec(successCallback, errorCallback, 'BluProvisionWrapper', 'configureBeacon', [arg0]);
};

exports.updateScanRules = function (arg0, successCallback, errorCallback) {
    var errorCallback = function(obj) {
      onError(obj);
    };

    var successCallback = function(obj) {
      onSuccess(obj);
    };
    exec(successCallback, errorCallback, 'BluProvisionWrapper', 'updateScanRules', [arg0]);
};
