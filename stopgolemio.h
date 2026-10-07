#ifndef STOPGOLEMIO_H
#define STOPGOLEMIO_H

#include <QString>

class StopGolemio
{
public:
    StopGolemio();
    QString stopName="";
    QString platformName="";
    int locationType=0;
    QString stopId="";
    bool wheelchairBoarding=false;
    QString zoneId="";
    int aswNode=0;
    int aswStop=0;
    double stopLat=0.0;
    double stopLon=0.0;
};

#endif // STOPGOLEMIO_H
