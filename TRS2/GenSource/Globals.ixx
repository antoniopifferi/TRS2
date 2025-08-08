// Parm.ixx — C++23 module interface for MSVC

//------------------------------
// Global module fragment
// (for legacy headers/macros that can't be "import"ed)
//------------------------------
module;
#include <stdio.h>                 // brings plain FILE into global namespace
#include <stddef.h>                // size_t etc., just in case

// If you truly need Qt here, include it in the global fragment.
// (Not used in the declarations below, so omitted.)
// #include <QMainWindow>
// #include <QString>
// #include <QMap>

//------------------------------
// Module interface
//------------------------------
export module Globals;

// Standard library imports used in exported declarations
import <string>;
import <cstdint>;
import <vector>;
import <mutex>;
import <condition_variable>;
import <thread>;

// Your constants/types come from this module.
// Re-export so importers of Parm see them without importing Const separately.
export import Const;

//------------------------------
// Exported declarations
//------------------------------

export struct LoopS {
    int Home;
    int First;
    int Last;
    int Delta;
    int Num;
    int Actual;
    std::string FileBreak;
    bool Break;
    bool Invert;
    std::string Cont;
};

export struct StepS {
    int Control;
    int Com;
    int Axis;
    std::string Type;
    int Step;
    int Loop;
    std::string Sign;
    char Speed;
    std::string Mode;
    bool Sort;
    bool Lcd;
    bool Hold;
    long Actual;
    long Delta;
    long Home;
    long Min;
    long Max;
    double Factor;
    double FreqMax;
    double FreqMin;
    double FreqActual;
    double FreqDelta;
    double Freq;
    std::string FName;
    std::string FPath;
};

export struct FileS {
    char Type;
    char Dir[PATHLEN];
    char Name[PATHLEN];
    char Ext[PATHLEN];
    char Prefix[PATHLEN];
    char Path[PATHLEN];
    int Tag;
    char Save;
    FILE* File;
};

export struct NumS {
    long Page;
    long Board;
    long Prot;
    long Det;
    long Fiber;
    long Source; // ALE
    long LoopxFrame;
};

export struct FiberS {
    char Board;
    char Fiber;
    char Det;
    char Coord;
    char Pad;
    double Xf;
    double Yf;
    double Zf;
    double Rf;
    double Nf;         // ALE
    int row;           // ALE
    int col;           // ALE
};

export struct SourceS {
    char Coord;
    char Pad;
    char Switch;
    char Chann;
    double Xs;
    double Ys;
    double Zs;
    double Rs;
    double Ns;         // ALE
    int row;           // ALE
    int col;           // ALE
};

export struct TwitchS {
    char Chann[MAX_ACQ][MOXY_NUM_SWITCH];
    int NoSwitch;
};

export struct TFiberS {
    char Board[MAX_ROW_FIBER];
    char Fibers[MAX_ROW_FIBER][STRLEN_FIBER];
    char Det[MAX_ROW_FIBER];
};

export struct TSourceS {
    char Source[MAX_ROW_SOURCE];
    char Switch[MAX_ROW_SOURCE];
    char Chann[MAX_ROW_SOURCE];
};

export struct ChannS {
    long First;
    long Last;
    long Num;
    double Fract;
};

export struct GpibS {
    int hGpib;
    char sGpib[3];
};

export struct MeasS {
    unsigned long Plot;
    unsigned long Roi;
    unsigned long Status;
    unsigned long Ram;
    char Clear;
    char Stop;
    char Autorun;
    char SkipOscill;
};

export struct WaitS {
    char Type;
    long Pos;
    char Step;
};

export struct JumpS {
    char Jump;
    char Loop;
    char Board;
    int Break;
    unsigned long Max;
    unsigned long Area;
};

export struct RamS {
    unsigned long Loop;
    unsigned long LoopU;
    unsigned long Actual;
    unsigned long Num;
};

