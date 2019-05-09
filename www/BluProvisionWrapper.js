var exec = require('cordova/exec');

exports.init = function (arg0, successCallback, errorCallback) {
    exec(successCallback, errorCallback, 'BluProvisionWrapper', 'init', [arg0]);
};

exports.startScan = function (arg0, successCallback, errorCallback) {
    exec(successCallback, errorCallback, 'BluProvisionWrapper', 'startScan', [arg0]);
};

exports.stopScan = function (arg0, successCallback, errorCallback) {
    exec(successCallback, errorCallback, 'BluProvisionWrapper', 'stopScan', [arg0]);
};

exports.provision = function (arg0, successCallback, errorCallback) {
    exec(successCallback, errorCallback, 'BluProvisionWrapper', 'provision', [arg0]);
};

exports.getTemplate = function (arg0, successCallback, errorCallback) {
    exec(successCallback, errorCallback, 'BluProvisionWrapper', 'getTemplate', [arg0]);
};

exports.signIn = function (arg0, successCallback, errorCallback) {
    exec(successCallback, errorCallback, 'BluProvisionWrapper', 'signIn', [arg0]);
};

exports.signOut = function (arg0, successCallback, errorCallback) {
    exec(successCallback, errorCallback, 'BluProvisionWrapper', 'signOut', [arg0]);
};
