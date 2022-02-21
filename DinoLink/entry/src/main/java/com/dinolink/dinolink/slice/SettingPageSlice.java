package com.dinolink.dinolink.slice;

import com.dinolink.dinolink.ResourceTable;
import com.dinolink.dinolink.myToastUtils.ToastUtils;
import ohos.aafwk.ability.AbilitySlice;
import ohos.aafwk.content.Intent;
import ohos.agp.components.Button;
import ohos.agp.components.TextField;
import ohos.data.DatabaseHelper;
import ohos.data.preferences.Preferences;
import ohos.global.resource.NotExistException;
import ohos.global.resource.ResourceManager;
import ohos.global.resource.WrongTypeException;

import java.io.IOException;

public class SettingPageSlice extends AbilitySlice {

    private DatabaseHelper databaseHelper;
    private Preferences preferences;
    private ResourceManager resManager;
    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setUIContent(ResourceTable.Layout_ability_setting_page);

        databaseHelper = new DatabaseHelper(getApplicationContext());
        String filename = "preference_db";
        preferences = databaseHelper.getPreferences(filename);

        resManager = this.getResourceManager();

        String centerIP = preferences.getString("center_ip", "");
        TextField centerIPInput = (TextField) findComponentById(ResourceTable.Id_center_ip_input);
        centerIPInput.setText(centerIP);

        Button applyButton = (Button) findComponentById(ResourceTable.Id_apply_button);
        applyButton.setClickedListener(component -> {
            preferences.putString("center_ip", ((TextField) findComponentById(ResourceTable.Id_center_ip_input)).getText());
            preferences.flush();
            try {
                String message = resManager.getElement(ResourceTable.String_successfully_saved_change).getString();
                ToastUtils.showDialog(getContext(), message);
            } catch (IOException e) {
                e.printStackTrace();
            } catch (NotExistException e) {
                e.printStackTrace();
            } catch (WrongTypeException e) {
                e.printStackTrace();
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
