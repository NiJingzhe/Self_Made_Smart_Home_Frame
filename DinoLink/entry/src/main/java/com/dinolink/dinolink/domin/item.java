package com.dinolink.dinolink.domin;

public class item {

    private int img;
    private String deviceName;
    private String deviceState;

    public item() {
    }

    public item(int img_, String deviceName_, String deviceState_) {
        img = img_;
        deviceName = deviceName_;
        deviceState = deviceState_;
    }

    public String getDeviceName() {
        return deviceName;
    }

    public void setDeviceName(String deviceName_) {
        deviceName = deviceName_;
    }

    public String getDeviceState() {
        return deviceState;
    }

    public int getImg() {
        return img;
    }

    public void setImage(int img_) {
        img = img_;
    }

    public void setState(String state) {
        deviceState = state;
    }

}
