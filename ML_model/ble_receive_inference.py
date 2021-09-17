import asyncio
from bleak import BleakClient
import collections
import numpy as np
import struct
import pandas as pd 
import sys

motion_dataset = collections.deque(maxlen=45)
CHARACTERISTIC_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"  # <--- Change to the characteristic you want to enable notifications from.
ADDRESS = "64:69:4E:8A:09:80"


def notification_handler(sender, data):
    """Simple notification handler which prints the data received."""
    # values = int.from_bytes(data, byteorder='big')
    print(data)

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