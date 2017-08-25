# rssi-map

## Objective

The aim is to create an WiFi RSSI map for my college, which will result in a diagram of strongest and weakest wireless zones.

## Procedure

An ESP12-E is used for rapidly logging WiFi RSS values which are then sent to an Android phone via HC-05 bluetooth.  
On the android phone, latitudes and longitudes (courtesy of Google's location API) for each RSSI data-point are compiled into a .csv file.  
The .csv file has to be then processed accordingly keeping in mind the relative layout of the assessed region.