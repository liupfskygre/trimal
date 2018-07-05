#include "../../include/ReadWriteMS/ReadWriteMachineState.h"
#include "../../include/ReadWriteMS/phylip_paml_state.h"
#include "../../include/defines.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "../../include/newAlignment.h"

using namespace std;

int phylip_paml_state::CheckAlignment(istream* origin)
{
    return 0;
}

newAlignment* phylip_paml_state::LoadAlignment(std::string filename)
{
    return nullptr;
}

bool phylip_paml_state::SaveAlignment(newAlignment* alignment, std::ostream* output, std::string* FileName)
{
    /* Generate output alignment in PHYLIP format compatible with PAML program */

    int i, maxLongName;
    string *tmpMatrix;

    /* Check whether sequences in the alignment are aligned or not.
     * Warn about it if there are not aligned. */
    if (!alignment->isAligned) {
        debug.report(ErrorCode::UnalignedAlignmentToAlignedFormat, new std::string[1] { this->name });
        return false;
    }

    /* Allocate local memory for generating output alignment */
    tmpMatrix = new string[alignment->sequenNumber];

    /* Depending on alignment orientation: forward or reverse. Copy directly
     * sequence information or get firstly the reversed sequences and then
     * copy it into local memory */
    for(i = 0; i < alignment->sequenNumber; i++)
        tmpMatrix[i] = (!Machine->reverse) ?
                       alignment->sequences[i] :
                       utils::getReverse(alignment->sequences[i]);

    maxLongName = PHYLIPDISTANCE;
    for(i = 0; (i < alignment->sequenNumber); i++)
        maxLongName = utils::max(maxLongName, alignment->seqsName[i].size());

    /* Generating output alignment */
    /* First Line: Sequences Number & Residued Number */
    *output << " " << alignment->sequenNumber << " " << alignment->residNumber << endl;

    /* Print alignment */
    /* Print sequences name follow by the sequence itself in the same line */
    for(i = 0; i < alignment->sequenNumber; i++)
        *output << setw(maxLongName + 3) << left << alignment->seqsName[i].substr(0, maxLongName)
             << alignment->sequences[i] << endl;
    *output << endl;

    /* Deallocate local memory */
    delete [] tmpMatrix;
    
    return true;
}

bool phylip_paml_state::RecognizeOutputFormat(std::string FormatName)
{
    if (ReadWriteBaseState::RecognizeOutputFormat(FormatName)) return true;
    return FormatName == "phylippaml";
}

