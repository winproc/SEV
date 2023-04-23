#pragma once
#include <Windows.h>
#include <vector>

class RaptorUI {
public:
	bool Enabled;
	int Stage;
	DWORD Identifier;
	HWND WindowHandle;

	RaptorUI() {
		this->Enabled = false;
		this->Identifier = 0;
		this->Stage = 0;
		this->WindowHandle = NULL;
	}
};

int GetUIFromIdentifier(const std::vector<RaptorUI>& UIList,DWORD Identifier) {
	for (int i = 0; i < UIList.size(); i++) {
		if (UIList[i].Identifier == Identifier) {
			return i;
		}
	}
	return -1;
}