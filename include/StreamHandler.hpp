#pragma once

#include "AudioFile.hpp"

#include "sndfile.h"
#include "portaudio.h"

#if defined (__linux__)
#include <cstdlib> // required for putenv.
#endif

#include <vector>
#include <functional>

struct Playback
{
    AudioFile * audioFile;
    int position;
    bool loop;
};

enum AudioEventType
{
    start,
    stop,
};

class StreamHandler
{
public:
    StreamHandler();
    ~StreamHandler();

    void processEvent(
        AudioEventType audioEventType,
        AudioFile * audioFile = nullptr,
        bool loop = false
    );

    static int PortAudioCallback(
        const void * input,
        void * output,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo * paTimeInfo,
        PaStreamCallbackFlags statusFlags,
        void * userData
    );

private:
    const int CHANNEL_COUNT = 2;
    const unsigned long SAMPLE_RATE = 44000;
    const PaStreamParameters * NO_INPUT = nullptr;

    static void wrapPortAudioCall(const std::string &, const std::function<PaError()> &);
    static void wrapPortAudioCallOrTerminate(const std::string &, const std::function<PaError()> &);

    PaStream * stream;
    std::vector<Playback> playingSounds;
};
