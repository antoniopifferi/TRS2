/* ########################   STEPPER CLASS   ######################## */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#include "GenSource/Step.h"
#include "DevSource/MicroStep.h"
#include "DevSource/ArdStep.h"
#include "GenSource/Parm.h"
#include "GenSource/Var.h"

//#include "MonoStep.h"


// Placeholder functions for error handling and success messages
void Failure(const std::string& message) {
    //std::cerr << "Failure: " << message << std::endl;
    std::cout << "Failure: " << message << std::endl;
}

void Passed() {
    std::cout << "Operation Passed" << std::endl;
}

std::unique_ptr<Step> Step::createStep(int iS) {
    std::unique_ptr<Step> step = nullptr;
    auto type = P.Step[iS].Type;

    if (type == "MICRO") {
        step = std::make_unique<MicroStep>(iS);
    } else if (type == "ARD") {
        step = std::make_unique<ArdStep>(iS);
    }

    if(step){
        step->Type=P.Step[iS].Type;
        step->Com=P.Step[iS].Com;
        step->Axis=P.Step[iS].Axis;
        step->Mode=P.Step[iS].Mode;
        step->Sign=P.Step[iS].Sign;
        step->Loop=P.Step[iS].Loop-1;
        step->Hold=P.Step[iS].Hold;
        step->Lcd=P.Step[iS].Lcd;
        step->FName=P.Step[iS].FName;
        step->Min=P.Step[iS].Min;
        step->Max=P.Step[iS].Max;
        step->FreqMin=P.Step[iS].FreqMin;
        step->FreqMax=P.Step[iS].FreqMax;
        step->FreqDelta=P.Step[iS].FreqDelta;
        step->Freq=P.Step[iS].Freq;
        step->Factor=P.Step[iS].Factor;
        step->Sort=P.Step[iS].Sort;
        step->iS=iS;
    }

    if(step)
        step->initPos();

    return step;
}

//Step* Step::createStep(int iS) {
//    auto type=P.Step[iS].Type;
//    if (type == "MICRO")
//        return new MicroStep(iS);
//    else if (type == "ARD")
//        return new ArdStep(iS);
//    else
//        return nullptr; // or throw an exception for invalid type
//}

void Step::initPos(void){
    bool sethome = false;
    int numread = 0;
    int loop=this->Loop;
    long num=P.Loop[loop].Num;

    diffHome=false;
    //**if(P.Loop[P.Step[Step].Loop].Cont != CONT_NONE) num+=1;
    std::cout << "Initializing Array Position for Stepper # " << static_cast<int>(iS + 1) << std::endl;
    this->start.resize(num);
//    this->stop.resize(num);

    // if FName empty, then fill start/stop with loop
    if(P.Step[iS].FName.empty()){
        home = (long)(P.Loop[loop].Home*this->Factor);
        for(int il=0;il<num;il++){
            this->start[il]=(long)(this->Factor*(P.Loop[loop].First+il*P.Loop[loop].Delta));
//            this->stop[il]=(long)(P.Step[iS].Factor*(P.Loop[loop].First+(il+1)*P.Loop[loop].Delta));
        }
    }

    // if FName, then fill the labels/values vector
    else {
        std::ifstream fpos(P.Step[iS].FPath); // Open file for reading
        if (!fpos.is_open()) {
            std::cerr << "Error: unable to open file " << P.Step[iS].FPath << std::endl;
            return;
        }

        // Scan all lines at for each line get label/value pair
        std::string line;
        while (std::getline(fpos, line)) {
            std::istringstream iss(line);
            long label;
            double value;
            char delimiter;

            if (!(iss >> label >> delimiter >> value)) {
                std::cerr << "Error: Unable to parse line: " << line << std::endl;
                continue;
            }

            // if home, then set home
            if(label==P.Loop[loop].Home)
                if(!sethome){
                    this->home = (long)(value*P.Step[iS].Factor+0.5);
                    sethome = true;
                }
                else
                    this->diffHome=true;

            // assign labels/values
            for(int il=0;il<num;il++){
                if(label==(P.Loop[loop].First+il*P.Loop[loop].Delta)){
                    long pos=(long)(value*P.Step[this->iS].Factor+0.5);
                    this->start[il]=pos;
                    numread++;
                    //if(il>0) this->stop[il-1]=pos; // stop is operative after the first
                    //if(il==num-1) this->stop[il-1]=
                }
            }
        }
        fpos.close();
        if(numread<(num-1))
            std::cerr << "Error: Not Enough Points on File Pos" << std::endl;
    }
    //this->delta=this->stop[num-1]-this->start[0];
    this->actual=this->home;
    std::cout << "Home = " << static_cast<int>(this->home) << std::endl;
    std::cout << "PASSED" << std::endl;
}

