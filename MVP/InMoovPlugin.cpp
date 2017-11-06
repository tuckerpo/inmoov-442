/* Pull in cnoid functionality suite */
#include <cnoid/Plugin>
#include <cnoid/ItemTreeView>
#include <cnoid/BodyItem>
#include <cnoid/ToolBar>
#include <cnoid/SimpleController>
#include <cnoid/MenuManager>
#include <cnoid/MessageView>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>

/* Begin namespace(s) to not have to fully qualify every line of code */
using namespace cnoid;
using namespace std;

/* Preprocessor macro for defining a weighted constant */
#define GRAVITY 9.8

/* define our MVP logic class, declare plugin function */
class InMoovPlugin : public Plugin
{
  public:
	/* Boolean for LEGS walk method */
	bool stepDone;
	/* Boolean for SR1 swingLegs method */
	bool leftLeg;
	/* Mode for SR1 disco method */
	int discoMode = 0;
	/* ADD BOOLEANS/VARIABLES HERE FOR NEW METHODS */



	InMoovPlugin() : Plugin("InMoov Bipedal Kinematics")
	{
		/* define that Body files will be implemented */
		require("Body");
	}

	virtual bool initialize()
	{
		ToolBar* TB = new ToolBar("InMoov Kinematics");
		/* From here, add buttons and functionality to the TB.
		ToolBar class has member functions for adding buttons
		and defining how the joint sliders react when clicked.
		It is a self-bound function. Look around at the other
		predefined functions for guidance. */

		/* SR1 Model Buttons */
		leftLeg = true;
		TB->addButton("SR1 Walk")
			->sigClicked()
			.connect(bind(&InMoovPlugin::swingLegs, this, 0.04));
		TB->addButton("SR1 RotateRLEG")
			->sigClicked()
			.connect(bind(&InMoovPlugin::changeOrientationR, this, 0.04));
		TB->addButton("SR1 RotateLLEG")
			->sigClicked()
			.connect(bind(&InMoovPlugin::changeOrientationL, this, 0.04));
		TB->addButton("SR1 Disco")
			->sigClicked()
			.connect(bind(&InMoovPlugin::discoDance, this, 0.04));
		/* SR1 Model Buttons */


		/* Separator button in plugin gui */
		TB->addButton("          ")
			->sigClicked()
			.connect(bind(&InMoovPlugin::separate, this));


		/* LEGS Model Buttons */
		// Initialize stepDone boolean
		stepDone = true;
		// Adds Walk button to toolbar
		TB->addButton("LEGS Walk")
			->sigClicked()
			.connect(bind(&InMoovPlugin::walk, this));
		// Adds Reset button to toolbar
		TB->addButton("LEGS Reset")
			->sigClicked()
			.connect(bind(&InMoovPlugin::reset, this));
		/* LEGS Model Buttons */


		/* Separator button in plugin gui */
		TB->addButton("          ")->sigClicked().connect(bind(&InMoovPlugin::separate, this));


		/* >>>>> TEST MODEL BUTTONS HERE <<<<< */





		/* >>>>> TEST MODEL BUTTONS HERE <<<<< */


		/* Note that this virtual function must return true.
		It may be a good idea to use this restriction as a
		testing parameter */
    		addToolBar(TB);
		return true;
	}

