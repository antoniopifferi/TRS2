/* STEPPER CONSTANTS */
#define STEP_SIGN_POS	0
#define STEP_SIGN_NEG	1
#define WAIT_FALSE		0
#define WAIT_TRUE		1
#define NEWP_VEL_CORR	(1.000/1.005) // Empirical correction factor for nominal velocity
#define NEWP_FAST_RV	400		// Ramp Velocity (um/s) #400
#define NEWP_SLOW_RV	100		// Ramp Velocity (um/s) #100
#define NEWP_CONT_RV	5000	// Ramp Velocity (um/s) #5000
#define NEWP_FAST_XV	65000	// Max  Velocity (um/s) #65000
#define NEWP_SLOW_XV	1000	// Max  Velocity (um/s) #1000
#define NEWP_CONT_XV	100000	// Max  Velocity (um/s) #100000
#define NEWP_FAST_RW	1000	// Ramp Width (ms)      #1000
#define NEWP_SLOW_RW	500		// Ramp Width (ms)		#500
#define NEWP_CONT_RW	500		// Ramp Width (ms)	    #500
#define NEWP_FAST_SV	4000	// Set Velocity (um/s)  #40000
#define NEWP_SLOW_SV	200		// Set Velocity (um/s)  #200
#define STEP_EQUAL_POS	11		// Maximum number of unchanged pos
#define FACTOR_MONO	   1
#define FACTOR_TUNE    100
#define FACTOR_NEWP    1		// Loop Step (um)	#1000
#define FACTOR_TIO     2	   //Loop Step factor with TIO board
#define MAXITERNEWP	   10    // Maximum number of iterations in MoveNewp to reach Goal
#define MAX_STEP	   11

#define LPT1 		   888	 // PARALLEL PORT ADDRESS (PIN 11,17-25 -> GND)
#define STEP_LPT_ON_1  0x01	 // LSB 	-> PIN 2	(Axis1)	
#define STEP_LPT_ON_2  0x08  // LSB + 3	-> PIN 5	(Axis2)
#define STEP_LPT_CW_1  0x02  // LSB + 1	-> PIN 3	(Axis1)
#define STEP_LPT_CW_2  0x10	 // LSB + 4	-> PIN 6	(Axis2)
#define STEP_LPT_AWO_1 ~0x04 // LSB + 2	-> PIN 4	(Axis1)
#define STEP_LPT_AWO_2 ~0x20 // LSB + 5	-> PIN 7	(Axis2)

#define SLEEP_MONO 	   0.002	 // 0.025 Sleep Time for MONO (s)
#define SLEEP_TUNE 	   0.008	 // Sleep Time for TUNE	(s)
#define SLEEP_NEWP     5
#define STEPS_MONO	   1      // Number of Steps Moto for 1 nm  (nanometer)
#define STEPS_TUNE	   8       // Number of Steps Tune for 0.01 mm  (millimeter)	
#define STEPS_NEWP	   "000"   // Number of Steps Newp for 1 mm ("0" = *10 steps)	
#define MAXPOS	   	   10000	 // Maximum number of step or switch positions
#define EXP_STEP	   1.0
#define SLEEP_MIN_MVIS 0.005 //0.010
#define SLEEP_MAX_MVIS 0.020 //0.040
//**#define SLEEP_MIN_MNIR 0.002 //0.010
//**#define SLEEP_MAX_MNIR 0.008 //0.040
/**/#define SLEEP_MIN_MNIR 0.0025 //0.010
/**/#define SLEEP_MAX_MNIR 0.0025 //0.040
#define SLEEP_MIN_TUNE 0.002 //0.002
#define SLEEP_MAX_TUNE 0.002 //0.002
#define SPEED          30  // Newport velocity (mm/s)


struct StepS {
	int Control;
	char  Com;
	char  Axis;
	char  Type;
	char  Step;
	char  Loop;
	char  Dir;
	char Sign;
	char Speed;
	char Mode;
	char Sort;
	char Moving;
	char Started;
	char DiffHome;
	char Lcd;
	char Hold;
	long Actual;
	long Actual_mean_pow;
	long Actual_std;
	long Delta;
	long Home;
	long Min;
	long Max;
	double Factor;
	struct TioS Tio;
	struct MioS Mio;
	struct StandaS Standa;
	double FreqMax;
	double FreqMin;
	double FreqActual;
	double FreqDelta;
	double Freq;
	long Start[MAXPOS];
	long Stop[MAXPOS];
	char  FName[STRLEN];
	char  FPath[STRLEN];
	struct Delay_GateS Delay_Gate;
	struct Standa2S Standa2;
	long StopGoal; // EDO
	};
