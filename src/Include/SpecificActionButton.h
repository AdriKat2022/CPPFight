#pragma once

#include "Button.h"
#include "Action.h"

class SpecificActionButton : public Button {

public:
	void SelectAction();


private:
	Action m_action;

};