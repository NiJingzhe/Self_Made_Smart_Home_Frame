package com.dinolink.dinolink;

import ohos.ace.ability.AceAbility;
import ohos.aafwk.content.Intent;

public class devicePage extends AceAbility {
    @Override
    public void onStart(Intent intent) {
        setInstanceName("default2");
        super.onStart(intent);
    }

    @Override
    public void onStop() {
        super.onStop();
    }
}