/* MOVE STEPPER MOTOR */
void Step::moveStep(long *Actual,long Goal,bool Wait,bool Status){
    long delta;
    if (*Actual==Goal) return;
    moving=true;
    delta=Goal-*Actual;
    dir=(delta>0?1:-1);
    Goal=(dir>0?std::min(Goal,Max):std::max(Goal,Min));
    bool on=false;

    moveStepDev(Goal);
    P.Spc.Trash=TRUE;
    if(Wait) return;
    //if(Status) SetCtrlVal (hDisplay, P.Step[Step].Control, (P.Step[Step].Actual/(1.0*P.Step[Step].Factor)));//TODO: Check for TRIM
    moving=false;
    if(Status){
        for(int iS=0;iS<MAX_STEP;iS++)
            if(Steps[iS])
                on |= Steps[iS]->moving;
        //        if(!on) SetCtrlVal (hDisplay, DISPLAY_MOVE, OFF);
    }
}


///* START CONTINUOUS MOVEMENT */
//void StartCont(char Step, char Status){
//    double freq;
//    long delta,stopgoal;
//    int num_meas=1;
//    int imeas,il;
//    int loop = P.Step[Step].Loop;
//    int iloop = P.Loop[loop].Actual;
//    long start[MAXPOS];
//    long stop[MAXPOS];

//    char invert=(P.Loop[loop].Invert)&&REMINDER(P.Loop[loop-1].Actual,2);
//    for(il=P.Step[Step].Loop+1;il<MAX_LOOP;il++) num_meas*=P.Loop[il].Num;

//    for(il=0;il<P.Loop[loop].Num;il++){
//        stop[il]=(invert?P.Step[Step].Start[P.Loop[loop].Num-1-il]:P.Step[Step].Stop[il]);
//        start[il]=(invert?P.Step[Step].Stop[P.Loop[loop].Num-1-il]:P.Step[Step].Start[il]);
//    }

//    switch (P.Step[Step].Loop) {		// CHECK: MAYBE THERE IS AN ERROR IN THE PRODUCT OF .NUM
//    case LOOP5: imeas=1; break;
//    case LOOP4: imeas=1+P.Loop[LOOP5].Actual; break;
//    case LOOP3: imeas=1+P.Loop[LOOP5].Actual+P.Loop[LOOP4].Actual*P.Loop[LOOP5].Num; break;
//    case LOOP2: imeas=1+P.Loop[LOOP5].Actual+P.Loop[LOOP4].Actual*P.Loop[LOOP5].Num+P.Loop[LOOP3].Actual*P.Loop[LOOP4].Num*P.Loop[LOOP5].Num; break;
//    case LOOP1: imeas=1+P.Loop[LOOP5].Actual+P.Loop[LOOP4].Actual*P.Loop[LOOP5].Num+P.Loop[LOOP3].Actual*P.Loop[LOOP4].Num*P.Loop[LOOP5].Num+P.Loop[LOOP2].Actual*P.Loop[LOOP3].Num*P.Loop[LOOP4].Num*P.Loop[LOOP5].Num; break;
//    }
//    switch (P.Loop[P.Step[Step].Loop].Cont) {
//    case CONT_STEP:
//        freq=fabs(stop[iloop]-start[iloop])/(num_meas*P.Spc.TimeM);
//        stopgoal=stop[iloop];
//        break;
//    case CONT_RANGE:
//        freq=fabs(P.Step[Step].Delta)/(num_meas*P.Spc.TimeM*P.Loop[P.Step[Step].Loop].Num);
//        stopgoal=stop[P.Loop[P.Step[Step].Loop].Num-1];
//        break;
//    }
//    if(freq!=P.Step[Step].FreqActual) SetVel(Step,freq);
//    if((P.Wait.Type==WAIT_POS)&&(P.Wait.Step==Step)){
//        delta=stop[iloop]-start[iloop];
//        P.Wait.Pos=start[iloop]+(imeas*delta/num_meas);
//    }

