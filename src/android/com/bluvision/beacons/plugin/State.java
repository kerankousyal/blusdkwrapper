package com.bluvision.beacons.plugin;

public enum State {
  CONNECTED("connected"),
  DISCONNECTED("disconnected"),
  CONNECTION_FAIL("connection_fail");

  private String mState;
  private State(String str) {
      this.mState = str;
  }

  public String getStringState() {
      return this.mState;
  }
}
