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

    // Factory (defined in StepFactory.ixx to avoid module cycles)
    static std::unique_ptr<Step> createStep(int iS);

    virtual ~Step() = default;

    // High-level ops
    void moveStep(long* Actual, long Goal, bool Wait, bool Status);
    void setVel(double Freq);
    void initPos(void);
    void initStep();
    long calcGoal();

    // Device-specific primitive
    virtual void moveStepDev(long goal) = 0;
};

// ------------------------------
// Implementations
// ------------------------------

void Step::initPos(void){
    bool sethome = false;
    int numread = 0;
    int loop= P.Step[iS].Loop;
    long num=P.Loop[loop].Num;

    diffHome=false;
    std::cout << "Initializing Array Position for Stepper # " << static_cast<int>(iS + 1) << std::endl;
    this->start.resize(num);

    if(P.Step[iS].FName.empty()){
        home = static_cast<long>(P.Loop[loop].Home* P.Step[iS].Factor);
        for(long il=0; il<num; ++il){
            this->start[il] = static_cast<long>(P.Step[iS].Factor * (P.Loop[loop].First + il*P.Loop[loop].Delta));
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

void Step::initStep(){
    moving=false;

    if(P.Step[iS].Mode=="CONT") {
        const double freq = std::fabs(P.Step[this->iS].Delta/(P.Spc.TimeM*P.Loop[P.Step[this->iS].Loop].Num));
        setVel(freq);
    } else {
        setVel(P.Step[this->iS].Freq);
    }
}

void Step::setVel(double Freq){
    Freq = std::fabs(Freq);
    P.Step[this->iS].FreqActual = Freq;
}

void Step::moveStep(long *Actual,long Goal,bool Wait,bool /*Status*/){
    if (*Actual==Goal) return;
    moving=true;
    const long delta=Goal-*Actual;
    dir=(delta>0?1:-1);
    Goal=(dir>0?std::min(Goal, P.Step[iS].Max):std::max(Goal, P.Step[iS].Min));

    moveStepDev(Goal);

    P.Spc.Trash=true;

    if(Wait) return;

    moving=false;
}

long Step::calcGoal(){
    const int  loop  = P.Step[iS].Loop;
    const long index = P.Loop[loop].Actual;
    return this->start[index];
}
