package com.dinolink.dinolink.slice;

import com.dinolink.dinolink.ResourceTable;
import ohos.aafwk.ability.AbilitySlice;
import ohos.aafwk.content.Intent;
import ohos.agp.components.Button;
import ohos.agp.components.Component;
import ohos.agp.components.TextField;
import ohos.data.DatabaseHelper;
import ohos.data.preferences.Preferences;

public class SettingPageSlice extends AbilitySlice {

    private DatabaseHelper databaseHelper;
    private Preferences preferences;

    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setUIContent(ResourceTable.Layout_ability_setting_page);

        databaseHelper = new DatabaseHelper(getApplicationContext());
        String filename = "preference_db";
        preferences = databaseHelper.getPreferences(filename);

        String centerIP = preferences.getString("center_ip", "");
        TextField centerIPInput = (TextField) findComponentById(ResourceTable.Id_center_ip_input);
        centerIPInput.setText(centerIP);

        Button applyButton = (Button) findComponentById(ResourceTable.Id_apply_button);
        applyButton.setClickedListener(new Component.ClickedListener() {
            @Override
            public void onClick(Component component) {
                preferences.putString("center_ip", ((TextField) findComponentById(ResourceTable.Id_center_ip_input)).getText());
                preferences.flush();
            }
        });

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
