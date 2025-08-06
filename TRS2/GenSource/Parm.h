#ifndef PARMS_H
#define PARMS_H

#define MAXLOOP 5
#define MAXSTEP 12

#include <QMainWindow>
#include <QString>
#include <QMap>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>

import Const;

struct LoopS {
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

struct StepS {
    int Control;
    int Com;
    int Axis;
    std::string Type;
    int Step;
    int Loop;
//    int Dir;
    std::string Sign;
    char Speed;
    std::string Mode;
    bool Sort;
//    char Moving;
//    char Started;
//    char DiffHome;
    bool Lcd;
    bool Hold;
    long Actual;
//    long Actual_mean_pow;
//    long Actual_std;
    long Delta;
    long Home;
    long Min;
    long Max;
    double Factor;
//    struct StandaS Standa;
    double FreqMax;
    double FreqMin;
    double FreqActual;
    double FreqDelta;
    double Freq;
//    long *Start;
//    long *Stop;
    std::string FName;
    std::string FPath;
//    struct Delay_GateS Delay_Gate;
//    struct Standa2S Standa2;
//    long StopGoal; // EDO
};




/* ########################   TYPE DEFINITION  ############################ */

//// DMD_TX Structures

//struct DmdTx_Node{
//    unsigned char data;
//    struct DmdTx_Node *next;
//};
//struct DmdTx_List{
//    int *data;
//    struct DmdTx_List *next;
//};

///** This structure contains all the data about the patterns to be sent to the dmd */
//struct DmdTx_Patterns{
//    unsigned char (*defPatterns)[12]; // pattern settings (exposure time, bit-depth, triggers, pattern index...)
//    unsigned char configureLut[6]; // configuration of Look up table (LUT)
//    unsigned char (*setBmp)[6]; // image settings (index, size)
//    unsigned char ***bmpLoad; // compressed BMP image to load
//    int nB;
//    int *packNum; // number of data packets (max 504 bytes) to be loaded
//    int nEl;
//    int **bitsPackNum; // size of each packet
//    int *exposure;
//    int numOfBatches;
//};

///** This structure contains data of the patterns for the dmd */
//struct Dmd{
//    hid_device *handle; // pointer to the hid device
//    struct DmdTx_Patterns *pattern; // structure containing the pattern for the DMD (see in dmd.h)
//    int szPattern;
//    int repeat;
//    char ReconsPy;
//};

///** This structure contains the parameters to set the measurements (type of pattern and duration) */
//struct InfoDmd{
//    int RasterOrHadamard; // selected mode for the measure
//    int nBasis;
//    int nMeas;
//    int startPosition;
//    int previousPos;
//    int exp;
//    int dark_time;
//    int repeat;
//    int compress;
//    int sizeBatch;
//    int zoom;
//    int xC;
//    int yC;
//    int csMode;
//    int startPx;
//    int endPx;
//};

struct FileS {
    char Type;
    char Dir   [PATHLEN];
    char Name  [PATHLEN];
    char Ext   [PATHLEN];
    char Prefix[PATHLEN];
    char Path  [PATHLEN];
    int Tag;
    char Save;
    FILE *File;
};

struct NumS {
    long Page;
    long Board;
    long Prot;
    long Det;
    long Fiber;
    long Source; //ALE
    long LoopxFrame;
};

struct FiberS {
    char Board;
    char Fiber;
    char Det;
    char Coord;
    char Pad;
    double Xf;
    double Yf;
    double Zf;
    double Rf;
    double Nf;											//ALE
    int row;										    //ALE
    int col;										    //ALE
};

struct SourceS {
    char Coord;
    char Pad;
    char Switch;
    char Chann;
    double Xs;
    double Ys;
    double Zs;
    double Rs;
    double Ns;											//ALE
    int row;										    //ALE
    int col;										    //ALE
};

struct TwitchS {
    char Chann[MAX_ACQ][MOXY_NUM_SWITCH];
    int NoSwitch;
};

struct TFiberS {
    char Board[MAX_ROW_FIBER];
    char Fibers[MAX_ROW_FIBER][STRLEN_FIBER];
    char Det[MAX_ROW_FIBER];
};

struct TSourceS {
    char Source[MAX_ROW_SOURCE];
    char Switch[MAX_ROW_SOURCE];
    char Chann[MAX_ROW_SOURCE];
};

struct ChannS {
    long First;
    long Last;
    long Num;
    double Fract;
};

struct GpibS {
    int hGpib;
    char sGpib[3];
};

struct MeasS {
    unsigned long Plot;
    unsigned long Roi;
    unsigned long Status;
    unsigned long Ram;
    char Clear;
    char Stop;
    char Autorun;
    char SkipOscill;
};

struct WaitS {
    char Type;
    long Pos;
    char Step;
};

struct JumpS {
    char Jump;
    char Loop;
    char Board;
    int Break;
    unsigned long Max;
    unsigned long Area;
};

struct RamS {
    unsigned long Loop;
    unsigned long LoopU;
    unsigned long Actual;
    unsigned long Num;
};

struct MammIdxS {
    int Home;
    int Top[MAMM_NUM_BOARD];
    int Border[MAMM_NUM_BOARD];
    int Actual;
    int First;
    int Last;
    int Num;
};

struct MammRateS {
    double High[MAMM_NUM_BOARD];
    double Mid[MAMM_NUM_BOARD];
    double Low[MAMM_NUM_BOARD];
    double Actual[MAMM_NUM_BOARD];
};

struct MammAttS{
    char Step;
    char Wait;
    //	int Idx[MAMM_NUM_ROW];
    int IdxMin;
    int IdxMin2;
    int IdxMax;
    int IdxMax2;
    int IdxGoal;
    double FreqOpen;
};

struct MammRefMeaS{	   //EDO
    double Width;
    double BaricentrePos;
    long MaxPos;
    long MaxVal;
    long Area;
    long First;
    long Last;
    double Treshold;
};
struct ScReinitS{  //EDO
    int Measure;
    int TrimmerPreBreak;
    int TrimmerPostBreak;
    int Oscilloscope;
    int InitMammot;
    int AnyOper;
};
struct NumAcqS{		  //EDO
    int Actual;
    float Tot;
    char Active;
};
struct ExtraFrameS{
    int Num;
    int IsActiveOnLoopYNum;
};
struct MammS {
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
    struct MammIdxS Idx[D2];
    struct MammRateS Count;
    struct MammRateS Rate;
    struct MammAttS Att[MAMM_NUM_BOARD];
    char OverTreshold;   //EDO
    char IsTop;					//EDO
    int ShiftBack;				//EDO
    int TopLim;					//EDO
    int CorrShift;				//EDO
    char Roi;					//EDO
    double Fract;				//EDO
    char IgnoreTrash;			//EDO
    char Status;
    char   IniFile[MAMM_NUM_BOARD][260];		//EDO
    struct MammRefMeaS RefMeas;				    //EDO
    struct NumAcqS NumAcq;		  //EDO
    struct ExtraFrameS ExtraFrame;             //EDO
    int IsRefMeas;
    double NegativeTreshold;
};

struct ActionS{
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
    //char NewFrame;
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
    char SpcTime;			//EDO
    char InitMamm;         //EDO
    char StartMamm;			 //EDO
    char CheckMamm;         //EDO
    char StopMamm;		    //EDO
    char DoJumpMamm;		//EDO
    struct ScReinitS ScReInit;			//EDO
};

struct TimeS {
    char Time;
    unsigned long Counter;	// Tasks
    char sCount[3];			// Strings Counters
    long Board;			// Tio Board Number
    double Start;
    double Stop;
};

struct TioS {
    long lDir, lEnable, lHalf, lSwitch0, lSwitch1, lSwitch2, lSwitch3;				// Lines used
    unsigned long tGate, tClock, tCount;	// Tasks
    char sGate[3], sClock[3], sCount[3];	// Strings Counters
    char sPort[2];							// Port Number within same Board
    long Board;							// Tio Board Number
};

struct NidaqS {
    long lDir, lEnable, lHalf, lSwitch0, lSwitch1, lSwitch2, lSwitch3;
    unsigned long tGate, tClock, tCount;
    char sGate[3], sClock[3], sCount[3];
    char sPort[2];
    long Board;
};

struct MioS {
    char sChann[2];							// Channel within same Board
    long Board;							// NIDAQ Board Number
};


struct StandaS {
    long Home;							// Home position in TICS (Steps=Tics x STANDA_TICSxSTEP)
};


struct AdcS {
    unsigned long taskmodpower_diode;
    char sPath[STRLEN];							// Channel Path as defined in the daq  syntax
    char sChann[2];							// Channel within same Board
    long Board;							// NIDAQ Board Number
    long Chann;							// NIDAQ Channel Number
    unsigned long Task;							// NIDAQ Task ID
    double Data[100000];					// Buffered Data
};

struct MonoTcpS {
    unsigned int Handle;
    long ServerValue;
    int ServerReady;
    char IpAddress[MONO_TCP_STRLEN];
};

struct Delay_GateS{
    char Str [N_BIT_DELAYER_GATE];
    float Value;
    char pChar[N_BIT_DELAYER_GATE_COMMAND];
    float Calib_Factor[N_BIT_DELAYER_GATE];
    float Calib_Calib[N_BIT_DELAYER_GATE];
};

struct Standa2S {
    int Device;
    long DeltaHome;
};

struct SwitchS {
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
    struct TioS Tio;
    struct MioS Mio;
    struct NidaqS Nidaq;
};


struct SyncS {
    char  Sync;
    char  Type;
    char  Loop;
    char  Pattern;
    char  Dir;
    char   Com;
    double Width;
    int	   Baud;
};


struct OmaS {
    int Oma;
    int Ready;
    int FileYes;
    int FileDirOk;
    int FileNameOk;
    char Loop;
    float Baric;
    float Peak;
    FILE *File;
    int DataStored;
    unsigned int g_hconv;
};

struct OphirS {
    int Ophir;
    char Loop;
    FILE *File;
};

struct PowerS {
    int Power;
    char Step;
    int Loop;
    struct AdcS Adc;
};

struct TrimS {
    //	struct ChannS Roi;
    struct ChannS Range;
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

//struct SpadS{
//    CNVWriter					WriterTRS;
//    CNVBufferedSubscriber	SubscriberTDC;
//    CNVData						DataTRS;
//    CNVData						DataTDC;
//    double						Time;
//    unsigned int				*Buffer;
//};

//struct NirsS{
//    uint32_t Handle;
//    uint32_t IntTime; // ms
//    int		 UirTime; // ms
//    int		 Freq;	  //MHz
//    int		 Lambda; // 1 -> Laser1 always active, 2 -> Laser2 always active, 3 -> toggling Laser1/Laser2
//    uint32_t *Hist;
//    uint32_t RegOut[NIRS_REGLEN];
//    int	InitializedBox;
//    int InitializedLaser;
//};

//struct LucaSpcS{
//    uint64_t Handle;
//    uint32_t IntTime; // ms
//    uint32_t CtrTime; // ms
//    int		 Freq;	  //MHz
//    uint32_t Lambda; // 0 -> END, 1->635nm,2->670nm,3->730nm,4->830nm,5->852nm,6->915nm,7->980nm,8->1040nm
//    uint32_t *Hist;
//    uint32_t RegOut[LUCA_REGLEN];
//    int	InitializedBox;
//    int InitializedLaser;
//};


//struct SurfaceConceptS{
//    int	 Refolding; //EDO
//    int	 ScBoard[MAX_BOARD];	 //EDO
//    int  ScBoardInitialized[MAX_BOARD];   //EDO
//    int  ScInitializedForMammot[MAX_BOARD];   //EDO
//    double ScTimeElapsed;//EDO
//    float  ScAcqTime;		//EDO
//    int    ScAutoTrim; //EDO
//    int ScPipeClose;			//EDO
//    int SelRepNum;			//EDO
//    int StartDivider;		//EDO
//    int ScFirstBin;			//EDO
//    int ScLastBin;			//EDO
//    int ScDeinit;		   //EDO
//    char ScWait;
//    int	 Pipe[MAX_BOARD][MAX_DET];
//    unsigned int ScNumBin; //EDO
//    char DCR_files[MAX_BOARD][MAX_DET][STRLEN];
//    double *LinArray;
//    FILE *FID;
//    SC1000_TYPE *NonLinArray;
//    SC1000_TYPE *DCR_raw_count;
//    double *DCR_raw_time;
//    double *Buffer;
//    double *Buffer2;
//    SC1000_TYPE *IRF_raw_count;
//    double *IRF_raw_time;
//    int Modulo; // perform Refolding operation via SC hardware. It corresponds to the Modulo length, i.e. Period=Number of Bins to refold (NOT SURE, VERIFY)
//    double ***NonLinDt;     // corrections coefficients
//    double Binsize;								// temporal width of the mean bin
//    double Period;									// period between two IRF peaks (used in rebinning)
//    double Rebin;
//};

//struct SwabS{
//    __int64 Binwidth; // channel (bin) width in ps (ps/ch)
//    int DetSync; // code identifying Sync Detector (1-based from UIR)
//    int DetSyncFreqMult; // code identifying Sync Detector after FreqMult (=DetSync if FreqMult=1)
//    int DetSign[SWAB_MAX_DET]; // code identifying Sign Detectors (1-based from UIR)
//    int DetType[SWAB_MAX_DET]; // code identifying type of detector (SWAB_NONE, SWAB_SYNC, SWAB_SIGN)
//    double Level[SWAB_MAX_DET]; // threshold (mV)
//    int Hysteresis[SWAB_MAX_DET]; // Hysteresis (mV) - accepted values: 1mV, 20mV, 70mV
//    int Delay[SWAB_MAX_DET]; // (ps) delay
//    int Deadtime[SWAB_MAX_DET]; // (ps) delay
//    Swab_TimeTag_TimeTagger Ttr; // handle to a Real Tagger object
//    Swab_TimeTag_TimeTaggerVirtual Ttv; // handle to Virtual Tagger object
//    Swab_TimeTag_FrequencyMultiplier Fm; // handle to Frequency Multiplier object
//    Swab_TimeTag_TimeTaggerBase Ttb; // handle to Base Tagger object
//    Swab_TimeTag_HistogramLogBins Corr[SWAB_MAX_DET]; // handle to Correlation object
//    //Swab_TimeTag_Correlation Corr[SWAB_MAX_DET]; // handle to Correlation object
//    Swab_TimeTag_Histogram Hist[SWAB_MAX_DET]; // handle to Correlation object
//    Swab_TimeTag_FileWriter Fw; // handle to File Write object
//    CDotNetHandle Except; // handle to Exception raised by the .NET function in the Swab library
//    char* FNameVirt[STRLEN]; // file name for reading the TimeTags
//    char* FPathVirt[STRLEN]; // complete file path for reading the TimeTags
//    char* FPathOut[STRLEN]; // complete file path for writing the TimeTags
//    __int64 TimeSW; // duration in ps of acquisition
//    int Meas; // type of measurement, as defined in #define
//    int isFwRunning;
//    int SaveTags; // activate saving of TimeTags on File
//    int Type;
//    int FreqMult; // multiplication factor for refolding after frequency divider
//    int FreqDiv; // divider factor for reducing Sync
//};


// Ring buffer structure
struct RingBufferS {
    unsigned int *data;
    unsigned int front;
    unsigned int rear;
    unsigned int count;
    std::mutex mutex;
    std::condition_variable notEmpty;
    bool stop;
};

typedef struct RingBufferMA{
    struct RingBufferS* bufferM; // Measurement data buffer
    struct RingBufferS* bufferA; // Analyzed data buffer
};



struct MharpS{
    int Mode; // MHARP_MODE_HIST=standard histogramming, MHARP_MODE_T3=continuous flow using T3 (time-tags)
    //int oflcorrection; // overflow correction. remember number of occured overflow in sync time
    int SyncRate; // sync rate needed to control Tacq (expressed in terms of sync counts)
    //int Sync0; // initial sync value (number of elapsed syncs)
    uint64_t SyncGoal; // sync counts that delimit the next Tacq (already corrected for overflow)
    //int PassedTacq; // number of acquisitions up to now since board was started
    int NextAcq; // reached Tacq
    int NumRecords; // number of records in FIFO
    int FirstMarker; // detected the first marker in continuous flow
    int Binning; // binning of the acquisition bins (i.e. channels in old TRS)
    int SyncDivider; // to be used to reduce sync rate to max 75MHz, otherwise use 1
    int LenCode; // Power of 2 of the HystLen (=P.Chann.Num)
    int Offset; // shift of the histogram (ns) (maybe useful in few cases to discard part of the histogram)
    int SyncOffset; // offset of the sync (ps)
    int SyncLevel; // threshold for the sync (mV)
    int SyncEdge; // 0=falling, 1=rising
    int SyncDeadtime; // delay before a new sync is taken (ps)
    int InputOffset[MHARP_MAX_DET]; // offset of the signal (ps)
    int InputLevel[MHARP_MAX_DET]; // threshold for the signal (mV)
    int InputEdge[MHARP_MAX_DET]; // 0=falling, 1=rising
    int InputDeadtime[MHARP_MAX_DET]; // delay before a new input is taken (ps)
    int SaveTags; // save file with time-tags. Format=Flow of TimeTags as retrieved with ReadFifo
    char PathTags[PATHLEN]; // pathlength of the TAGS file
    FILE *FileTags; // pointer to the TAGS FILE
    struct RingBufferS RingBufferM; // ring buffer for Measurement
    struct RingBufferS RingBufferA; // ring buffer for Analysis
    struct RingBufferMA RingBufferMA; // ring buffer for Analysis
    std::thread AcquireThread; // handle for Multithread functions
    std::thread AnalyzeThread; // handle for Multithread functions
};

struct SpcS {
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
//    int	 Refolding; //EDO
//    int	 ScBoard[MAX_BOARD];	 //EDO
//    int  ScBoardInitialized[MAX_BOARD];   //EDO
//    int  ScInitializedForMammot[MAX_BOARD];   //EDO
//    double ScTimeElapsed;//EDO
//    float  ScAcqTime;		//EDO
//    int    ScAutoTrim; //EDO
//    int ScPipeClose;			//EDO
//    int SelRepNum;			//EDO
//    int StartDivider;		//EDO
//    int ScFirstBin;			//EDO
//    int ScLastBin;			//EDO
//    int ScDeinit;		   //EDO
//    char ScWait;			//EDO
//    int	 Pipe[MAX_BOARD][MAX_DET];//EDO
//    unsigned int ScNumBin; //EDO
//    struct SurfaceConceptS SC;   //EDO
//    struct SpadS Spad[MAX_BOARD];
//    struct NirsS Nirs[MAX_BOARD];
//    struct LucaSpcS Luca[MAX_BOARD];
//    struct SwabS Swab[MAX_BOARD];
//    struct BcdS Bcd[MAX_BOARD];
    struct MharpS Mharp[MAX_BOARD];
};

struct AcqS{
    long Bank;
    long Frame;
    long Counter;
    long Actual;
    long Tot;
};

struct PageS{
    char Source;
    char Fiber;
    char Board;
    long Acq;
    double TimeNom;
    double TimeEff;
};

struct FrameS{
    long Num;
    long Actual;
    int Min;
    int Max;
    int First;		 //EDO
    int Half;		 //EDO
    int Dir;		 //EDO
    int Last;		 //EDO
};

struct FilterS{
    long Actual;
    long Page[MAX_ACQ][MAX_BOARD][MAX_DET];
};

struct RoiS{
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

struct PlotS{
    long NumO;
    long NumM;
    int Plot[MAX_PLOT];
    int PageU[MAX_PLOT];
};

struct GraphS{
    char Type;
    char Scale;
};

struct TProtS{
    long AcqStart[MAX_ROW_PROT];
    long AcqStop[MAX_ROW_PROT];
    char Fibers[MAX_ROW_PROT][STRLEN_PROT];
    long Source[MAX_ROW_PROT];
};

struct TBlockS{
    int Num[MAX_ROW_PRES_BLOCK];
    int Type[MAX_ROW_PRES_BLOCK];
    int StartFrame[MAX_ROW_PRES_BLOCK];
    int StopFrame[MAX_ROW_PRES_BLOCK];
    char Param1[MAX_ROW_PRES_BLOCK][2];
    int Param2[MAX_ROW_PRES_BLOCK];
    int Param3[MAX_ROW_PRES_BLOCK];
};

struct TSequenceS{
    int BlockUsed[MAX_ROW_PRES_BLOCK];
    int Repeat[MAX_ROW_PRES_BLOCK];
    int Shuffle;
    int FrameTot;
};

struct TPartitionS{
    int LoopFactor[MAX_ROW_PRES_LOOP];
    int Align;
};

struct BlockObjS{
    int Num;
    int Length;
    int ActualRepetition;
    int LengthPart[MAX_ROW_PRES_BLOCK];
    int TypePart[MAX_ROW_PRES_BLOCK];
    char Param1[MAX_ROW_PRES_BLOCK][2];
    int Param2[MAX_ROW_PRES_BLOCK];
    int Param3[MAX_ROW_PRES_BLOCK];
};

struct ValueS{
    char Roi;
};

struct OscillS {
    double Time;
    long First[MAX_ROW_OSCILL];
    long Last[MAX_ROW_OSCILL];
    long Num[MAX_ROW_OSCILL];
    double Fract[MAX_ROW_OSCILL];
    struct ChannS Zoom;
};

struct CommandS{
    int Abort;
    int Continue;
    char ReadUIR;
};

struct ContestS{
    char Run;
    char Function;
};

struct ChronoS {
    char Chrono;
    double Now;
    double Delta;
};

struct LabelS {
    char Name[LABEL_NAMELEN];
    char Content[LABEL_CONTENTLEN];
    int Auto;
};

struct DoStepS {
    char Step;
    long Home;
    long Goal;
    char Oscill;
    char Break;
    char Return;
};

struct ConstS {
    double Rho;
    double Thick;
    double N;
};



/* Note Per Lorenzo
campo SubHeader
campo size Header
campo size SubHeader
int->long
VER_MAMM_HEADER (qualenumero?)
togliere commenti su INIT_SPC (per me)
*/

/*++#pragma pack(push,1)
T_HEAD{
    short Ver[2];
    long SubHeader;
    long SubHeadVer;
    long SizeHeader;
    long SizeSubHeader;
    long SizeData;
    long Kind;
    long Appl;
    long Oma;
    char Date[10+1];
    char Time[8+1];
    long LoopHome[MAX_LOOP-2];	  // for compatibility with FIT, use only LOOP3,LOOP4,LOOP5
    long LoopFirst[MAX_LOOP-2];
    long LoopLast[MAX_LOOP-2];
    long LoopDelta[MAX_LOOP-2];
    long LoopNum[MAX_LOOP-2];
    long McaChannNum;
    long PageNum;
    long FrameNum;
    long RamNum;
    double McaTime;
    double McaFactor;
    long MeasNorm;
    char LabelName[LABEL_MAX][LABEL_NAMELEN];
    char LabelContent[LABEL_MAX][LABEL_CONTENTLEN];
    double Constn;
    double ConstRho;
    double ConstThick;
    long MammHeader;
    long MammIdxFirst[D2];
    long MammIdxLast[D2];
    long MammIdxTop[D2];
    long MammRateMid[D2];
    long MammRateHigh[D2];
};*/

/*++T_SUB{
    char Geom;
    char Source;
    char Fiber;
    char Det;
    char Board;
    char Coord;
    char Pad;
    double Xf;
    double Yf;
    double Zf;
    double Rf;
    double Xs;
    double Ys;
    double Zs;
    double Rs;
    double Rho;
    double TimeNom;
    double TimeEff;
    double n;
    long Loop[MAX_LOOP-2];		  // for compatibility with FIT, use only LOOP3,LOOP4,LOOP5
    long Acq;
    long Page;
    char RoiNum;
    short RoiFirst[MAX_ROI_SUB];
    short RoiLast[MAX_ROI_SUB];
    double RoiLambda[MAX_ROI_SUB];
    double RoiPower[MAX_ROI_SUB];
};
#pragma pack(pop)*/

struct InfoS {
    char Kind;
    char Appl;
    char Geom;
    char SubHeader;
    char Monitor;
};

struct MoxyS {
    int Moxy;
    char Command[STRLEN];
    long TimeMic;
    float TimeSpc;
    int DisplayDivisor;
    int PresentationRise;
    int ExternalTrigger;
};

struct LayoutS {
    int Layout;
    char Order;
    char FGeometry[STRLEN];
};

struct PresentationS {
    int Flag;
    char FInitPresentationName[STRLEN];
    char FInitPresentationDir[STRLEN];
    char FStimuliName[STRLEN];
    char FStimuliDir[STRLEN];
};

struct FlowS {
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

struct ParmS {
    struct OscillS Oscill;
    struct CommandS Command;
    struct ContestS Contest;
    struct FileS File;
    struct GpibS Gpib[3];
    struct SpcS Spc;
    struct ChannS Chann;
    struct AcqS Acq;
    struct PageS Page[MAX_PAGE];
    struct FrameS Frame;
    struct NumS Num;
    struct FilterS Filter;
    struct RoiS Roi;
    struct PlotS Plot;
    struct GraphS Graph;
    struct ValueS Value;
    struct TProtS TProt;
    struct TFiberS TFiber;
    struct TSourceS TSource;
    struct FiberS Fiber[MAX_FIBER];
    //struct SourceS Source[MAX_ROW_SOURCE];  //ALE
    struct SourceS Source[MAX_SOURCE]; 		  //ALE
    struct TwitchS Twitch;
    struct MeasS Meas;
    struct RamS Ram;
    struct ActionS Action;
    struct JumpS Jump;
    struct ChronoS Chrono;
    struct LoopS Loop[MAX_LOOP];
    struct StepS Step[MAX_STEP];
    struct SwitchS Switch[MAX_SWITCH];
    struct SyncS Sync;
    struct OmaS Oma;
    struct OphirS Ophir;
    struct PowerS Power;
    struct TrimS Trim[MAX_TRIM];
    struct MammS Mamm;
    struct LabelS Label[LABEL_MAX];
    struct DoStepS DoStep[DOSTEP_MAX];
    struct ConstS Const;
    struct TimeS Time;
    struct WaitS Wait;
    struct InfoS Info;
    struct MoxyS Moxy;
    struct LayoutS Layout;
    struct PresentationS Presentation;
    struct TBlockS TBlock;
    struct TSequenceS TSequence;
    struct TPartitionS TPartition;
    struct BlockObjS BlockObj[MAX_ROW_PRES_BLOCK];
    struct FlowS Flow;
};

// Data Structures
struct DataS {
    /*++T_HEAD Head;		// D.Head
    T_SUB **Sub;		// D.Sub[P.Frame.Num][P.Num.Page]
    T_DATA ***Data;		// D.Data[P.Frame.Num][P.Num.Page][P.Num.Chann]
    T_DATA **Osc;		// D.Osc[P.Num.Board*P.Num.Det][P.Num.Chann]
    T_DATA **Buffer;	// D.Buffer[P.Num.Board][P.Num.Det*P.Num.Chann]
    T_DATA **Bank;		// D.Bank[P.Num.Board][SPC_BANK_DIM] or D.Bank[P.Num.Board][MAX FIFO MHARP] // not a problem: there is a calloc later
    T_DATA *Curve;		// D.Curve[P.Num.Chann]
    T_DATA *Last;		// D.Last[P.Num.Chann]
    SC1000_TYPE ***BufferTDC;
    */
};

















extern ParmS P;

#endif // PARMS_H
