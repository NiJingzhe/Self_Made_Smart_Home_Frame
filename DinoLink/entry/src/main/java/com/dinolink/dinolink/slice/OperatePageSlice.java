package com.dinolink.dinolink.slice;

import com.dinolink.dinolink.ResourceTable;
import ohos.aafwk.ability.AbilitySlice;
import ohos.aafwk.content.Intent;
import ohos.agp.colors.RgbColor;
import ohos.agp.components.AbsButton;
import ohos.agp.components.ComponentState;
import ohos.agp.components.Switch;
import ohos.agp.components.Text;
import ohos.agp.components.element.ShapeElement;
import ohos.agp.components.element.StateElement;

public class OperatePageSlice extends AbilitySlice {
    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setUIContent(ResourceTable.Layout_ability_operate_page);

        String deviceName = intent.getStringParam("device_name");

        Text title = (Text) findComponentById(ResourceTable.Id_title_device_name);
        title.setText(deviceName);

        Text deviceStateText = (Text) findComponentById(ResourceTable.Id_device_state_text);
        deviceStateText.setText(deviceStateText.getText() + "关");

        // 开启状态下滑块的样式
        ShapeElement elementThumbOn = new ShapeElement();
        elementThumbOn.setShape(ShapeElement.OVAL);
        elementThumbOn.setRgbColor(RgbColor.fromArgbInt(0xFFFFFFFF));
        elementThumbOn.setCornerRadius(50);
        // 关闭状态下滑块的样式
        ShapeElement elementThumbOff = new ShapeElement();
        elementThumbOff.setShape(ShapeElement.OVAL);
        elementThumbOff.setRgbColor(RgbColor.fromArgbInt(0xDDFFFFFF));
        elementThumbOff.setCornerRadius(50);
        // 开启状态下轨迹样式
        ShapeElement elementTrackOn = new ShapeElement();
        elementTrackOn.setShape(ShapeElement.RECTANGLE);
        elementTrackOn.setRgbColor(RgbColor.fromArgbInt(0xFF4DDB7C));
        elementTrackOn.setCornerRadius(100);
        // 关闭状态下轨迹样式
        ShapeElement elementTrackOff = new ShapeElement();
        elementTrackOff.setShape(ShapeElement.RECTANGLE);
        elementTrackOff.setRgbColor(RgbColor.fromArgbInt(0xFF808080));
        elementTrackOff.setCornerRadius(100);

        Switch deviceSwitch = (Switch) findComponentById(ResourceTable.Id_device_switch);
        deviceSwitch.setTrackElement(trackElementInit(elementTrackOn, elementTrackOff));
        deviceSwitch.setThumbElement(thumbElementInit(elementThumbOn, elementThumbOff));
        deviceSwitch.setCheckedStateChangedListener(new AbsButton.CheckedStateChangedListener() {
            @Override
            public void onCheckedChanged(AbsButton button, boolean isChecked) {
                if (isChecked) {
                    deviceStateText.setText("设备状态: 开");
                } else {
                    deviceStateText.setText("设备状态: 关");
                }
            }
        });

    }

    private StateElement trackElementInit(ShapeElement on, ShapeElement off) {
        StateElement trackElement = new StateElement();
        trackElement.addState(new int[]{ComponentState.COMPONENT_STATE_CHECKED}, on);
        trackElement.addState(new int[]{ComponentState.COMPONENT_STATE_EMPTY}, off);
        return trackElement;
    }

    private StateElement thumbElementInit(ShapeElement on, ShapeElement off) {
        StateElement thumbElement = new StateElement();
        thumbElement.addState(new int[]{ComponentState.COMPONENT_STATE_CHECKED}, on);
        thumbElement.addState(new int[]{ComponentState.COMPONENT_STATE_EMPTY}, off);
        return thumbElement;
    }


    @Override
    public void onActive() {
        super.onActive();
    }

    @Override
    public void onForeground(Intent intent) {
        super.onForeground(intent);
    }

    @Override
    public void onStop() {
        Text deviceStateText = (Text) findComponentById(ResourceTable.Id_device_state_text);
        deviceStateText.setText(ResourceTable.Id_device_state_text);
    }
}