	/* SR1 Walk Function */
 	void swingLegs(double dq)
    	{
		ItemList<BodyItem> bodyItems =
		ItemTreeView::mainInstance()->selectedItems<BodyItem>();

		for(size_t i=0; i < bodyItems.size(); ++i)
		{
	    		BodyPtr body = bodyItems[i]->body();

			// Checks if SR1 model
			if(body->numJoints() != 29)
			{
				MessageView::instance()->putln("Incorrect model! Please select the SR1 model.");
			}
			else
			{
				// Get joints from model
	    		    	int lleg_hip_p = body->link("LLEG_HIP_P")->jointId();
	    		    	int rleg_hip_p = body->link("RLEG_HIP_P")->jointId();
	    		    	int lleg_knee = body->link("LLEG_KNEE")->jointId();
	    		    	int rleg_knee = body->link("RLEG_KNEE")->jointId();
		    		int rarm_shoulder_p = body->link("RARM_SHOULDER_P")->jointId();
		    		int larm_shoulder_p = body->link("LARM_SHOULDER_P")->jointId();

	    		    	if(body->joint(lleg_hip_p)->q() < -1) {
	    		        	this->leftLeg = true;
	    		    	} else if(body->joint(lleg_hip_p)->q() > 1) {
	    		        	this->leftLeg = false;
	    		    	}

	    		    	if(this->leftLeg) {
	    		        	body->joint(lleg_hip_p)->q() += dq;
	    		        	if(body->joint(lleg_knee)->q() > 0)
	    		            		body->joint(lleg_knee)->q() -= dq;
	    		        		body->joint(rleg_hip_p)->q() -= dq;
	    		        		body->joint(rleg_knee)->q() += dq;
		        			body->joint(rarm_shoulder_p)->q() += dq;
		        			body->joint(larm_shoulder_p)->q() -= dq;
	    		    	} else {
	    		        	body->joint(lleg_hip_p)->q() -= dq;
	    		        	body->joint(lleg_knee)->q() += dq;
	    		        	body->joint(rleg_hip_p)->q() += dq;
	    		        	if(body->joint(rleg_knee)->q() > 0)
	    		            		body->joint(rleg_knee)->q() -= dq;
		        			body->joint(rarm_shoulder_p)->q() -= dq;
		        			body->joint(larm_shoulder_p)->q() += dq;

	    		    	}
	    		    	bodyItems[i]->notifyKinematicStateChange(true);
			}

    		}
    	}

	/* SR1 Rotate Left Leg */
	void changeOrientationL(double dq)
	{
		ItemList<BodyItem> bodyItems =
		ItemTreeView::mainInstance()->selectedItems<BodyItem>();
		for(size_t i=0; i < bodyItems.size(); ++i){
		    	BodyPtr body = bodyItems[i]->body();
			if(body->numJoints() != 29)
			{
				MessageView::instance()->putln("Incorrect model! Please select the SR1 model.");
			}
			else
			{
				int LLEG_HIP_Y = body->link("LLEG_HIP_Y")->jointId();
				int RLEG_HIP_Y = body->link("RLEG_HIP_Y")->jointId();
				body->joint(LLEG_HIP_Y)->q() += dq;
   				bodyItems[i]->notifyKinematicStateChange(true);
			}
		}

	}

	/* SR1 Rotate Right Leg */
	void changeOrientationR(double dq)
	{
		ItemList<BodyItem> bodyItems =
		ItemTreeView::mainInstance()->selectedItems<BodyItem>();
		for(size_t i=0; i < bodyItems.size(); ++i){
			BodyPtr body = bodyItems[i]->body();
			if(body->numJoints() != 29)
			{
				MessageView::instance()->putln("Incorrect model! Please select the SR1 model.");
			}
			else
			{
				int LLEG_HIP_Y = body->link("LLEG_HIP_Y")->jointId();
				int RLEG_HIP_Y = body->link("RLEG_HIP_Y")->jointId();
				body->joint(RLEG_HIP_Y)->q() += dq;
   				bodyItems[i]->notifyKinematicStateChange(true);
			}
		}
	}

	// arthurdier -- collaboration 
	void discoDance(double dq)
	{

		ItemList<BodyItem> bodyItems =
		ItemTreeView::mainInstance()->selectedItems<BodyItem>();

		for(size_t i=0; i < bodyItems.size(); ++i)
		{
	    		BodyPtr body = bodyItems[i]->body();

			// Checks if SR1 model
			if(body->numJoints() != 29)
			{
				MessageView::instance()->putln("Incorrect model! Please select the SR1 model.");
			}
			else
			{
				// Get joints from model
	    		int rarm_shoulder_p = body->link("RARM_SHOULDER_P")->jointId();
	    		int larm_shoulder_p = body->link("LARM_SHOULDER_P")->jointId();
	    		int rarm_shoulder_y = body->link("RARM_SHOULDER_Y")->jointId();
	    		int larm_shoulder_y = body->link("LARM_SHOULDER_Y")->jointId();
	    		int rarm_elbow 		= body->link("RARM_ELBOW")	   ->jointId();
				int larm_elbow 		= body->link("LARM_ELBOW")	   ->jointId();

				// cross hands over 
		    	if(discoMode <= 25){
		    		body->joint(rarm_elbow)->q() 	  -= dq;
		    		body->joint(larm_elbow)->q() 	  -= dq;
        			body->joint(rarm_shoulder_y)->q() += dq;
        			body->joint(larm_shoulder_y)->q() -= dq;
        			discoMode += 1;
		    	}
		    	if(discoMode > 25 && discoMode < 90){
		    		body->joint(larm_shoulder_p)->q() -= dq;
		    		body->joint(rarm_shoulder_p)->q() -= dq;
		    		discoMode += 1;
		    	}
		    	if(discoMode >= 90 && discoMode < 155){
		    		if(discoMode > 103 && discoMode%2 == 0){
			    		body->joint(rarm_elbow)->q() 	  += dq;
			    		body->joint(larm_elbow)->q() 	  += dq;
	        			body->joint(rarm_shoulder_y)->q() -= dq;
	        			body->joint(larm_shoulder_y)->q() += dq;
		    		}
		    		body->joint(larm_shoulder_p)->q() += dq;
		    		body->joint(rarm_shoulder_p)->q() += dq;
		    		discoMode += 1;
		    	}
		    	if(discoMode == 155) discoMode = 0;

		    	bodyItems[i]->notifyKinematicStateChange(true);
			}

    	}
	}



