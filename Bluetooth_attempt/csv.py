# https://tutorialedge.net/python/concurrency/asyncio-event-loops-tutorial/
import os, sys
import asyncio
import platform
import csv
from datetime import datetime
from typing import Callable, Any

from aioconsole import ainput
from bleak import BleakClient, discover

import os.path
root_path = os.path.expanduser('~')
output_file = f"{root_path}/Desktop/microphone_dump.csv"

selected_device = []


class Connection:
    
    client: BleakClient = None
    
    def __init__(
        self,
        loop: asyncio.AbstractEventLoop,
        read_characteristic: str,
        data_dump_size: int = 256,
    ):
        self.loop = loop
        self.read_characteristic = read_characteristic

        self.last_packet_time = datetime.now()
        self.dump_size = data_dump_size
        self.connected = False
        self.connected_device = None

        self.rx_data = []

    def on_disconnect(self, client: BleakClient, future: asyncio.Future):
        self.connected = False
        # Put code here to handle what happens on disconnet.
        print(f"Disconnected from {self.connected_device.name}!")

    async def cleanup(self):
        if self.client:
            await self.client.stop_notify(read_characteristic)
            await self.client.disconnect()

    async def manager(self):
        print("Starting connection manager.")
        while True:
            if self.client:
                await self.connect()
            else:
                await self.select_device()
                await asyncio.sleep(15.0, loop=loop)       

    async def connect(self):
        if self.connected:
            return
        try:
            await self.client.connect()
            self.connected = await self.client.is_connected()
            if self.connected:
                print(F"Connected to {self.connected_device.name}")
                self.client.set_disconnected_callback(self.on_disconnect)
                while True:
                    if not self.connected:
                        break
                    await asyncio.sleep(3.0, loop=loop)
            else:
                print(f"Failed to connect to {self.connected_device.name}")
        except Exception as e:
            print(e)

    async def select_device(self):
        print("Bluetooh LE hardware warming up...")
        await asyncio.sleep(2.0, loop=loop) # Wait for BLE to initialize.
        devices = await discover()

        print("Please select device: ")
        for i, device in enumerate(devices):
            print(f"{i}: {device.name}")

        response = -1
        while True:
            response = await ainput("Select device: ")
            try:
                response = int(response.strip())
            except:
                print("Please make valid selection.")
            
            if response > -1 and response < len(devices):
                break
            else:
                print("Please make valid selection.")

        print(f"Connecting to {devices[response].name}")
        self.connected_device = devices[response]
        self.client = BleakClient(devices[response].address, loop=self.loop)




#############
# Loops
#############
async def user_console_manager(connection: Connection):
    while True:
        if connection.client and connection.connected:
            try:
                value = bytes(await connection.client.read_gatt_char(read_characteristic))
                valuey = bytes(await connection.client.read_gatt_char(read_characteristicy))
                valuez = bytes(await connection.client.read_gatt_char(write_characteristic))
                #print("Value:", value)
                #valuet = int.from_bytes(value, byteorder='little', signed=False)
                #print("Valuet:", valuet)
                valueencz = (valuez).decode("utf-8")
                valueency = (valuey).decode("utf-8")
                valueenc = (value).decode("utf-8") 
                #print("Valueencoded", valueenc)
                #print("Message received: "  + valueenc)
                file = open(f'{root_path}/Desktop/test.csv', "a")
                #print("Created file")
                file = open(f'{root_path}/Desktop/test.csv', "a") #append the data to the file
                #file.write(valueenc + "\n") #write data with a newline
                text = str(valueenc) + "," + str(valueency) + "," + str(valueencz) + "\n"
                file.write(text)
                #close out the file
                file.close()

            except Exception as e:
                value = str(e).encode()
                
        else:
            await asyncio.sleep(2.0, loop=loop)


async def main():
    while True:
        # YOUR APP CODE WOULD GO HERE.
        await asyncio.sleep(5)



#############
# App Main
#############
read_characteristic = "ff99948c-18ff-4ed8-942e-512b9b24b6da"
read_characteristicy = "8084aa6b-6cae-461f-9540-e1a5768de49d"
write_characteristic = "ab80cb77-fe74-40d8-9757-96f8a54c16d9"

if __name__ == "__main__":

    # Create the event loop.
    loop = asyncio.get_event_loop()

    
    connection = Connection(
        loop, read_characteristic, read_characteristicy
    )
    try:
        asyncio.ensure_future(connection.manager())
        asyncio.ensure_future(user_console_manager(connection))
        asyncio.ensure_future(main())
        loop.run_forever()
    except KeyboardInterrupt:
        print()
        print("User stopped program.")
    finally:
        print("Disconnecting...")
        loop.run_until_complete(connection.cleanup())