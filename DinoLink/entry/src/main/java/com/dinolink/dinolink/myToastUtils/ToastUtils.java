package com.dinolink.dinolink.myToastUtils;

import com.dinolink.dinolink.ResourceTable;
import ohos.agp.components.DirectionalLayout;
import ohos.agp.components.LayoutScatter;
import ohos.agp.components.Text;
import ohos.agp.utils.LayoutAlignment;
import ohos.agp.window.dialog.ToastDialog;
import ohos.app.Context;

public class ToastUtils {
    public static void showDialog(Context context, String message) {

        //1.把 xml 文件加载到内存当中
        DirectionalLayout dl = (DirectionalLayout) LayoutScatter.getInstance(context).parse(ResourceTable.Layout_my_toast_layout, null, false);

        //2.获取到当前布局对象中的文本组件
        Text msg = (Text) dl.findComponentById(ResourceTable.Id_msg);

        //3.把需要提示的信息设置到文本组件
        msg.setText(message);

        //4.创建一个ToastDialog对象
        ToastDialog td = new ToastDialog(context);
        //设置弹框的大小，默认是包裹内容
        //宽高都要设置
        td.setSize(DirectionalLayout.LayoutConfig.MATCH_CONTENT, DirectionalLayout.LayoutConfig.MATCH_CONTENT);
        //设置出现的时间
        td.setDuration(2000);
        //设置对齐方式
        td.setAlignment(LayoutAlignment.CENTER);
        //把 xml 对象交给ToastDialog
        td.setContentCustomComponent(dl);

        td.setOffset(0, -500);
        //让弹框出现
        td.show();
    }
}
