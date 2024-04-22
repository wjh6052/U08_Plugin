#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class TOYPLUGIN_API FButtonCommand : public TCommands<FButtonCommand>
{
public:
	FButtonCommand();
	~FButtonCommand();

public:
	virtual void RegisterCommands() override;

private:
	void OnClicked_LoadMesh();
	void OnClicked_OpenViewer();

public:
	TSharedPtr<FUICommandInfo> LoadMeshID;
	TSharedPtr<FUICommandInfo> OpenViewerID;

	TSharedPtr<FUICommandList> Command;
};