//    MoveStep(&P.Step[Step].Actual,stopgoal,Step,FALSE,Status);
//}


///* WAIT CONTINUOUS MOVEMENT */
//void WaitCont(char Step, char Status){
//    int il;
//    int loop = P.Step[Step].Loop;
//    int iloop = P.Loop[loop].Actual;
//    long start[MAXPOS];
//    long stop[MAXPOS];
//    long stopgoal;

//    char invert=(P.Loop[loop].Invert)&&REMINDER(P.Loop[loop-1].Actual,2);
//    for(il=0;il<P.Loop[loop].Num;il++){
//        stop[il]=(invert?P.Step[Step].Start[P.Loop[loop].Num-1-il]:P.Step[Step].Stop[il]);
//        start[il]=(invert?P.Step[Step].Stop[P.Loop[loop].Num-1-il]:P.Step[Step].Start[il]);
//    }
//    switch (P.Loop[P.Step[Step].Loop].Cont) {
//    case CONT_STEP:
//        stopgoal=stop[iloop];
//        break;
//    case CONT_RANGE:
//        stopgoal=stop[P.Loop[P.Step[Step].Loop].Num-1];
//        break;
//    }
//    WaitStep(&P.Step[Step].Actual,stopgoal,Step,Status);
//}


/* INITIALIZE STEPPER MOTOR */
void Step::initStep(int Step){
    //++ P.Step[Step].Moving = FALSE;
    moving=false;
//    switch(P.Step[Step].Type){
//    case LPT: InitLpt(); break;
//    case NEWP: InitNewp(P.Step[Step].Speed,P.Step[Step].Axis,Step); break;
//    case MM4005: InitNewp4005(P.Step[Step].Speed,P.Step[Step].Axis,Step); break; //floriano
//    case TIO:  InitTio(P.Step[Step].Axis,Step); break;
//    case MIO:  InitMio(P.Step[Step].Axis,Step); break;
//    case MICRO2:
//    case MICRO:  InitMicro(Step); break;
//    case PWM:	InitPwm(Step); break;
//    case MONO:	InitMono(Step); break;
//    case MONO_TCP:	InitMonoTcp(Step); break;
//    case PI1:	InitPi(Step); break;
//    case FPM:	InitFpm(Step); break;
//    case DELAYER:	InitDelayer(Step); break;
//    case DELAYER_GATE: InitDelayerGate(Step); break;
//    /*XYZ*/case STANDA: InitStanda(Step); break;
//    case NKT_LAMBDA: InitNKTLambda(Step);break;
//    case NKT_POW:	 InitNKTPow(Step);break;
//    case ESP300:  InitEsp300(Step); break;
//    case LT900:  InitLt900(Step); break;
//    case CHAMALEON:  InitCham(Step); break;
//    case STEP_STANDA2: InitStanda2(Step); break;
//    case ATT_LUCA:	InitAttLuca(Step); break;
//    case BCD_SYNC: InitBcd(0); break;
//    case BCD_PIX: InitBcd(0); break;
//    case DMD_TX: InitDmdTx(Step); break;
//    case ARD_FLOW:
//    case ARD_STEP:  InitArd(Step); break;
//    default:;
//    }
    if(P.Step[Step].Mode=="CONT") setVel(Step,fabs(P.Step[Step].Delta/(P.Spc.TimeM*P.Loop[P.Step[Step].Loop].Num)));
    else setVel(Step, P.Step[Step].Freq);

}


