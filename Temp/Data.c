// TYPE OF DATA
// USE long for TimeHarp, Varro, Silena, USE short for all others SPC boards. NEW!!! unsigned short should work for Spcm too
#define T_DATA unsigned long
#define T_HEAD struct sHeader2
#define T_SUB struct sSubHeader1






struct DataS {
	T_HEAD Head;		// D.Head
	T_SUB **Sub;		// D.Sub[P.Frame.Num][P.Num.Page]
	T_DATA ***Data;		// D.Data[P.Frame.Num][P.Num.Page][P.Num.Chann] 
	T_DATA **Osc;		// D.Osc[P.Num.Board*P.Num.Det][P.Num.Chann] 
	T_DATA **Buffer;	// D.Buffer[P.Num.Board][P.Num.Det*P.Num.Chann] 
	T_DATA **Bank;		// D.Bank[P.Num.Board][SPC_BANK_DIM] or D.Bank[P.Num.Board][MAX FIFO MHARP] // not a problem: there is a calloc later
	T_DATA *Curve;		// D.Curve[P.Num.Chann] 
	T_DATA *Last;		// D.Last[P.Num.Chann]
	unsigned short *BusSpcm; // D.BusSpcm[P.Num.Det*P.Num.Chann] ONLY FOR SPCM
	SC1000_TYPE ***BufferTDC;
	};







/* INITIALIZE MEMORY */
void InitMem(void){
	SetCtrlVal (hDisplay, DISPLAY_MESSAGE, "Initializing Memory ... ");
	
	// For all
	D.Osc=DAlloc2D(P.Num.Board*P.Num.Det,P.Chann.Num); 
	D.Buffer=DAlloc2D(P.Num.Board,P.Num.Det*P.Chann.Num); 
	D.BusSpcm = calloc (P.Num.Det*P.Chann.Num, sizeof(unsigned short));
	if(P.Spc.Subtract) D.Last=DAlloc1D(P.Chann.Num); 
	
	// Just for Meas
	if(P.Contest.Run!=CONTEST_MEAS){ Passed(); return;}
	if(P.Moxy.Moxy) D.Bank=DAlloc2D(P.Num.Board,SPC_BANK_DIM); 
	if(P.Flow.Spcm) D.Bank=DAlloc2D(P.Num.Board,SPC_BANK_DIM); 
	if(P.Info.SubHeader) D.Sub=SAlloc2D(P.Frame.Num,P.Num.Page);
	D.Data=DAlloc3D(P.Frame.Num,P.Num.Page,P.Chann.Num);
	
	Passed();
	}


/* CLOSE MEMORY */
void CloseMem(void){
	DFree2D(D.Osc,P.Num.Board*P.Num.Det); 
	DFree2D(D.Buffer,P.Num.Board); 
	free(D.BusSpcm);
	if(P.Spc.Subtract) DFree1D(D.Last); 
	if(P.Contest.Run!=CONTEST_MEAS) return;
	if(P.Moxy.Moxy) DFree2D(D.Bank,P.Num.Board); 
	if(P.Flow.Spcm) DFree2D(D.Bank,P.Num.Board); 
	if(P.Info.SubHeader) SFree2D(D.Sub,P.Frame.Num);
	DFree3D(D.Data,P.Frame.Num,P.Num.Page); 
}
