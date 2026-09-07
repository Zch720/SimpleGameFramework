#pragma once

#include <sgf/utils/fwd.h>

namespace sgf_core {
    class AudioContext;

    class Listener;
    class AudioGroup;

    class AudioDataResolver;

    struct AudioDataTag;
    using AudioDataId = ResourceId<AudioDataTag>;
    class AudioData;
    class AudioDataManager;
    
    struct AudioSourceTag;
    using AudioSourceId = ResourceId<AudioSourceTag>;
    class AudioSource;
    class AudioSourceManager;
}
