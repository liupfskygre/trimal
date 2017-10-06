#ifndef VERBOSEMANAGER_H
#define VERBOSEMANAGER_H

#include <string>
#include <map>
#include <array>
#include <vector>
#include <iostream>

enum VerboseLevel {
    /// 0 = No output messages
    NONE        = 0,
    /// 1 = Info, warning and error messages
    INFO        = 1,
    /// 2 = Error and warning messages
    WARNING    = 2,
    /// 3 = Only error messages
    ERROR      = 3,
};

enum ErrorCode {

    AlignmentNotLoaded                          = 1,

    NoFormatsSpecified                          = 2,

    AlternativeMatrixNotRecognized              = 3,

    ReferenceFileNotLoaded                      = 4,

    GapThresholdOutOfRange                      = 5,
    GapThresholdNotRecognized                   = 6,

    SimilarityThresholdOutOfRange               = 7,
    SimilarityThresholdNotRecognized            = 8,

    ConsistencyThresholdOutOfRange              = 9,
    ConsistencyThresholdNotRecognized           = 10,

    ConservationThresholdOutOfRange             = 11,
    ConservationThresholdNotRecognized          = 12,

    ResidueOverlapOutOfRange                    = 13,
    ResidueOverlapNotRecognized                 = 14,

    SequencesOverlapOutOfRange                  = 15,
    SequencesOverlapNotRecognized               = 16,

    MaxIdentityOutOfRange                       = 17,
    MaxIdentityNotRecognized                    = 18,

    ClustersValueOutOfRange                     = 19,
    ClustersValueNotRecognized                  = 20,

    WindowValueOutOfRange                       = 21,
    WindowValueNotRecognized                    = 22,

    SelectSeqsNotRecognized                     = 23,
    SelectColsNotRecognized                     = 24,

    GapWindowValueOutOfRange                    = 25,
    GapWindowValueNotRecognized                 = 26,

    SimilarityWindowValueOutOfRange             = 27,
    SimilarityWindowValueNotRecognized          = 28,

    ConsistencyWindowValueOutOfRange            = 27,
    ConsistencyWindowValueNotRecognized         = 28,

    BlockSizeOutOfRange                         = 29,
    BlockSizeNotRecognized                      = 30,

    InFileComparisonStatistics                  = 31,

    IncompatibleArguments                       = 32,

    SelectSeqsResAndThresholdIncompatibilities  = 33,
    SelectSeqsResAndAutomathedMethodsIncompatibilities  = 34,
    SelectSeqsResAndWindowIncompatibilities     = 35,
    SelectSeqsResAndOverlapIncompatibilites     = 36,

    OnlyOneSequencesSelectionMethodAllowed      = 37,

    CombinationAmongTrimmingMethods             = 38,
    AutomathicMethodAndBlock                    = 39,

    WindowAndArgumentIncompatibilities          = 40,
    CombinationAmongThresholdsMethods           = 41,
    GeneralAndSpecificWindows                   = 42,
    StatisticsArgumentIncompatibilities         = 43,

    TrimmingMethodNeeded                        = 44,
    ForceFileWithoutCompareDataset              = 45,

    BacktranslationWithoutMainAlignment         = 46,

    NotAligned                                  = 47,

    MatrixGivenWithNoMethodToUseIt              = 48,

    SameNameOutput                              = 49,

    SequenceAndResiduesOverlapMutuallyNeeded    = 50,

    OutFileNeededWhenPrintingStatistics         = 51,

    AlignmentTypesNotMatching                   = 52,

    BlocksizeTooBig                             = 53,

    ParemeterOnlyOnBacktranslation              = 54,

    ProteinAlignmentMustBeAligned               = 55,

    BacktransAlignIsDNA                         = 56,



    ImpossibleToGenerate                        = 57,

    ImpossibleToProcessMatrix                   = 58,

    SelectOnlyAccepts                           = 59,

    MoreClustersThanSequences                   = 60,

    LeftBoundaryBiggerThanRightBoundary         = 61,

    DifferentNumberOfSequencesInCompareset      = 62,

    DifferentSeqsNamesInCompareset              = 63,

    CDScontainsProteinSequences                 = 64,

    SequenceContainsGap                         = 65,

    SequenceNotMultipleOfThree                  = 66,

    SequenceHasStopCodon                        = 67,

    SequenceNotPresentInCDS                     = 68,

    UnknownCharacter                            = 69,

    SequencesNotSameSize                        = 70,

    IncorrectSymbol                             = 71,

    UndefinedSymbol                             = 72,

    ParameterNotFoundOrRepeated                 = 73,

    SimilarityMatrixNotCompatibleWindow         = 74,

    PossibleMissmatch                           = 75,

    BracketsMissmatchFound                      = 76,

    UnalignedAlignmentToAlignedFormat           = 77,
    
    CantOpenFile                                = 78,
    
    FileIsEmpty                                 = 79,
    
    AlignmentFormatNotRecognized                = 80,
    
    OutputFormatNotRecognized                   = 81,
    
