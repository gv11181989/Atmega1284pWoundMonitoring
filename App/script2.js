var bluetoothDevice;

const button = document.getElementById("getDetails");
const details = document.getElementById("details");

button.addEventListener("click", async () => {
    bluetoothDevice = null;
    try {
      console.log('Requesting any Bluetooth Device...');
      bluetoothDevice = await navigator.bluetooth.requestDevice({
       // filters: [...] <- Prefer filters to save energy & show relevant devices.
          acceptAllDevices: true});
      bluetoothDevice.addEventListener('gattserverdisconnected', onDisconnected);
      connect();
      

        // Connect to the GATT server
        let deviceName = bluetoothDevice.gatt.device.name;
        console.log('deviceName--');
        console.log(deviceName);
        const server = await bluetoothDevice.gatt.connect()//.getCharacteristics("0000ffe1-0000-1000-8000-00805f9b34fb");
        // Getting the services we mentioned before through GATT server
        const infoService = await server.getPrimaryService("0000ffe0-0000-1000-8000-00805f9b34fb");

        console.log('infoService--');
        console.log(infoService);

        // Getting device information
        const infoCharacteristics = await infoService.getCharacteristics("0000ffe1-0000-1000-8000-00805f9b34fb");

        console.log('infoCharacteristics--');
        console.log(infoCharacteristics);
        console.log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    } catch(error) {
      console.log('Argh! ' + error);
    }
  })
  
  async function connect() {
    exponentialBackoff(3 /* max retries */, 2 /* seconds delay */,
      async function toTry() {
        time('Connecting to Bluetooth Device... ');
      },
      function success() {
        console.log('> Bluetooth Device connected. Try disconnect it now.');

      },
      
      function fail() {
        time('Failed to reconnect.');
      });
  }
  
  function onDisconnected() {
    console.log('> Bluetooth Device disconnected');
    connect();
  }
  
  /* Utils */
  
  // This function keeps calling "toTry" until promise resolves or has
  // retried "max" number of times. First retry has a delay of "delay" seconds.
  // "success" is called upon success.
  async function exponentialBackoff(max, delay, toTry, success, fail) {
    try {
      const result = await toTry();
      success(result);
    } catch(error) {
      if (max === 0) {
        return fail();
      }
      time('Retrying in ' + delay + 's... (' + max + ' tries left)');
      setTimeout(function() {
        exponentialBackoff(--max, delay * 2, toTry, success, fail);
      }, delay * 1000);
    }
  }
  
  function time(text) {
    console.log('[' + new Date().toJSON().substr(11, 8) + '] ' + text);
  }