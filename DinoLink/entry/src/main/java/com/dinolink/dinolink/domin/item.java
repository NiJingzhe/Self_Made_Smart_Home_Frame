package com.dinolink.dinolink.domin;

public class item {

    private int img;
    private String deviceName;

    public item(int img_,String deviceName_){
        img = img_;
        deviceName = deviceName_;
    }

    public String getDeviceName(){
        return deviceName;
    }

    public int getImg(){
        return img;
    }

    public void setDeviceName(String deviceName_){
        deviceName = deviceName_;
    }

    public void setImage(int img_){
        img = img_;
    }

}
