Smart Waste Management System API Documentation
Overview
The Smart Waste Management System is an integrated solution for monitoring waste levels in bins in real time and managing waste collection efficiently. It comprises embedded systems and a mobile application. The embedded system consists of Arduino-based hardware equipped with ultrasonic sensors, GPS modules, and servo motors to detect waste levels, determine locations, and trigger alerts. The mobile application provides a user-friendly interface for users to monitor bin levels and view bin locations.

Components
The system comprises the following components:
•	Embedded System: Arduino-based hardware equipped with ultrasonic sensors, GPS modules, and servo motors.
•	Mobile Application: HTML/CSS/JavaScript-based application for user interaction and visualization.

API Endpoints
1. Embedded System (Arduino)
a. setup ()
•	Description: Initializes the system components and establishes connections.
•	Parameters: None
•	Returns: None
b. loop ()
•	Description: Main loop to continuously monitor waste levels, user presence, and GPS coordinates.
•	Parameters: None
•	Returns: None

c. WifiReconnect()
•	Description: Reconnects to the Wi-Fi network if disconnected.
•	Parameters: None
•	Returns: None
d. pushMessage()
•	Description: Pushes waste level data and GPS coordinates to the MQTT server at regular intervals.
•	Parameters: None
•	Returns: None

2. Mobile Application (HTML/CSS/JavaScript)
a. GetData()
•	Description: Retrieves data from the ThingSpeak API to display bin level, latitude, and longitude.
•	Parameters: None
•	Returns: None
b. Location()
•	Description: Opens Google Maps with the bin's location based on latitude and longitude.
•	Parameters: None
•	Returns: None

Data Format
1. Embedded System Data
•	Bin Level: Percentage of waste level in the bin.
•	Latitude: GPS latitude coordinates.
•	Longitude: GPS longitude coordinates.
2. Mobile Application Data
•	Bin Level: Percentage of waste level in the bin.
•	Latitude: GPS latitude coordinates.
•	Longitude: GPS longitude coordinates.

A breakdown of the Code Sample
1. Embedded System
// Arduino code here
void setup() {
    // Initialization code
}

void loop() {
    // Main loop
    WifiReconnect();
    pushMessage();
}

void WifiReconnect() {
    // Reconnect to Wi-Fi network
}

void pushMessage() {
    // Push waste level data and GPS coordinates
}

2. Mobile Application
// HTML/CSS/JavaScript code here
$(document).ready(function () {
    GetData();
});

function GetData() {
    // Retrieve data from ThingSpeak API
}

function Location() {
    // Open Google Maps with bin location
}