	/* LEGS Walk Function */
	void walk()
    	{
		/* vector of type BodyItem */
		ItemList<BodyItem> bodyItems = ItemTreeView::mainInstance()->selectedItems<BodyItem>();
		double dq = 0.04;

		/* size_t is defined as unsigned long long - to be used for large iterative values > 0 */
		/* for loop: for each body item, assign a pointer to it, same with joints internal loop */
		for(size_t i=0; i < bodyItems.size(); ++i)
		{
			/* Obtain joint ids from model */
			BodyPtr body = bodyItems[i]->body();

			// Checks if LEGS model
			if(body->numJoints() != 6)
			{
				MessageView::instance()->putln("Incorrect model! Please select the LEGS model.");
			}
			else
			{
				int hip_right = body->link("HIP_RIGHT")->jointId();
				int hip_left = body->link("HIP_LEFT")->jointId();
				int knee_right = body->link("KNEE_RIGHT")->jointId();
				int knee_left = body->link("KNEE_LEFT")->jointId();
				int ankle_right = body->link("ANKLE_RIGHT")->jointId();
				int ankle_left = body->link("ANKLE_LEFT")->jointId();

				/* Left leg moves forward first */
				if(this->stepDone)
				{
					/* When left leg back and right leg forward */
					if(body->joint(hip_left)->q() < -0.01)
					{
						// Left leg moves forward
						body->joint(hip_left)->q() += dq;
						if(body->joint(hip_left)->q() > -0.19)
						{
							body->joint(knee_left)->q() += dq * 2.5;
							if(body->joint(hip_left)->q() > -0.07)
							{
								body->joint(ankle_left)->q() += dq / 2;
							}
						}

						// Right leg moves back
						if(body->joint(hip_left)->q() < -0.19)
						{
							body->joint(knee_right)->q() -= dq * 2.5;
						}
						else if(body->joint(hip_left)->q() >= -0.19 && body->joint(knee_right)->q() < -0.01)
						{
							body->joint(knee_right)->q() += dq * 2.5;
						}

						if(body->joint(hip_right)->q() > 0.17)
						{
							body->joint(hip_right)->q() -= dq / 0.625;
						}
						else if(body->joint(hip_right)->q() <= 0.17)
						{
							body->joint(hip_right)->q() -= dq;
						}
					
					}
					/* When both legs in neutral/straight position */			
					else if(body->joint(hip_left)->q() >= -0.01 && body->joint(hip_left)->q() < 0.15)
					{
						// Left leg continues to move forward
						body->joint(hip_left)->q() += dq;
						if(body->joint(knee_left)->q() > -0.39)
						{
							body->joint(knee_left)->q() -= dq * 2.5;
						}

						// Right leg continues to move back
						body->joint(hip_right)->q() -= dq;
						body->joint(ankle_right)->q() += dq;
					}
					/* Left leg halfway forwards and right leg halfway backwards */
					else if(body->joint(hip_left)->q() >= 0.15 && body->joint(hip_left)->q() < 0.47)
					{
						// Right leg moving fully backwards
						if(body->joint(hip_left)->q() < 0.35)
						{
							body->joint(knee_right)->q() -= dq * 2.5;
							body->joint(ankle_right)->q() -= dq;
						}
						body->joint(hip_right)->q() -= dq * 0.625;

						// Left leg extending fully forwards
						if(body->joint(hip_left)->q() >= 0.3)
						{
							body->joint(knee_left)->q() += dq * 2.5;
						}
						body->joint(hip_left)->q() += dq;
					}
					/* Left leg front and right leg back complete.
					   Switching to right leg front and left leg back. */
					else if(body->joint(hip_left)->q() >= 0.47)
					{
						this->stepDone = false;
					}
				}

				else
				{
					/* Left leg starts moving backwards and right leg starts moving forward */
					if(body->joint(hip_left)->q() <= 0.49 && body->joint(hip_left)->q() >= 0.33)
					{
						// Left leg moves backward
						if(body->joint(knee_left)->q() > -0.4)
						{
							body->joint(knee_left)->q() -= dq * 2.5;
						}
						body->joint(hip_left)->q() -= dq;

						// Right leg moves forward
						body->joint(hip_right)->q() += dq;
					}
					/* Moving both legs back to neutral/standing position */
					else if(body->joint(hip_left)->q() < 0.33 && body->joint(hip_left)->q() >= 0.01)
					{
						// Left leg moves backward
						body->joint(knee_left)->q() += dq * 1.25;
						body->joint(hip_left)->q() -= dq;

						// Right leg moves forward
						body->joint(hip_right)->q() += dq * 0.625;
						if(body->joint(hip_left)->q() < 0.29 && body->joint(hip_left)->q() > 0.11)
						{
							body->joint(knee_right)->q() += dq * 2.5;
							if(body->joint(hip_left)->q() < 0.19)
							{
								body->joint(ankle_right)->q() += dq / 2;
							}
						}
					}
					/* Both legs back to neutral/standing position.
					   Begin moving left leg further back and right leg forwards*/
					else if(body->joint(hip_left)->q() < 0.01 && body->joint(hip_left)->q() >= -0.35)
					{
						// Left leg steps backward
						body->joint(hip_left)->q() -= dq;
						body->joint(ankle_left)->q() += dq;
						if(body->joint(hip_left)->q() <= -0.19)
						{
							body->joint(knee_left)->q() -= dq * 2.5;
							body->joint(ankle_left)->q() -= dq * 2;
						}

						// Right leg extends forward
						if(body->joint(knee_right)->q() > -0.39 && body->joint(hip_right)->q() < 0.25)
						{
							body->joint(knee_right)->q() -= dq * 2.5;
						}
						if(body->joint(hip_right)->q() >= 0.25)
						{
							body->joint(knee_right)->q() += dq * 2.5;
						}
						body->joint(hip_right)->q() += dq * 1.33333;
					}
					/* Right leg front and left leg back complete.
					   Switching back to right leg back and left leg front. */
					else if(body->joint(hip_left)->q() < -0.35)
					{
						this->stepDone = true;
					}
				}

				/* Update model's joint positions */
				bodyItems[i]->notifyKinematicStateChange(true);
			}
		}
    	}

