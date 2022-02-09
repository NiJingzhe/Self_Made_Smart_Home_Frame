package com.dinolink.dinolink;

import com.dinolink.dinolink.slice.OperatePageSlice;
import ohos.aafwk.ability.Ability;
import ohos.aafwk.content.Intent;

public class OperatePage extends Ability {
    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setMainRoute(OperatePageSlice.class.getName());
    }
}
