#include "ButtonCommand.h"
#include "DesktopPlatformModule.h"
#include "Interfaces/IMainFrameModule.h"
#include "Serialization/BufferArchive.h"
#include "DetailPanel/StaticMesh_DetailPanel.h"
#include "LevelEditorViewport.h"
#include "Actors/CMeshActor_Copied.h"
#include "Misc/FileHelper.h"



FButtonCommand::FButtonCommand()
	: TCommands("ButtonCommand", FText::FromString("Button Commands"), NAME_None, FEditorStyle::GetStyleSetName())
{
	Command = MakeShareable(new FUICommandList());
}

FButtonCommand::~FButtonCommand()
{
	if (Command.IsValid())
		Command.Reset();
}

void FButtonCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(LoadMeshID, "LoadMesh", "Load Mesh Data", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenViewerID, "OpenViewer", "Open Asset Viewer", EUserInterfaceActionType::Button, FInputChord());
#undef  LOCTEXT_NAMESPACE

	Command->MapAction(LoadMeshID, FExecuteAction::CreateRaw(this, &FButtonCommand::OnClicked_LoadMesh));
	Command->MapAction(OpenViewerID, FExecuteAction::CreateRaw(this, &FButtonCommand::OnClicked_OpenViewer));
}

void FButtonCommand::OnClicked_LoadMesh()
{
	UE_LOG(LogTemp, Error, TEXT("Load Mesh Button is Clicked"));

	FString path;

	IMainFrameModule& mainFrame = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* hwnd = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();


	TArray<FString> fileNames;
	platform->OpenFileDialog(hwnd, "Load Mesh Data", path, "", "Mesh Binary File(*.bin)|*.bin", EFileDialogFlags::None, fileNames);
	if (fileNames.Num() < 1) return;


	FBufferArchive buffer;
	FFileHelper::LoadFileToArray(buffer, *fileNames[0]);
	FMemoryReader reader = FMemoryReader(buffer, true);
	buffer.Seek(0); //FP*


	FBinaryData data;
	reader << data;
	reader.FlushCache();
	reader.Close();


	//GLog->Logf(L"Vertex Count : %d", data.Positions.Num());
	//GLog->Logf(L"Index Count : %d", data.Indices.Num());






#ifdef COPIED_CSV


	FString text;
	for (int32 i = 0; i < data.Positions.Num(); i++)
	{
		text.Append(data.Positions[i].ToString() + ",");
		text.Append(data.Normals[i].ToString() + ",");
		text.Append(data.UVs[i].ToString() + ",");
		text.Append(data.Colors[i].ToString() + "\n");
	}

	FString textFileName = FPaths::GetBaseFilename(fileNames[0], false);
	FString textSaveName = textFileName + "_Copied.csv";

	FFileHelper::SaveStringToFile(text, *textSaveName);

	FString str;
	str.Append(FPaths::GetCleanFilename(textSaveName));
	str.Append(" CSV File Load");
	GLog->Log(str);
#endif

	//-> Spawn Actor
	
	FLevelEditorViewportClient* client = (FLevelEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();

	UWorld* world = GEditor->GetEditorWorldContext().World();
	
	FVector start = client->GetViewLocation();
	FVector end = start + client->GetViewRotation().RotateVector(FVector(100000, 0, 0));
	
	FHitResult hitResult;
	world->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility);
	if (hitResult.bBlockingHit == false) return;


	FTransform transform;

	transform.SetLocation(hitResult.ImpactPoint);

	FVector direction = (end - start).GetSafeNormal();
	FRotator rotation = FRotator(0, direction.Rotation().Yaw, 0);
	transform.SetRotation(FQuat(rotation));

	ACMeshActor_Copied* actor = world->SpawnActorDeferred<ACMeshActor_Copied>
	(
		ACMeshActor_Copied::StaticClass(),
		transform,
		nullptr,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
	);

	actor->SetPositions(data.Positions);
	actor->SetIndices(data.Indices);
	actor->SetNormals(data.Normals);
	actor->SetUVs(data.UVs);
	actor->SetColors(data.Colors);

	actor->FinishSpawning(transform);


}

void FButtonCommand::OnClicked_OpenViewer()
{
	UE_LOG(LogTemp, Error, TEXT("Open Viewer Button is Clicked"));
}