export struct MammIdxS {
    int Home;
    int Top[MAMM_NUM_BOARD];
    int Border[MAMM_NUM_BOARD];
    int Actual;
    int First;
    int Last;
    int Num;
};

export struct MammRateS {
    double High[MAMM_NUM_BOARD];
    double Mid[MAMM_NUM_BOARD];
    double Low[MAMM_NUM_BOARD];
    double Actual[MAMM_NUM_BOARD];
};

export struct MammAttS {
    char Step;
    char Wait;
    int IdxMin;
    int IdxMin2;
    int IdxMax;
    int IdxMax2;
    int IdxGoal;
    double FreqOpen;
};

export struct MammRefMeaS { // EDO
    double Width;
    double BaricentrePos;
    long MaxPos;
    long MaxVal;
    long Area;
    long First;
    long Last;
    double Treshold;
};

export struct ScReinitS {  // EDO
    int Measure;
    int TrimmerPreBreak;
    int TrimmerPostBreak;
    int Oscilloscope;
    int InitMammot;
    int AnyOper;
};

export struct NumAcqS {    // EDO
    int Actual;
    float Tot;
    char Active;
};

export struct ExtraFrameS {
    int Num;
    int IsActiveOnLoopYNum;
};

export struct MammS {
    char Mamm;
    char AutoLabel;
    char FindTop;
    int IterBord;
    int IdxBorderNIR;
    double BackTopNIR;
    double Lambda[MAMM_NUM_LAMBDA];
    char Step[D2];
    char Loop[D2];
    char Shrink[D2];
    MammIdxS Idx[D2];
    MammRateS Count;
    MammRateS Rate;
    MammAttS Att[MAMM_NUM_BOARD];
    char OverTreshold;   // EDO
    char IsTop;          // EDO
    int ShiftBack;       // EDO
    int TopLim;          // EDO
    int CorrShift;       // EDO
    char Roi;            // EDO
    double Fract;        // EDO
    char IgnoreTrash;    // EDO
    char Status;
    char   IniFile[MAMM_NUM_BOARD][260];  // EDO
    MammRefMeaS RefMeas;                  // EDO
    NumAcqS NumAcq;                        // EDO
    ExtraFrameS ExtraFrame;                // EDO
    int IsRefMeas;
    double NegativeTreshold;
};

export struct ActionS {
    char Status;
    char CheckJump;
    char DoJump;
    char MoveSwitch[MAX_SWITCH];
    char MoveStep[MAX_STEP];
    char WaitStep[MAX_STEP];
    char StartCont[MAX_STEP];
    char WaitCont[MAX_STEP];
    char Trim[MAX_TRIM];
    char Break[MAX_LOOP];
    char StartSync;
    char StopSync;
    char SpcReset;
    char SpcStop;
    char SpcOut;
    char WaitEnd;
    char WaitChrono;
    char DisplayStatus;
    char DisplayRoi;
    char DisplayPlot;
    char DataSave;
    char StartOma;
    char StopOma;
    char Ophir;
    char StopAdc;
    char StartAdc;
    char WaitAdc;
    char ReadUIR;
    char SpcFlow;
    char StartFlow;
    char StopFlow;
    char ReconsPy;
    char SpcTime;       // EDO
    char InitMamm;      // EDO
    char StartMamm;     // EDO
    char CheckMamm;     // EDO
    char StopMamm;      // EDO
    char DoJumpMamm;    // EDO
    ScReinitS ScReInit; // EDO
};

export struct TimeS {
    char Time;
    unsigned long Counter;  // Tasks
    char sCount[3];         // String Counters
    long Board;             // Tio Board Number
    double Start;
    double Stop;
};

export struct TioS {
    long lDir, lEnable, lHalf, lSwitch0, lSwitch1, lSwitch2, lSwitch3;
    unsigned long tGate, tClock, tCount;
    char sGate[3], sClock[3], sCount[3];
    char sPort[2];
    long Board;
};

