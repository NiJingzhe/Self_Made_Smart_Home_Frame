package com.dinolink.dinolink.provider;

import com.dinolink.dinolink.ResourceTable;
import com.dinolink.dinolink.domin.item;
import com.dinolink.dinolink.slice.DeviceOperatorSlice;
import ohos.aafwk.ability.AbilitySlice;
import ohos.aafwk.content.Intent;
import ohos.agp.components.*;

import java.util.ArrayList;
import java.util.Objects;

public class itemProvider extends BaseItemProvider {
    private ArrayList<item> list;
    private AbilitySlice as;
    //public DirectionalLayout dl;

    public itemProvider(ArrayList<item> list_, AbilitySlice as_) {
        this.list = list_;
        this.as = as_;
    }

    public ArrayList<item> getList() {
        return list;
    }

    public void setList(ArrayList<item> list) {
        this.list = list;
    }

    public AbilitySlice getAs() {
        return as;
    }

    public void setAs(AbilitySlice as) {
        this.as = as;
    }

    @Override
    public int getCount() {
        return list.size();
    }

    @Override
    public Object getItem(int i) {
        if (list != null && i >= 0 && i <= list.size()) {
            return list.get(i);
        }
        return null;
    }

    @Override
    public long getItemId(int i) {
        return i;
    }

    @Override
    public Component getComponent(int i, Component component, ComponentContainer componentContainer) {
        DirectionalLayout dl;
        if (component != null) {
            dl = (DirectionalLayout) component;
        } else {
            //获取每一个item的布局对象
            dl = (DirectionalLayout) LayoutScatter.getInstance(as).parse(ResourceTable.Layout_list_item, null, false);
        }

        //获取每一个item的数据
        item item = list.get(i);
        //把数据加载到布局中

        Text device_name = (Text) dl.findComponentById(ResourceTable.Id_device_name);
        device_name.setText(item.getDeviceName());

        Image img = (Image) dl.findComponentById(ResourceTable.Id_img_button);
        int resourceId = Objects.equals(item.getDeviceState(), "OFF") ? ResourceTable.Media_switch_off : ResourceTable.Media_switch_on;
        img.setImageAndDecodeBounds(resourceId);
        img.setClickable(true);
        img.setClickedListener(new Component.ClickedListener() {
            @Override
            public void onClick(Component component) {
                Image img = (Image) component;
                switch (item.getDeviceState()) {
                    case "OFF":
                        img.setImageAndDecodeBounds(ResourceTable.Media_switch_on);
                        item.setState("ON");
                        break;
                    case "ON":
                        img.setImageAndDecodeBounds(ResourceTable.Media_switch_off);
                        item.setState("OFF");
                        break;
                    default:
                        break;
                }

            }
        });

        dl.setClickable(true);
        dl.setLongClickable(false);
        dl.setClickedListener((clickedComponent) -> {
            DirectionalLayout clickedDl = (DirectionalLayout) clickedComponent;
            Text clicked_Device_name = (Text) clickedDl.findComponentById(ResourceTable.Id_device_name);
            Intent dlClickedIntent = new Intent();
            dlClickedIntent.setParam("device_name", clicked_Device_name.getText());
            dlClickedIntent.setParam("device_state", item.getDeviceState());
            dlClickedIntent.setParam("item_id", i);
            as.presentForResult(new DeviceOperatorSlice(), dlClickedIntent, 0);
        });

        return dl;

    }

}
