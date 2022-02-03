export default {
    data: {
        title: "Hello HarmonyOS",
        isHarmonyOS: true
    },

    switchTitle() {
        let that = this;
        that.title = that.isHarmonyOS ? "Hello World" : "Hello HarmonyOS";
        that.isHarmonyOS = !that.isHarmonyOS;
    }
}