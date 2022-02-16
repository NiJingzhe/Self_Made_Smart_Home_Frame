package com.dinolink.dinolink;

import com.dinolink.dinolink.slice.SettingPageSlice;
import ohos.aafwk.ability.Ability;
import ohos.aafwk.content.Intent;

public class SettingPage extends Ability {
    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setMainRoute(SettingPageSlice.class.getName());
    }
}
