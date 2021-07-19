## Bluetooth with windows 

This folder contains the Script and sketch to send data through a bluetooth connection between Arduino and a Windows machine using Python and visual Studio code

### Arduino file

If you follow the steps to setup the Arduino IDE to use the Arduino Nano 33 BLE Sense, is not necessary another step.

1. Open and load the file found in the sendimuclassifier folder found in this folder.

### Windows setup

1.  Create a folder and open the folder with the terminal and use `python -m venv env` to create a virtual environment
2.  Then use the requirements.txt file found in this folder with the command `pip install -r requirements.txt`
3. Run the script `csv.py` in the visual studio code IDE or the terminal
4. It would show the devices after a few seconds to connect choose the one named gyroscope 
5. It would create a new file in the Desktop to record all the data incoming from the Arduino.

### Raspberry Pi 

If you want to use the `csv.py` in Raspberry Pi run Raspbian OS Lite does not include everything we need, so there are a few packages to fetch with the apt tool.

```
sudo apt install python3-pip
sudo pip3 install bleak  
```

Once PIP3 and Bleak are installed, we're ready to go.

Also change this lines in the `csv.py` file:

```
import os.path
root_path = os.path.expanduser('~')
output_file = f"{root_path}/Desktop/microphone_dump.csv"
```

In Raspberry Pi the path works different.