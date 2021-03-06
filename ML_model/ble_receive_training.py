import asyncio
from bleak import BleakClient
import collections
import numpy as np
import struct
import pandas as pd 

motion_dataset = collections.deque(maxlen=45)
CHARACTERISTIC_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"  
ADDRESS = "64:69:4E:8A:09:80"


def notification_handler(sender, data):
    """Notification data received to .csv file."""
    values = round(struct.unpack('<f', data)[0],2)
    motion_dataset.append(values)
    to_csv = np.array(motion_dataset)
    pd.DataFrame(to_csv).to_csv("motion_13.csv",index=False)
    print(motion_dataset)

async def run(address):

    async with BleakClient(address) as client:
        await client.start_notify(CHARACTERISTIC_UUID, notification_handler)
        while (1):
            await asyncio.sleep(1.0)
        await client.stop_notify(CHARACTERISTIC_UUID)


if __name__ == "__main__":
    loop = asyncio.get_event_loop()
    
    while (1):
        try:
            loop.run_until_complete(run(ADDRESS))
        except Exception as e: print(e)