const button = document.getElementById("getDetails");
const details = document.getElementById("details");

button.addEventListener("click", async () => {
    try {

        navigator.bluetooth.requestDevice({ filters: [{ services: ['f3cd22bb-9fe3-466b-8793-ab9e9061baa5'] }] })
            .then(device => device.gatt.connect())
            .then(server => server.getPrimaryService('f3cd22bb-9fe3-466b-8793-ab9e9061baa5'))
            .then(service => service.getCharacteristic('f3cd22bb-9fe3-466b-8793-ab9e9061baa5'))
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

//             var result = "";
//   for (var i = 0; i < a.length; i++) {
//     // console.log(`each value ${parseInt(a[i])}`);
//     result += String.fromCharCode(parseInt(a[i]));
//   }
//   console.log(result);
            // console.log('Received ' + value.getUint8(1).toString(16));
            // TODO: Parse Heart Rate Measurement value.
            // See https://github.com/WebBluetoothCG/demos/blob/gh-pages/heart-rate-sensor/heartRateSensor.js
        }

        // navigator.bluetooth.requestDevice({ filters: [{ services: ['0000ffe0-0000-1000-8000-00805f9b34fb'] }] })
        //     .then(device => device.gatt.connect())
        //     .then(server => {
        //         // Getting Battery Service…
        //         return server.getPrimaryService('0000ffe0-0000-1000-8000-00805f9b34fb');
        //     })
        //     .then(service => {
        //         // Getting Battery Level Characteristic…
        //         return service.getCharacteristic('0000ffe1-0000-1000-8000-00805f9b34fb');
        //     })
        //     .then(characteristic => {
        //         // Reading Battery Level…
        //         console.log(characteristic.readValue());
        //     })
        //     .then(value => {
        //         for (let i = 0; i < value.byteLength; i++) {
        //             a.push('0x' + ('00' + value.getUint8(i).toString(16)).slice(-2));
        //           }
        //         //   log('> ' + a.join(' '));
        //         console.log(`Notification says ${a.join(' ')}`);
        //     })
        // .catch (error => { console.error(error); });
        // // Request the Bluetooth device through browser
        // const device = await navigator.bluetooth.requestDevice({
        //     optionalServices: ["0000ffe0-0000-1000-8000-00805f9b34fb"],
        //     acceptAllDevices: true,
        // });

        // // Connect to the GATT server
        // let deviceName = device.gatt.device.name;
        // console.log('deviceName--');
        // console.log(deviceName);
        // const server = await device.gatt.connect()//.getCharacteristics("0000ffe1-0000-1000-8000-00805f9b34fb");
        // // Getting the services we mentioned before through GATT server
        // const infoService = await server.getPrimaryService("0000ffe0-0000-1000-8000-00805f9b34fb");

        // console.log('infoService--');
        // console.log(infoService);

        // // Getting device information
        // const infoCharacteristic = await infoService.getCharacteristic("0000ffe1-0000-1000-8000-00805f9b34fb");

        // console.log('infoCharacteristics--');
        // console.log(infoCharacteristic.readValue());
        // console.log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

        // print("********************************");


        // let infoValues = [];
        // const promise = new Promise((resolve, reject) => {
        //     infoCharacteristics.forEach(async (characteristic, index, array) => {
        //         // Returns a buffer
        //         const value = await characteristic.readValue();
        //         console.log(String(value))
        //         console.log(new TextDecoder().decode(value));
        //         // Convert the buffer to string
        //         infoValues.push(new TextDecoder().decode(value));
        //         if (index === array.length - 1) resolve();
        //     });
        // });

        // promise.then(() => {
        //     // Display all the information on the screen
        //     // use innerHTML
        //     details.innerHTML = `
        //       Device Name - ${deviceName}<br />
        //       Device Information:
        //       <ul>
        //         ${infoValues.map((value) => `<li>${value}</li>`).join("")}
        //       </ul> 
        //     `;
        // });

    } catch (err) {
        console.error(err);
        alert("error");
    }
});