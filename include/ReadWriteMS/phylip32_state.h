#ifndef PHYLIP32STATE_H
#define PHYLIP32STATE_H

#include "ReadWriteBaseState.h"

class phylip32_state : public ReadWriteBaseState {
public:

    explicit phylip32_state(ReadWriteMS *MachineState) {
        Machine = MachineState;
        name = "phylip32";
        extension = "phy";
        canLoad = true;
        canSave = true;
    };

    int CheckAlignment(istream *origin) override;

    newAlignment *LoadAlignment(string filename) override;

    bool SaveAlignment(newAlignment *alignment, ostream *output, std::string *FileName) override;

    bool RecognizeOutputFormat(std::string FormatName) override;

};

#endif // PHYLIP32STATE_H