    OnlyOneFormatOnConsoleOutput                = 82,
    
    AlignmentNotSaved                           = 83,
    
    VerboseLevelNotRecognized                   = 84,
    
    NeedToSpecifyVerboseLevel                   = 85,

    __MAXERROR

};
enum WarningCode {
    RemovingOnlyGapsColumn                      = 1,

    KeepingOnlyGapsColumn                       = 2,

    SequenceWillBeCutted                        = 3,

    IncludingIndeterminationSymbols             = 4,

    LessNucleotidesThanExpected                 = 5,

    HeaderWillBeCut                             = 6,

    __MAXWARNING
};

enum InfoCode {
    CuttingSequence                             = 1,

    WindowSizeCompareset                        = 2,

    __MAXINFO
};

namespace __internalReport {

class __reporter {
    bool CanReport;
    
    public:
        
    __reporter(bool CanReport) : CanReport{CanReport} { }
    
    template <typename T>
    __reporter &operator<<(const T &a) {
        if (CanReport)
            std::cout<<a;
        return *this;
    }

    __reporter &operator<<(std::ostream& (*pf) (std::ostream&)) {
        if (CanReport)
            std::cout<<pf;
        return *this;
    }
};

class __reportSystem
{
private:
    
    __reporter canReport = __reporter(true);
    __reporter cantReport = __reporter(false);

    static const std::map<InfoCode, const char *>       InfoMessages ;
    static const std::map<WarningCode, const char *>    WarningMessages ;
    static const std::map<ErrorCode, const char *>      ErrorMessages ;
    
public:
    /** \brief Level of Verbosity.\n The report system won't output messages that are lower than the current level */
    
    VerboseLevel Level;
    
    
    bool IsDebug = false;

    /**
     \brief Method to print all Info, Warning and Error codes and their respective message.\n
            This method is usefull to check wheter all codes have a message linked to them.
            It will use the current VerboseLevel of the object, which defaults to ERROR level.
     */
    void PrintCodesAndMessages();

    /**
     \brief Method to report an Error. It will be displayed if VerboseManager::Level is equal or higher to VerboseLevel::Errors
     \param message Code to report.
     \param vars Array of strings that will replace the '[tags]' in the message. The number of elements in the array must be the same as [tag] aparitions on the message.\n
     <b> The method will take care of destroying the pointer </b>
     */
    void report(ErrorCode message, std::string * vars = NULL);

    /**
     \brief Method to report an Error. It will be displayed if VerboseManager::Level is equal or higher to ::VerboseLevel::Errors
     \param message Code to report.
     \param vars Array of chars that will replace the first aparition of '[tags]' in the message. \n
     <b> The method wont take care of destroying the pointer </b> This allows to reuse the parameter passed.
     */
    void report(ErrorCode message, char * vars);
    /**
    \brief Method to report a Watning. It will be displayed if VerboseManager::Level is equal or higher to VerboseManager::VerboseLevel::Warnings
    \param message Code to report.
    \param vars Array of strings that will replace the '[tags]' in the message. The number of elements in the array must be the same as [tag] aparitions on the message.\n
    <b> The method will take care of destroying the pointer </b>
    */
    void report(WarningCode message, std::string * vars = NULL);
    /**
     \brief Method to report a Warning. It will be displayed if VerboseManager::Level is equal or higher to VerboseManager::VerboseLevel::Warnings
     \param message Code to report.
     \param vars Array of chars that will replace the first aparition of '[tags]' in the message. \n
     <b> The method wont take care of destroying the pointer </b> This allows to reuse the parameter passed.
     */
    void report(WarningCode message, char * vars);
    /**
    \brief Method to report a Info message. It will be displayed if VerboseManager::Level is equal or higher to VerboseManager::VerboseLevel::Info
    \param message Code to report.
    \param vars Array of strings that will replace the '[tags]' in the message. The number of elements in the array must be the same as [tag] aparitions on the message.\n
    <b> The method will take care of destroying the pointer </b>
    */
    void report(InfoCode message, std::string * vars = NULL);
    /**
     \brief Method to report a Info message. It will be displayed if VerboseManager::Level is equal or higher to VerboseManager::VerboseLevel::Info
     \param message Code to report.
     \param vars Array of chars that will replace the first aparition of '[tags]' in the message. \n
     <b> The method wont take care of destroying the pointer </b> This allows to reuse the parameter passed.
     */
    void report(InfoCode message, char * vars);


//     void log(std::string debugMessage);
    
    __reporter log(VerboseLevel level)
    {
        if (!IsDebug) return cantReport;
        
        if (level >= Level)
            return canReport;
        else
            return cantReport;
    }

    template <typename T>
    __reportSystem &operator<<(const T &a) {
        if (IsDebug)
            std::cout<<a;
        return *this;
    }

    __reportSystem &operator<<(std::ostream& (*pf) (std::ostream&)) {
        if (IsDebug)
            std::cout<<pf;
        return *this;
    }

};

}

extern __internalReport::__reportSystem debug;

#endif // VERBOSEMANAGER_H

