const button = document.getElementById("getDetails");
const details = document.getElementById("details");

button.addEventListener("click", async () => {
    try {

        navigator.bluetooth.requestDevice({ filters: [{ services: ['0000ffe0-0000-1000-8000-00805f9b34fb'] }] })
            .then(device => device.gatt.connect())
            .then(server => server.getPrimaryService('0000ffe0-0000-1000-8000-00805f9b34fb'))
            .then(service => service.getCharacteristic('0000ffe1-0000-1000-8000-00805f9b34fb'))
            .then(characteristic => characteristic.startNotifications())
            .then(characteristic => {
                characteristic.addEventListener('characteristicvaluechanged',
                    handleCharacteristicValueChanged);
                console.log('Notifications have been started.');
            })
            .catch(error => { console.log(error); });

        function handleCharacteristicValueChanged(event) {
            var value = event.target.value;
            var a = "";
            for (let i = 0; i < 5; i++) {
                // a.push(value.getUint8(i));
                a += (String.fromCharCode(parseInt(value.getUint8(i))));
            }
            //   log('> ' + a.join(' '));
            console.log(`Notification says ${a}`);
        }


    } catch (err) {
        console.error(err);
        alert("error");
    }
});