/* CLOSE STEPPER MOTOR */
void CloseStep(char Step){
//    switch(P.Step[Step].Type){
//    case TIO:  CloseTio(P.Step[Step].Axis,Step); break;
//    case MICRO2:
//    case MICRO: CloseMicro(Step); break;
//    case PWM: ClosePwm(Step); break;
//    case MONO: CloseMono(Step); break;
//    case MONO_TCP: CloseMonoTcp(Step); break;
//    case PI1: ClosePi(); break;
//    case FPM: CloseFpm(Step); break;
//    /*XYZ*/case STANDA: CloseStanda(Step); break;
//    case NKT_LAMBDA: CloseNKTLambda(Step);break;
//    case NKT_POW:	 CloseNKTPow(Step);break;
//    case ESP300: CloseEsp300(Step); break;
//    case LT900: CloseLt900(Step); break;
//    case CHAMALEON: CloseCham(Step); break;
//    case STEP_STANDA2: CloseStanda2(Step); break;
//    case ATT_LUCA:	CloseAttLuca(Step); break;
//    case BCD_SYNC:
//    case BCD_PIX: CloseBcd(); break;
//    case DMD_TX: CloseDmdTx(Step); break;
//    case ARD_FLOW:
//    case ARD_STEP: CloseArd(Step); break;
//    default:;
//    }
}


/* SET STEPPER VELOCITY */
void Step::setVel(int Step, double Freq){
    Freq = fabs(Freq);
//    switch(P.Step[Step].Type){
//    case NEWP: SetVelNewp(Freq); break;
//    case MM4005: SetVelNewp4005(Step,Freq); break;
//    case TIO:  SetVelTio(Step,Freq); break;
//    case MICRO2:
//    case MICRO:  SetVelMicro(Step,Freq); break;
//    case PWM:  SetVelPwm(Step,Freq); break;
//    case MONO:  SetVelMono(Step,Freq); break;
//    case MONO_TCP: SetVelMonoTcp(Step,Freq); break;
//    case PI1:  SetVelPi(Freq); break;
//    /*XYZ*/case STANDA: SetVelStanda(Step,Freq); break;
//    case ESP300: SetVelEsp300(Step,Freq); break;
//    case CHAMALEON: SetVelCham(Step,Freq); break;
//    case STEP_STANDA2: SetVelStanda2(Step,Freq); break;
//    case ARD_FLOW:
//    case ARD_STEP:  SetVelArd(Step,Freq); break;
//    default:;
//    }
    P.Step[Step].FreqActual=Freq;
}


/* DEFINE HOME */
void DefineHome(char Step){
//    switch(P.Step[Step].Type){
//    case NEWP: DefineHomeNewp(Step); break;
//    case MM4005: DefineHomeNewp4005(Step); break;
//    case MICRO2:
//    case MICRO: DefineHomeMicro(Step); break;
//    case PWM: DefineHomePwm(Step); break;
//    case MONO: DefineHomeMono(Step); break;
//    case MONO_TCP: DefineHomeMonoTcp(Step); break;
//    case PI1: DefineHomePi(Step); break;
//    /*XYZ*/case STANDA: DefineHomeStanda(Step); break;
//    case ESP300: DefineHomeEsp300(Step); break;
//    case LT900: DefineHomeLt900(Step); break;
//    case CHAMALEON: DefineHomeCham(Step); break;
//    case STEP_STANDA2: DefineHomeStanda2(Step); break;
//    case ATT_LUCA: DefineHomeAttLuca(Step); break;
//    case DMD_TX: DefineHomeDmdTx(Step); break;
//    case ARD_FLOW:
//    case ARD_STEP: DefineHomeArd(Step); break;
//    default:;
//    }
    P.Step[Step].Actual=P.Step[Step].Home;
}

/* INVERT ARRAY INDEX */
void InvertIndex(void){
    //TODO: DA RIVEDERE
}


/* CALCULATE GOAL FOR STEPPER */
long Step::calcGoal(int Step){
    int loop = Steps[Step]->Loop;
    long index = P.Loop[loop].Actual;
    long goal = Steps[Step]->start[index];
    return(goal);
}



/* STOP STEPPER */
void StopStep(char Step){
//    switch (P.Step[Step].Type){
//    case TIO:  StopTio(Step);break;
//    case MICRO2:
//    case MICRO: StopMicro(Step); break;
//    case PWM: StopPwm(Step); break;
//    case PI1: StopPi(); break;
//    case FPM: StopFpm(Step); break;
//    case STANDA: StopStanda(Step); break;
//    case ESP300: StopEsp300(Step); break;
//    case CHAMALEON: StopCham(Step); break;
//    case STEP_STANDA2: StopStanda2(Step); break;
//    case ATT_LUCA: StopAttLuca(Step); break;
//    case DMD_TX: StopDmdTx(Step); break;
//    case ARD_FLOW:
//    case ARD_STEP: StopArd(Step); break;
//    default:;
//    }
}

