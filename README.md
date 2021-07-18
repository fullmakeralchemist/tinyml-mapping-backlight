<!--
*** Thanks for checking out this README Template. If you have a suggestion that would
*** make this better, please fork the tinyml-mapping-backlight and create a pull request or simply open
*** an issue with the tag "suggest".
*** Thanks again! Now go create something AMAZING! :D
***
***
***
*** To avoid retyping too much info. Do a search and replace for the following:
*** fullmakeralchemist, tinyml-mapping-backlight, twitter_handle, fullmakeralchemist@gmail.com   
-->

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/fullmakeralchemist/tinyml-mapping-backlight">
    <img src="assets/logo.png" alt="Logo" width="720">
  </a>
  <br />

  <a href="https://www.linkedin.com/in/fullmakeralchemist/">
    <img src="https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555" alt="LinkedIn" height="25">
  </a>
  <a href="https://twitter.com/makeralchemist/">
    <img src="https://img.shields.io/twitter/follow/makeralchemist?label=Twitter&logo=twitter&style=for-the-badge" alt="Twitter" height="25">
  </a>

   <h3 align="center">Tiny ML in Mapping Dance, Visual Arts and interactive museums</h3>
  <p align="center">
    Because Art Inspired Technology, Technology Inspired Art
    <br />
    <a href="https://youtu.be/3YUVTDTo-Zk"><strong>View the demo »</strong></a>
    <br />
  </p>
  <br />
</p>
<br />

