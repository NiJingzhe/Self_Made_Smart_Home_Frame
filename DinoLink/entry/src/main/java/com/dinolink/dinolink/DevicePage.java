package com.dinolink.dinolink;

import com.dinolink.dinolink.slice.DevicePageSlice;
import ohos.aafwk.ability.Ability;
import ohos.aafwk.content.Intent;

public class DevicePage extends Ability {
    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setMainRoute(DevicePageSlice.class.getName());
    }
}