/* TELL POSITION */
void TellPos(char Step,long *Position){
//    switch(P.Step[Step].Type){
//    case NEWP: TellPosNewp(Step,Position); break;
//    case MM4005: TellPosNewp4005(Step,Position); break;
//    case TIO: TellPosTio(Step,Position); break;
//    case MICRO2:
//    case MICRO: TellPosMicro(Step,Position); break;
//    case PWM: TellPosPwm(Step,Position); break;
//    case MONO: TellPosMono(Step,Position); break;
//    case MONO_TCP: TellPosMonoTcp(Step,Position); break;
//    case PI1: TellPosPi(Step,Position); break;
//    case STANDA: TellPosStanda(Step,Position); break;
//    case ESP300: TellPosEsp300(Step,Position); break;
//    case CHAMALEON: TellPosCham(Step,Position); break;
//    case STEP_STANDA2: TellPosStanda2(Step,Position); break;
//    case ATT_LUCA: TellPosAttLuca(Step,Position); break;
//    case ARD_FLOW:
//    case ARD_STEP: TellPosArd(Step,Position); break;
//    default:;
//    }
}

/* WAIT FOR POSITION */
void WaitPos(char Step,long Goal){
    long pa;
    char is_success, is_timeout, is_first, is_equal;
    long last=P.Step[Step].Actual;
    if(P.Step[Step].Type==STEP_NONE) return;
    is_first=TRUE;
    do{
        TellPos(Step,&pa);
        is_success=((Steps[Step]->dir==1)?(pa>=Goal):(pa<=Goal));
        is_equal=(pa==last);
        if(!is_equal) is_first=TRUE;
        last=pa;
        is_timeout=is_equal;
 /*       if(is_equal&&!is_first){
            auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
            auto tmax=1.0/(P.Step[Step].FreqActual/2.0);
            is_timeout=((t1-t0)>(2*tmax));
        }
        if(is_equal&&is_first){
            auto t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
            is_first=FALSE;
            is_timeout=FALSE;
        }*/
    }
    while((!is_success)&&(!is_timeout));
    //**SetTableCellAttribute (hDisplay,DISPLAY_T_TRIS,MakePoint(COL_TRIS_STEP,Step+1),ATTR_CTRL_VAL,(double)pa);
    //**ProcessDrawEvents ();

    //**P.Step[Step].Actual=pa;  // Corrected for MAMM, check in TRIM
}

/* WAIT FOR END STEPPER */
void WaitStep(long *Actual,long Goal,char Step,char Status){
    //if(!P.Step[Step].Started) return;   // modified to comply with delta==0;
//    switch (P.Step[Step].Type) {
//    case NEWP: /*WaitNewp(Step,Goal);*/ break;
//    case TIO: WaitTio(Step,abs(Goal-*Actual),P.Step[Step].Dir); break;
//    case MICRO2:
//    case MICRO: WaitMicro(Step,Goal); break;
//    //case PWM: WaitPwm(Step,Goal); break;
//    case MONO: WaitMono(Step,Goal); break;
//    case MONO_TCP: WaitMonoTcp(Step,Goal); break;
//    case PI1: WaitPi(Step,Goal); break;
//    //case ADC: WaitAdc(); break;
//    case STANDA: WaitStanda(Step,Goal); break;
//    case ESP300: WaitEsp300(Step,Goal); break;
//    case CHAMALEON: WaitCham(Step,Goal); break;
//    case STEP_STANDA2: WaitStanda2(Step,Goal); break;
//    case ATT_LUCA: WaitAttLuca(Step,Goal); break;
//    case DMD_TX: WaitDmdTx(Step,Goal); break;
//    case ARD_FLOW:
//    case ARD_STEP: WaitArd(Step,Goal); break;
//    default:;
//    }
}