<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Motivation](#motivation)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
  * [Data Exploration](#data-exploration)
  * [Model Training](#model-training)
  * [Mapping and lightning Script Running](#script)
  * [Model Serving](#model-serving)
* [Roadmap](#roadmap)
* [License](#license)
* [Contact](#contact)

<!-- ABOUT THE PROJECT -->
## About The Project

<!-- linkvideo -->

An intelligent assistant device to track moves with responses during a dance performance or an interactive building with mapping and Backlight.

This project makes use of a machine learning algorithm capable of tracking and detecting moves to identify associated gesture recognition through a microcontroller. This allows the corresponding media, lightning and kinetic sculpture set to play when the right move was made because lighting interacts with all the visuals of a stage creating a new experience.


### Motivation

Some facts:
-There are a lot of new art projects adding technology nowadays.
-Factors like the difficulties that artists come up with during their attempts to familiarize with new technologies, so that they can integrate them in their projects.
-High cost of buying and installing new software together with its supporting systems.
-Limited access that a large percentage of the student population has to new technologies made it sometimes **difficult to use technology in dance**.

##### Technology in art can be an element for good, but only when everyone is included.

Interactive multimedia is one of the most important applications of technology. It is one of the most accessible technological innovations, which does not require expert knowledge in computer programming. Interactive multimedia involves a lot of elements (i.e. text, image, sound, graphics, etc.) all included in an easy learning environment where creative action and inquiry have the primary role.

### Built With

With a lot of love 💖, motivation to help others 💪🏼 and [Python](https://www.python.org/) 🐍, using:

* [Tensorflow 2.0](https://www.tensorflow.org/)
* [Google Colab](https://colab.research.google.com/) <img src="https://colab.research.google.com/img/favicon.ico" width="15"> (with its wonderful GPUs)
* Model quantization with `tf.lite` for serving ⚙️
* Encode the Model in an Arduino Header File
* A [Raspberry Pi](https://www.raspberrypi.org/) 4 <img src="https://www.raspberrypi.org/homepage-9df4b/favicon.png" width="15">
* A [Arduino Nano 33 BLE SENSE](https://store.arduino.cc/usa/nano-33-ble-sense)
* A [NodeMCU ESP8266](https://nodemcu.readthedocs.io/en/release/) board
* The MQTT [Mosquitto](https://mosquitto.org/) Broker
* The [Eclipse Paho](http://eclipse.org/paho/) MQTT Python client [library](https://pypi.org/project/paho-mqtt/)
* [PubSubClient library](https://github.com/knolleary/pubsubclient/archive/master.zip) in Arduino IDE for the ESP8266 Board
* Arduino IDE
* ESP8266 Board [Package](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide)


<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps

### Prerequisites

This is an example of how to list things you need to use the software and how to install them. 

For this particular section I will suppose that you already have a Raspberry Pi already setup. If not I have a guide in Medium about [Getting started on Raspberry Pi 4](https://fullmakeralchemist.medium.com/setting-up-your-raspberry-pi-4-wireless-f51c16937d1e). Also you will need git installed on your system. If not, I have a guide posted on [Medium](https://fullmakeralchemist.medium.com/install-git-and-visual-studio-code-on-raspberry-pi-48d054fdee07) to do it .
For a general overview of the Arduino Nano 33 BLE Sense setup, you can check out the Arduino Guide on [Getting started with Arduino Nano 33 BLE Sense](https://www.arduino.cc/en/Guide/NANO33BLESense).

Before installing the libraries in Raspberry Pi run the following code lines in the Raspberry Pi terminal:

```
sudo apt update
sudo apt upgrade
```
After updating and upgrading we will write the following command:

```
sudo pip install python-vlc
```

To install the Mosquitto Broker enter these next commands:

```
pi@raspberry:~ $ sudo apt install -y mosquitto mosquitto-clients
```

You’ll have to type Y and press Enter to confirm the installation. To make Mosquitto auto start on boot up enter:

```
pi@raspberry:~ $ sudo systemctl enable mosquitto.service
```
```
pi@raspberry:~ $  mosquitto -v
```
This returns the Mosquitto version that is currently running in your Raspberry Pi. It should be 1.5.X or above.

#### Raspberry Pi IP Address & Paho Package

To use Mosquitto broker later on your projects, you’ll need your Raspberry Pi IP address. To retrieve your Raspberry Pi IP address, type the next command in your Terminal window:
```
pi@raspberry:~ $ hostname -I
```
The Paho package provides a client class which enables applications to connect to an MQTT broker to publish messages, and to subscribe to topics and receive published messages. In this project, the Python script is going to publish messages to the ESP8266 to turn the GPIOs on and off to control the lights.
To install paho-mqtt run the following command:

```
sudo pip install paho-mqtt
```

And those are the steps that we will follow to set up our Raspberry Pi. In any case, this specific setup can be seen in the corresponding raspberrypiserial folder.

Now lets see the setup for the Arduino IDE

#### Setup Arduino IDE

To install the ESP8266 Board Package enter:

```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```
Into Additional Board Manager URLs field in the Arduino v1.6.4+ preferences.
<!-- IMAGE -->
Next, use the Board manager to install the ESP8266 package.
<!-- image -->

After the install process, you should see that esp8266 package is marked INSTALLED. Close the Boards Manager window once the install process has completed.

Setup ESP8266 Support When you've restarted, select Adafruit Feather HUZZAH ESP8266  from the Tools->Board dropdown.

#### Getting the MQTT library for the ESP8266
For the ESP8266 to interact with the Raspberry Pi web server, you need to install the PubSubClient [library](https://github.com/knolleary/pubsubclient). This library provides a client for doing simple publish/subscribe messaging with a server that supports MQTT (basically allows your ESP8266 to talk with a Python web server).

##### Installing the Library
1. [Click here to download the PubSubClient library](https://github.com/knolleary/pubsubclient/archive/master.zip). You should have a .zip folder in your Downloads folder
2. Unzip the .zip folder and you should get pubsubclient-master folder
3. Rename your folder from pubsubclient-master to pubsubclient
4. Move the pubsubclient folder to your Arduino IDE installation libraries folder
5. Then, re-open your Arduino IDE

The library comes with a number of example sketches. See File > Examples > PubSubClient within the Arduino IDE software.

Finally, you can upload the full [sketch]() to your ESP8266 (replace with your SSID, password and RPi IP address):

### Run the script


Clone the tinyml-mapping-backlight repo, download it or just copy and paste from the files from this repo:
bash
```
git clone https://github.com/fullmakeralchemist/tinyml-mapping-backlight
```

The simplest way is just using the Thonny IDE which is included with Raspberry Pi OS, Thonny comes with Python 3.6 built in, so you don’t need to install anything. Just open up the program, which you’ll find under Menu > Programming. It offers a lot of advanced features not currently available in the Python 3 (IDLE) program. Also you can follow my guide to install Visual Studio Code, but some libraries show some errors trying to run the script. So I recommend you to use the Thonny IDE.

<!-- image -->

<!-- USAGE EXAMPLES -->
## Usage

### Data Exploration

The dataset used for this project was obtained from the capture_acc_gyro file, you can find it in the Repository. This dataset records 119 x,y and z acceleration and gyroscope data from on-board IMU and prints it to the Serial Monitor for one second when the significant motion is detected and prints the data in CSV format. This data will be copied and pasted into a text file and this text fill will be saved as a CSV file. To be uploaded to the Google Collab Notebook to train.
<!-- image -->

### Model Training

After reading Tiny ML Machine Learning with TensorFlow Lite on Arduino and Ultra-Low-Power Microcontrollers, I found this [resource](https://github.com/arduino/ArduinoTensorFlowLiteTutorials/) that helped me a lot to just focus on making some tests with different movements, training and testing with the Arduino board.

As part of the project development I have implemented the proposed model using Tensorflow 2.0. For training I used the previously mentioned CSV files obtained from Arduino on a Google Colab environment using GPUs. So far the model was trained for 600 epochs using a batch size of 64. The training history can be seen in the following graphs:

<!-- image graphs -->
Although the results may not seem quite good, the model has achieved an accuracy value of 0.9149 on the validation dataset with 600 training epochs, with a record of at least 20 repeats of the movement recorded with the arduino capture file, also I try with 30 and 40 reparts, with more repetitions of the movement gets a better result, the problem is it gets tired repeat a movement so many times. We can get a general idea of the model performance in the arduino tinyimu file running the model printing the **line data.f[i] in the loop through the output tensor values from the model**.

The trained model architecture, quantized model with tflite and encoded the Model in an Arduino Header File(for the deployment in the Arduino board) can be found in the model folder. Finally, if you want to re-train the model and verify the results on your own, you have to upload the csv files found in the same folder.