	/* Resets LEGS model position back to default */
	void reset()
    	{
		this->stepDone = true;

		ItemList<BodyItem> bodyItems = ItemTreeView::mainInstance()->selectedItems<BodyItem>();
		for(size_t i=0; i < bodyItems.size(); ++i)
		{
			BodyPtr body = bodyItems[i]->body();
			if(body->numJoints() != 6)
			{
				MessageView::instance()->putln("Incorrect model! Please select the LEGS model.");
			}
			else
			{
				int hip_right = body->link("HIP_RIGHT")->jointId();
				int hip_left = body->link("HIP_LEFT")->jointId();
				int knee_right = body->link("KNEE_RIGHT")->jointId();
				int knee_left = body->link("KNEE_LEFT")->jointId();
				int ankle_right = body->link("ANKLE_RIGHT")->jointId();
				int ankle_left = body->link("ANKLE_LEFT")->jointId();

				body->joint(hip_right)->q() = 0;
				body->joint(hip_left)->q() = 0;
				body->joint(knee_right)->q() = 0;
				body->joint(knee_left)->q() = 0;
				body->joint(ankle_right)->q() = 0;
				body->joint(ankle_left)->q() = 0;

				bodyItems[i]->notifyKinematicStateChange(true);
			}
		}

	}

	/* Blank function / Used to separate buttons on toolbar */
	void separate()
    	{
	}



/* >>> TEST MODEL FEATURES HERE <<< */





/* >>> TEST MODEL FEATURES HERE <<< */



};

CNOID_IMPLEMENT_PLUGIN_ENTRY(InMoovPlugin)
