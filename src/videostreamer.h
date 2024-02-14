#ifndef VIDEOSTREAMER_H
#define VIDEOSTREAMER_H

#include <QObject>

#include "UsageEnvironment.hh"
#include "NetAddress.hh"

class VideoStreamer
{
    Q_OBJECT
public:
    static VideoStreamer* createNew(UsageEnvironment& env, char const* rtspURL,
                             int verbosityLevel = 0,
                             char const* applicationName = NULL,
                             portNumBits tunnelOverHTTPPortNum = 0,
                             int socketNumToServer = -1);
};

#endif // VIDEOSTREAMER_H
