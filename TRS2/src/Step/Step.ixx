export module Step;

import <string>;
import <vector>;
import <memory>;
import <fstream>;
import <sstream>;
import <iostream>;
import <cmath>;
import <algorithm>;

import Const;
import Globals;

export class Step {
public:
    // Variables (from original Step.h)
    long actual{};
    int  iS{};
    std::vector<long> start;
    std::vector<long> stop;
    bool diffHome{};
    bool moving{};
    long home{};
    long delta{};
    double freqActual{};
    int dir{};

    std::string Type;
    int         Com{};
    int         Axis{};
    std::string Mode;
    std::string Sign;
    int         Loop{};     // 0-based loop index
    bool        Hold{};
    bool        Lcd{};
    std::string FName;
    long        Min{};
    long        Max{};
    long        FreqMin{};
    long        FreqMax{};
    long        FreqDelta{};
    long        Freq{};
    double      Factor{1.0};
    bool        Sort{};

    // Factory (defined in StepFactory.ixx to avoid module cycles)
    static std::unique_ptr<Step> createStep(int iS);

    virtual ~Step() = default;

    // High-level ops
    void moveStep(long* Actual, long Goal, bool Wait, bool Status);
    void setVel(int Step, double Freq);
    void initPos(void);
    void initStep(int Step);
    long calcGoal(int Step);

    // Device-specific primitive
    virtual void moveStepDev(long goal) = 0;
};

// ------------------------------
// Implementations
// ------------------------------

void Step::initPos(void){
    bool sethome = false;
    int numread = 0;
    int loop=this->Loop;
    long num=P.Loop[loop].Num;

    diffHome=false;
    std::cout << "Initializing Array Position for Stepper # " << static_cast<int>(iS + 1) << std::endl;
    this->start.resize(num);

    if(P.Step[iS].FName.empty()){
        home = static_cast<long>(P.Loop[loop].Home*this->Factor);
        for(long il=0; il<num; ++il){
            this->start[il] = static_cast<long>(this->Factor * (P.Loop[loop].First + il*P.Loop[loop].Delta));
        }
    } else {
        std::ifstream fpos(P.Step[iS].FPath);
        if (!fpos.is_open()) {
            std::cerr << "Error: unable to open file " << P.Step[iS].FPath << std::endl;
            return;
        }

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

            if(label==P.Loop[loop].Home) {
                if(!sethome){
                    this->home = static_cast<long>(value*P.Step[iS].Factor + 0.5);
                    sethome = true;
                } else {
                    this->diffHome=true;
                }
            }

            for(long il=0; il<num; ++il){
                if(label==(P.Loop[loop].First+il*P.Loop[loop].Delta)){
                    long pos = static_cast<long>(value*P.Step[this->iS].Factor + 0.5);
                    this->start[il] = pos;
                    numread++;
                }
            }
        }

        fpos.close();
        if (numread < (num - 1)) {
            std::cerr << "Error: Not Enough Points on File Pos" << std::endl;
        }
    }

    actual = home;
    std::cout << "Home = " << static_cast<int>(home) << std::endl;
    std::cout << "PASSED" << std::endl;
}

void Step::initStep(int Step){
    moving=false;

    if(P.Step[Step].Mode=="CONT") {
        const double freq = std::fabs(P.Step[Step].Delta/(P.Spc.TimeM*P.Loop[P.Step[Step].Loop].Num));
        setVel(Step, freq);
    } else {
        setVel(Step, P.Step[Step].Freq);
    }
}

void Step::setVel(int Step, double Freq){
    Freq = std::fabs(Freq);
    P.Step[Step].FreqActual = Freq;
}

void Step::moveStep(long *Actual,long Goal,bool Wait,bool /*Status*/){
    if (*Actual==Goal) return;
    moving=true;
    const long delta=Goal-*Actual;
    dir=(delta>0?1:-1);
    Goal=(dir>0?std::min(Goal,Max):std::max(Goal,Min));

    moveStepDev(Goal);

    P.Spc.Trash=true;

    if(Wait) return;

    moving=false;
}

long Step::calcGoal(int /*Step*/){
    const int  loop  = this->Loop;
    const long index = P.Loop[loop].Actual;
    return this->start[index];
}
