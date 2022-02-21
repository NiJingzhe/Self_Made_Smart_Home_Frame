package com.dinolink.dinolink.slice;

import com.dinolink.dinolink.ResourceTable;
import com.dinolink.dinolink.domin.item;
import com.dinolink.dinolink.provider.itemProvider;
import ohos.aafwk.ability.AbilitySlice;
import ohos.aafwk.content.Intent;
import ohos.aafwk.content.Operation;
import ohos.agp.components.Button;
import ohos.agp.components.ListContainer;
import ohos.data.DatabaseHelper;
import ohos.data.preferences.Preferences;

import java.util.ArrayList;

public class DeviceListSlice extends AbilitySlice {

    ListContainer listContainer;
    Intent intent_;
    ArrayList<item> itemList;

    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setUIContent(ResourceTable.Layout_ability_device_page);

        DatabaseHelper dataBaseHelper = new DatabaseHelper(getApplicationContext());
        String fileName = "preference_db";
        Preferences preference = dataBaseHelper.getPreferences(fileName);

        String centerIP = preference.getString("center_ip", "");

        //找到listcontainer
        listContainer = (ListContainer) findComponentById(ResourceTable.Id_list_container);

        // 创建集合并给集合添加数据
        itemList = initData();
        //创建一个Item的管理员对象（适配器）
        //并把要展示的所有数据和要加载的页面传过去
        itemProvider ip = new itemProvider(itemList, this);
        //把适配器交给列表容器组件
        listContainer.setItemProvider(ip);

        Button settingButton = (Button) findComponentById(ResourceTable.Id_setting_button);
        settingButton.setClickedListener(component -> {
            Intent toSettingPage = new Intent();
            Operation operation = new Intent.OperationBuilder()
                    .withDeviceId("")    // 设备Id，在本地上进行跳转可以为空，跨设备进行跳转则需要传入值
                    .withBundleName("com.dinolink.dinolink")    // 包名
                    .withAbilityName(".SettingPage")    // Ability页面的名称，在本地可以缺省前面的路径
                    .build();    // 构建代码
            toSettingPage.setOperation(operation);    // 将operation存入到intent中
            startAbility(toSettingPage);    // 实现Ability跳转
        });

    }

    public ArrayList<item> initData() {
        ArrayList<item> list = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            list.add(new item(ResourceTable.Media_switch_off, "device" + i, "OFF"));
        }
        return list;
    }


    @Override
    protected void onResult(int requestCode, Intent resultIntent) {
        if (resultIntent == null || requestCode != 0) {
            return;
        }
        super.onResult(requestCode, resultIntent);
        if (resultIntent.getIntParam("item_id", -1) == -1) {
            return;
        }
        itemList.get(resultIntent.getIntParam("item_id", -1))
                .setState(resultIntent.getStringParam("device_state"));

    }

    @Override
    public void onActive() {
        super.onActive();
        listContainer = (ListContainer) findComponentById(ResourceTable.Id_list_container);
        itemProvider ip = new itemProvider(itemList, this);
        listContainer.setItemProvider(ip);

    }

    @Override
    public void onForeground(Intent intent) {
        super.onForeground(intent);
    }
}
