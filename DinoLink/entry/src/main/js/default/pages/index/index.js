import router from '@system.router';

export default {
    data: {
        count: 0,
        intervalID: 0
    },

    onInit() {
        this.intervalID = setInterval(this.countSeconds, 1000);
    },

    countSeconds: function () {
        let that = this;
        that.data.count++;
        //console.info(that.data.count)
        if (that.data.count === 3) {
            clearInterval(this.data.intervalID);
            router.replace({
                uri: "pages/devicePage/devicePage"
            })

        }
    },
}