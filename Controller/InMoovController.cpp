#include <cnoid/SimpleController>
#include <cnoid/Joystick>

using namespace cnoid;

const double pgain[] = {
    8000.0, 8000.0, 8000.0, 8000.0, 8000.0, 8000.0,
    3000.0, 3000.0, 3000.0, 3000.0, 3000.0, 3000.0, 3000.0, 
    8000.0, 8000.0, 8000.0, 8000.0, 8000.0, 8000.0,
    3000.0, 3000.0, 3000.0, 3000.0, 3000.0, 3000.0, 3000.0, 
    8000.0, 8000.0, 8000.0 };
    
const double dgain[] = {
    100.0, 100.0, 100.0, 100.0, 100.0, 100.0,
    100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0,
    100.0, 100.0, 100.0, 100.0, 100.0, 100.0,
    100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0,
    100.0, 100.0, 100.0 };


class InMoovController : public SimpleController
{ 
    Joystick joystick;
    
    BodyPtr ioBody;
    double dt;
    std::vector<double> qref;
    std::vector<double> qold;

public:
    
    virtual bool initialize(SimpleControllerIO* io)
    {
        ioBody = io->body();
        dt = io->timeStep();
        std::ostream& os = io->os();
        
        for(auto joint : ioBody->joints()){
            io->enableIO(joint);
            qref.push_back(joint->q());
        }
        qold = qref;
        
        if(!joystick.isReady()){
            os << "Joystick is not ready: " << joystick.errorMessage() << std::endl;
        }
        if(joystick.numAxes() < 5){
            os << "The number of the joystick axes is not sufficient for controlling the robot." << std::endl;
        }
        
        return true;
    }

    virtual bool control()
    {
        for(int i=0; i < ioBody->numJoints(); ++i){
            Link* joint = ioBody->joint(i);
            double q = joint->q(); 
            
            joystick.readCurrentState();

            double pos[2];
            for(int i=0; i < 2; ++i){
                pos[i] = joystick.getPosition(i);
                if(fabs(pos[i]) < 0.2){
                    pos[i] = 0.0;
                }
            }                  
            if (i == ioBody->link("LARM_ELBOW")->jointId() || 
                i == ioBody->link("LLEG_KNEE")->jointId()  ||
                i == ioBody->link("LLEG_HIP_P")->jointId()){
                
                q += 0.1 * pos[1] + pos[0];
            }
            if (i == ioBody->link("RARM_ELBOW")->jointId() || 
                i == ioBody->link("RLEG_KNEE")->jointId()  ||
                i == ioBody->link("RLEG_HIP_P")->jointId()){
                
                q -= 0.1 * pos[1] + pos[0];
            }                        
            double dq = (q - qold[i]) / dt;
            double u = (qref[i] - q) * pgain[i] + (0.0 - dq) * dgain[i];
            qold[i] = q;
            joint->u() = u;
        }
             
        return true;
    }
};

CNOID_IMPLEMENT_SIMPLE_CONTROLLER_FACTORY(InMoovController)
