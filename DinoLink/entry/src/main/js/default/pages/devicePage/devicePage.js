import router from '@system.router';

export default {
    data: {
        //title: "Hello World",
    },
    settingButtonClicked: function(){
        router.replace({
            uri:"pages/settingPage/settingPage"
        })
    }
}