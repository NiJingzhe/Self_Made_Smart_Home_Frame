package com.dinolink.dinolink.slice;

import com.dinolink.dinolink.ResourceTable;
import ohos.aafwk.ability.AbilitySlice;
import ohos.aafwk.content.Intent;
import ohos.agp.components.TickTimer;

public class MainAbilitySlice extends AbilitySlice implements TickTimer.TickListener {

    TickTimer tickTimer;



    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setUIContent(ResourceTable.Layout_ability_main);


        tickTimer = findComponentById(ResourceTable.Id_ticktimer);
        tickTimer.setCountDown(false);
        tickTimer.setTickListener(this);
        tickTimer.setFormat("ss");
        tickTimer.start();
    }

    @Override
    public void onTickTimerUpdate(TickTimer tickTimer){
        if (tickTimer.getText().equals("04")){
            tickTimer.stop();
            present(new DevicePageSlice(),new Intent());
            terminate();
        }
    }

    @Override
    public void onActive() {
        super.onActive();

    }

    @Override
    public void onForeground(Intent intent) {
        super.onForeground(intent);
    }
}
