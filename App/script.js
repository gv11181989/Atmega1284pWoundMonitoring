const button = document.getElementById("getDetails");
const details = document.getElementById("details");

button.addEventListener("click", async () => {
    try {

        // Request the Bluetooth device through browser
        const device = await navigator.bluetooth.requestDevice({
            optionalServices: ["0000ffe0-0000-1000-8000-00805f9b34fb"],
            acceptAllDevices: true,
        });

        // Connect to the GATT server
        let deviceName = device.gatt.device.name;
        const server = await device.gatt.connect();
        // Getting the services we mentioned before through GATT server
        const infoService = await server.getPrimaryService("0000ffe0-0000-1000-8000-00805f9b34fb");

        // Getting device information
        const infoCharacteristics = await infoService.getCharacteristics("0000ffe1-0000-1000-8000-00805f9b34fb");
        console.log(infoCharacteristics);


        // let infoValues = [];
        // const promise = new Promise((resolve, reject) => {
        //     infoCharacteristics.forEach(async (characteristic, index, array) => {
        //         // Returns a buffer
        //         const value = await characteristic.readValue();
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