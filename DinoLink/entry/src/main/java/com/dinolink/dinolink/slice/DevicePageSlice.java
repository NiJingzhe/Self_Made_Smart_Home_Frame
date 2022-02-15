package com.dinolink.dinolink.slice;

import com.dinolink.dinolink.ResourceTable;
import com.dinolink.dinolink.domin.item;
import com.dinolink.dinolink.provider.itemProvider;
import ohos.aafwk.ability.AbilitySlice;
import ohos.aafwk.content.Intent;
import ohos.agp.components.ListContainer;

import java.util.ArrayList;

public class DevicePageSlice extends AbilitySlice {

    ListContainer listContainer;

    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setUIContent(ResourceTable.Layout_ability_device_page);
        //找到listcontainer
        listContainer = (ListContainer) findComponentById(ResourceTable.Id_list_container);

        // 创建集合并给集合添加数据
        ArrayList<item> itemList = initData();

        int index = intent.getIntParam("device_id", -2);
        String state = intent.getStringParam("device_state");
        itemList.get(index).setState(state);
        //创建一个Item的管理员对象（适配器）
        //并把要展示的所有数据和要加载的页面传过去
        itemProvider ip = new itemProvider(itemList, this);
        //把适配器交给列表容器组件
        listContainer.setItemProvider(ip);
    }

    public ArrayList<item> initData() {
        ArrayList<item> list = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            list.add(new item(ResourceTable.Media_switch_off, "device" + i, "OFF"));
        }
        return list;
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
