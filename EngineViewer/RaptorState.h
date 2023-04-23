#pragma once
#include <Windows.h>
#include <vector>

class RaptorUI {
public:
	bool Enabled = false;
	DWORD Identifier = 0;
};

RaptorUI GetUIFromIdentifier(const std::vector<RaptorUI>& UIList,DWORD Identifier) {
	for (RaptorUI UI : UIList) {
		if (UI.Identifier == Identifier) {
			return UI;
		}
	}
}