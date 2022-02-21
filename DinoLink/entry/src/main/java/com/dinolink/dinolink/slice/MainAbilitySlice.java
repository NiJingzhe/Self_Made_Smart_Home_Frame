package com.dinolink.dinolink.slice;

import com.dinolink.dinolink.ResourceTable;
import ohos.aafwk.ability.AbilitySlice;
import ohos.aafwk.content.Intent;
import ohos.aafwk.content.Operation;
import ohos.agp.components.TickTimer;

public class MainAbilitySlice extends AbilitySlice implements TickTimer.TickListener {

    TickTimer tickTimer;

    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setUIContent(ResourceTable.Layout_ability_main);


        tickTimer = (TickTimer) findComponentById(ResourceTable.Id_ticktimer);
        tickTimer.setCountDown(false);
        tickTimer.setTickListener(this);
        tickTimer.setFormat("ss");
        tickTimer.start();
    }

    @Override
    public void onTickTimerUpdate(TickTimer tickTimer){
        if (tickTimer.getText().equals("04")) {
            tickTimer.stop();
            Intent toDevicePage = new Intent();
            Operation operation = new Intent.OperationBuilder()
                    .withDeviceId("")    // 设备Id，在本地上进行跳转可以为空，跨设备进行跳转则需要传入值
                    .withBundleName("com.dinolink.dinolink")    // 包名
                    .withAbilityName(".DevicePage")    // Ability页面的名称，在本地可以缺省前面的路径
                    .build();    // 构建代码
            toDevicePage.setOperation(operation);    // 将operation存入到intent中
            startAbility(toDevicePage);    // 实现Ability跳转
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