export struct NidaqS {
    long lDir, lEnable, lHalf, lSwitch0, lSwitch1, lSwitch2, lSwitch3;
    unsigned long tGate, tClock, tCount;
    char sGate[3], sClock[3], sCount[3];
    char sPort[2];
    long Board;
};

export struct MioS {
    char sChann[2];
    long Board;
};

export struct StandaS {
    long Home; // in TICS
};

export struct AdcS {
    unsigned long taskmodpower_diode;
    char sPath[STRLEN];
    char sChann[2];
    long Board;
    long Chann;
    unsigned long Task;
    double Data[100000];
};

export struct MonoTcpS {
    unsigned int Handle;
    long ServerValue;
    int ServerReady;
    char IpAddress[MONO_TCP_STRLEN];
};

export struct Delay_GateS {
    char Str[N_BIT_DELAYER_GATE];
    float Value;
    char pChar[N_BIT_DELAYER_GATE_COMMAND];
    float Calib_Factor[N_BIT_DELAYER_GATE];
    float Calib_Calib[N_BIT_DELAYER_GATE];
};

export struct Standa2S {
    int Device;
    long DeltaHome;
};

export struct SwitchS {
    char  Switch;
    int Control;
    char  Device;
    char  Type;
    int Com;
    char  Line0;
    char Port[2];
    int Board;
    char  Loop;
    char Mode;
    long Home;
    long Pos[MAXPOS];
    long Actual;
    char  FName[STRLEN];
    char  FPath[STRLEN];
    TioS Tio;
    MioS Mio;
    NidaqS Nidaq;
};

export struct SyncS {
    char  Sync;
    char  Type;
    char  Loop;
    char  Pattern;
    char  Dir;
    char   Com;
    double Width;
    int	   Baud;
};

export struct OmaS {
    int Oma;
    int Ready;
    int FileYes;
    int FileDirOk;
    int FileNameOk;
    char Loop;
    float Baric;
    float Peak;
    FILE* File;
    int DataStored;
    unsigned int g_hconv;
};

export struct OphirS {
    int Ophir;
    char Loop;
    FILE* File;
};

export struct PowerS {
    int Power;
    char Step;
    int Loop;
    AdcS Adc;
};

export struct TrimS {
    ChannS Range;
    int Control;
    char Type;
    char Wait;
    char Scan;
    char Dir;
    char Region;
    char Step;
    char Trim;
    char Loop;
    char FileTrim;
    double Fract;
    char Target;
    double Goal;
    double Low;
    double High;
    double Best;
    double BestW;
    double BestA;
    double Value;
    char Sign;
    char Success;
    char Improved;
    char ImprovedW;
    char ImprovedA;
    char Stop;
    char Boundary;
    char Increase;
    double Time;
    double DeltaU;
    long Delta;
    int Num;
    int Trial;
    int Set;
    int SetW;
    int SetA;
    char Display;
    char Status;
    char Break;
    char Prompt;
    long PosBest;
    long PosAct;
    long PosW;
    long PosA;
    long Label[MAXPOS];
    double Pos[MAXPOS];
    int RegionFile[MAXPOS];
    char  FName[STRLEN];
    char  FPath[STRLEN];
    char RegionActual;
};

// Ring buffer structures
export struct RingBufferS {
    unsigned int* data;
    unsigned int front;
    unsigned int rear;
    unsigned int count;
    std::mutex mutex;
    std::condition_variable notEmpty;
    bool stop;
};

// Fixed: was an invalid typedef in the header. Now a normal exported struct.
export struct RingBufferMA {
    RingBufferS* bufferM; // Measurement data buffer
    RingBufferS* bufferA; // Analyzed data buffer
};

