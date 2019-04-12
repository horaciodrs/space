#include "animation.hpp"

namespace Ros{

	void Animation::Begin(void){
		Running = true;
		CurrentFrame = 0;
		FrameCount = w / FrameWidth;
	}

	void Animation::End(void){
		Running = false;
	}

	void Animation::Draw(void){

		if(Running == false){
			return;
		}

		if(CurrentFrame > FrameCount){
			End();
			return;
		}

		Object::Draw(x, y, CurrentFrame * FrameWidth, 0, FrameWidth, h);

		CurrentFrame++;

	}

	Animation::Animation(std::string pId, int pFrameWidth, Application *pApp) : FrameWidth(pFrameWidth), Object(pId, pApp){
		
	}

	Animation::~Animation(){

	}

}