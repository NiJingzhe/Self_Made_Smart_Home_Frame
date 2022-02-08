package com.dinolink.dinolink;

import ohos.ace.ability.AceAbility;
import ohos.aafwk.content.Intent;

public class settingPage extends AceAbility {
    @Override
    public void onStart(Intent intent) {
        setInstanceName("default3");
        super.onStart(intent);
    }

    @Override
    public void onStop() {
        super.onStop();
    }
}
