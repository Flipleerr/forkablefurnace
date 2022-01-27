#ifndef _TIA_H
#define _TIA_H
#include "../dispatch.h"
#include "../macroInt.h"
#include <queue>
#include "sound/tia/TIASnd.h"

class DivPlatformTIA: public DivDispatch {
  protected:
    struct Channel {
      int freq, baseFreq, pitch, note;
      unsigned char ins, shape;
      signed char konCycles;
      bool active, insChanged, freqChanged, keyOn, keyOff, portaPause, inPorta;
      int vol, outVol;
      DivMacroInt std;
      Channel(): freq(0), baseFreq(0), pitch(0), note(0), ins(-1), shape(4), active(false), insChanged(true), freqChanged(false), keyOn(false), keyOff(false), portaPause(false), inPorta(false), vol(0), outVol(15) {}
    };
    Channel chan[2];
    bool isMuted[2];
    TIASound tia;
    friend void putDispatchChan(void*,int,int);
  
  public:
    void acquire(short* bufL, short* bufR, size_t start, size_t len);
    int dispatch(DivCommand c);
    void* getChanState(int chan);
    void reset();
    void forceIns();
    void tick();
    void muteChannel(int ch, bool mute);
    void setPAL(bool pal);
    bool isStereo();
    bool keyOffAffectsArp(int ch);
    void notifyInsDeletion(void* ins);
    int init(DivEngine* parent, int channels, int sugRate, bool pal);
    void quit();
};
#endif