export struct MharpS {
    int Mode;                // MHARP_MODE_HIST / MHARP_MODE_T3
    int SyncRate;            // sync counts
    std::uint64_t SyncGoal;  // next Tacq delimiter
    int NextAcq;
    int NumRecords;
    int FirstMarker;
    int Binning;
    int SyncDivider;
    int LenCode;
    int Offset;
    int SyncOffset;
    int SyncLevel;
    int SyncEdge;            // 0=falling, 1=rising
    int SyncDeadtime;
    int InputOffset[MHARP_MAX_DET];
    int InputLevel[MHARP_MAX_DET];
    int InputEdge[MHARP_MAX_DET];     // 0=falling, 1=rising
    int InputDeadtime[MHARP_MAX_DET];
    int SaveTags;
    char PathTags[PATHLEN];
    FILE* FileTags;
    RingBufferS RingBufferM;
    RingBufferS RingBufferA;
    RingBufferMA RingBufferMA;
    std::thread AcquireThread;
    std::thread AnalyzeThread;
};

export struct SpcS {
    char   Type;
    char   Control;
    char   Trash;
    char   Started;
    char   SkipZero;
    char   Overflow;
    char   Subtract;
    char   Format;
    int	   Init;
    double TimeInit;
    double Zero;
    double EffTime[MAX_BOARD];
    double TimeO;
    double TimeM;
    int	   TimeHydra;
    int	   TimeMharp;
    int	   TimeTH260;
    int	   TH260HistLen;
    int	   TimeSC1000;
    long   Count;
    char   TdcDcrFileRoot[260];
    char   Scale;
    double Calib;
    double Factor;
    int    RoutingBits;
    double RepRate;
    int	   MaxPage[MAX_BOARD];
    char   Settings[MAX_BOARD][260];
    char   IniFile[MAX_BOARD][260];
    MharpS Mharp[MAX_BOARD];
};

export struct AcqS {
    long Bank;
    long Frame;
    long Counter;
    long Actual;
    long Tot;
};

export struct PageS {
    char Source;
    char Fiber;
    char Board;
    long Acq;
    double TimeNom;
    double TimeEff;
};

export struct FrameS {
    long Num;
    long Actual;
    int Min;
    int Max;
    int First;   // EDO
    int Half;    // EDO
    int Dir;     // EDO
    int Last;    // EDO
};

export struct FilterS {
    long Actual;
    long Page[MAX_ACQ][MAX_BOARD][MAX_DET];
};

export struct RoiS {
    char Window;
    char RoiM[MAX_ROW_ROI];
    char RoiO[MAX_ROW_ROI];
    long First[MAX_ROW_ROI];
    long Last[MAX_ROW_ROI];
    double Fract[MAX_ROW_ROI];
    long Page[MAX_ROW_ROI];
    long Area[MAX_ROW_ROI];
    double Width[MAX_ROW_ROI];
    double Lambda[MAX_ROW_ROI];
    double Rho[MAX_ROW_ROI];
};

export struct PlotS {
    long NumO;
    long NumM;
    int Plot[MAX_PLOT];
    int PageU[MAX_PLOT];
};

export struct GraphS {
    char Type;
    char Scale;
};

export struct TProtS {
    long AcqStart[MAX_ROW_PROT];
    long AcqStop[MAX_ROW_PROT];
    char Fibers[MAX_ROW_PROT][STRLEN_PROT];
    long Source[MAX_ROW_PROT];
};

export struct TBlockS {
    int Num[MAX_ROW_PRES_BLOCK];
    int Type[MAX_ROW_PRES_BLOCK];
    int StartFrame[MAX_ROW_PRES_BLOCK];
    int StopFrame[MAX_ROW_PRES_BLOCK];
    char Param1[MAX_ROW_PRES_BLOCK][2];
    int Param2[MAX_ROW_PRES_BLOCK];
    int Param3[MAX_ROW_PRES_BLOCK];
};

export struct TSequenceS {
    int BlockUsed[MAX_ROW_PRES_BLOCK];
    int Repeat[MAX_ROW_PRES_BLOCK];
    int Shuffle;
    int FrameTot;
};

export struct TPartitionS {
    int LoopFactor[MAX_ROW_PRES_LOOP];
    int Align;
};

