- 20260515_1811# GolemioClient
Qt C++ library for downloading departures from Golemio API (Prague integrated transport)

```
QT       += network xml
```




## Changelog
- 20260518_1125
  - added ConnectionGolemio::dumpToQStringLine
  
- 20260515_1819
  -  GolemioDepartureBoardsV2 previous commit fix
  
- 20260515_1811
  - added QLoggingCategory
    - GolemioDepartureBoardsV2
    - GolemioDepartureBoardsV4
    - GolemioRequestHandler
  
- 20260504_2310
  - GolemioDepartureBoardsV4 
    - default mAdress fix
  - added GolemioVehiclePositions (WIP)
    - GTFS tripId based requests, no parsing
  -  GolemioPublicVehiclePositions
  - VehiclePositionResult renamed to VehiclePositionResultPublic
  
- 20260504_1842
  - GolemioPublicVehiclePositions
    - mAdress fix
  
- 20260504_1741
  - GolemioDepartureBoardsV2
    - fix of GolemioRequestHandler::startDataDownload(QString)
  - GolemioV4 renamed to GolemioDepartureBoardsV4
  
- 20260506_1653
  - Golemio renamed to GolemioDepartureBoardsV2
  - GolemioDepartureBoardsV2 
    - functions translated to English
  - GolemioRequestHandler
    - some functions translated to English
- 20260430_1216
  - Golemio
    - split base functions to GolemioRequestHandler
  - new class GolemioPublicVehiclePositions
- 20260225_1936
  - GolemioV4::parseDomDocumentDepartures
    - added parsing of is_guaranteed and other parameters
  - ConnectionGolemioV4 
    - added tripIsGuaranteed

- 20260108_1538
  - Golemio::startDataDownload
    - empty cisNumber check
  - GolemioV4::parseDomDocumentDepartures
    - added icons parsing
- 20251006_1808
  - GolemioResultV4 include path fix