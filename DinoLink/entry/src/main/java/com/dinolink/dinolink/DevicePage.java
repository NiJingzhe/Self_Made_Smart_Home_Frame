package com.dinolink.dinolink;

import com.dinolink.dinolink.slice.DeviceListSlice;
import com.dinolink.dinolink.slice.DeviceOperatorSlice;
import ohos.aafwk.ability.Ability;
import ohos.aafwk.content.Intent;

public class DevicePage extends Ability {
    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setMainRoute(DeviceListSlice.class.getName());
        super.addActionRoute("action.operate", DeviceOperatorSlice.class.getName());
    }
}