export struct BlockObjS {
    int Num;
    int Length;
    int ActualRepetition;
    int LengthPart[MAX_ROW_PRES_BLOCK];
    int TypePart[MAX_ROW_PRES_BLOCK];
    char Param1[MAX_ROW_PRES_BLOCK][2];
    int Param2[MAX_ROW_PRES_BLOCK];
    int Param3[MAX_ROW_PRES_BLOCK];
};

export struct ValueS {
    char Roi;
};

export struct OscillS {
    double Time;
    long First[MAX_ROW_OSCILL];
    long Last[MAX_ROW_OSCILL];
    long Num[MAX_ROW_OSCILL];
    double Fract[MAX_ROW_OSCILL];
    ChannS Zoom;
};

export struct CommandS {
    int Abort;
    int Continue;
    char ReadUIR;
};

export struct ContestS {
    char Run;
    char Function;
};

export struct ChronoS {
    char Chrono;
    double Now;
    double Delta;
};

export struct LabelS {
    char Name[LABEL_NAMELEN];
    char Content[LABEL_CONTENTLEN];
    int Auto;
};

export struct DoStepS {
    char Step;
    long Home;
    long Goal;
    char Oscill;
    char Break;
    char Return;
};

export struct ConstS {
    double Rho;
    double Thick;
    double N;
};

// Info / control blocks
export struct InfoS {
    char Kind;
    char Appl;
    char Geom;
    char SubHeader;
    char Monitor;
};

export struct MoxyS {
    int Moxy;
    char Command[STRLEN];
    long TimeMic;
    float TimeSpc;
    int DisplayDivisor;
    int PresentationRise;
    int ExternalTrigger;
};

export struct LayoutS {
    int Layout;
    char Order;
    char FGeometry[STRLEN];
};

export struct PresentationS {
    int Flag;
    char FInitPresentationName[STRLEN];
    char FInitPresentationDir[STRLEN];
    char FStimuliName[STRLEN];
    char FStimuliDir[STRLEN];
};

export struct FlowS {
    char Flow;
    int Slot0;
    int NumSlot;
    int Page0;
    int EmptyBank;
    int FilledFrame;
    int Bank;
    int Spcm;
    int Mharp;
    volatile int StopMultiThread;
    int MultiThreadFunctionId;
    int NumRecords;
};

// Root aggregate
export struct ParmS {
    OscillS Oscill;
    CommandS Command;
    ContestS Contest;
    FileS File;
    GpibS Gpib[3];
    SpcS Spc;
    ChannS Chann;
    AcqS Acq;
    PageS Page[MAX_PAGE];
    FrameS Frame;
    NumS Num;
    FilterS Filter;
    RoiS Roi;
    PlotS Plot;
    GraphS Graph;
    ValueS Value;
    TProtS TProt;
    TFiberS TFiber;
    TSourceS TSource;
    FiberS Fiber[MAX_FIBER];
    SourceS Source[MAX_SOURCE];   // ALE
    TwitchS Twitch;
    MeasS Meas;
    RamS Ram;
    ActionS Action;
    JumpS Jump;
    ChronoS Chrono;
    LoopS Loop[MAX_LOOP];
    StepS Step[MAX_STEP];
    SwitchS Switch[MAX_SWITCH];
    SyncS Sync;
    OmaS Oma;
    OphirS Ophir;
    PowerS Power;
    TrimS Trim[MAX_TRIM];
    MammS Mamm;
    LabelS Label[LABEL_MAX];
    DoStepS DoStep[DOSTEP_MAX];
    ConstS Const;
    TimeS Time;
    WaitS Wait;
    InfoS Info;
    MoxyS Moxy;
    LayoutS Layout;
    PresentationS Presentation;
    TBlockS TBlock;
    TSequenceS TSequence;
    TPartitionS TPartition;
    BlockObjS BlockObj[MAX_ROW_PRES_BLOCK];
    FlowS Flow;
};

// Optional placeholder for future data container
export struct DataS {
    // Intentionally empty (commented out in original header)
};

// Export the external declaration; define it in a module implementation unit:
// module Parm;  ParmS P{};
export extern ParmS P;
