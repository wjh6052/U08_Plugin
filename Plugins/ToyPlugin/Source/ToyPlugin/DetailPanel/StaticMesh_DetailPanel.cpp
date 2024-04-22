#include "StaticMesh_DetailPanel.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "DesktopPlatformModule.h"
#include "Interfaces/IMainFrameModule.h"
#include "Serialization/BufferArchive.h"
#include "Actors/CMeshActor.h"
#include "Misc/FileHelper.h"

TSharedRef<IDetailCustomization> FStaticMesh_DetailPanel::MakeInstance()
{
	return MakeShareable(new FStaticMesh_DetailPanel());
}

void FStaticMesh_DetailPanel::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& catetory = DetailBuilder.EditCategory("AwesomeCategory");

	catetory.AddCustomRow(FText::FromString("Shuffle Material"))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Material Instance"))
	]
	.ValueContent()
	.HAlign(HAlign_Left)
	.MaxDesiredWidth(250)
	[
		SNew(SButton)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)
		.OnClicked(this, &FStaticMesh_DetailPanel::OnClicked_ShuffleMatrial)
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Shuffle"))
		]
	];

	catetory.AddCustomRow(FText::FromString("Save Mesh"))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Save Mesh"))
	]
	.ValueContent()
	.HAlign(HAlign_Left)
	.MaxDesiredWidth(250)
	[
		SNew(SButton)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)
		.OnClicked(this, &FStaticMesh_DetailPanel::OnClicked_SaveMesh)
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Save To Binary File"))
		]
	];

	DetailBuilder.GetObjectsBeingCustomized(Objects);
}

FReply FStaticMesh_DetailPanel::OnClicked_ShuffleMatrial()
{
	ACMeshActor* actor = Cast<ACMeshActor>(Objects[0]);
	if (actor == nullptr) return FReply::Unhandled();

	actor->ShuffleMaterial();

	return FReply::Handled();
}

FReply FStaticMesh_DetailPanel::OnClicked_SaveMesh()
{

	//-------------------------------------------------------------------------
	//Get Mesh Data
	//-------------------------------------------------------------------------
	
	//-> Get Mesh Comp
	ACMeshActor* actor = Cast<ACMeshActor>(Objects[0]);
	UActorComponent* comp = actor->GetComponentByClass(UStaticMeshComponent::StaticClass());
	UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(comp);
	if (meshComp == nullptr) return FReply::Unhandled();


	//-> Get Mesh Asset
	UStaticMesh* meshAsset = meshComp->GetStaticMesh();
	FStaticMeshRenderData* renderData = meshAsset->RenderData.Get();
	if (renderData->LODResources.Num() < 1) return FReply::Unhandled();


	//-> Get Vertices Data
	FStaticMeshLODResources& lod = renderData->LODResources[0];
	
	FPositionVertexBuffer& positionBuffer = lod.VertexBuffers.PositionVertexBuffer;
	FStaticMeshVertexBuffer& meshBuffer = lod.VertexBuffers.StaticMeshVertexBuffer;
	FColorVertexBuffer& colerBuffer = lod.VertexBuffers.ColorVertexBuffer;
	FRawStaticIndexBuffer& indexBuffer = lod.IndexBuffer;

	if(positionBuffer.GetNumVertices() < 1) return FReply::Unhandled();
	if(indexBuffer.GetNumIndices() < 1) return FReply::Unhandled();

	uint32 vertexCount = positionBuffer.GetNumVertices();
	int32 indexCount = indexBuffer.GetNumIndices();

	//GLog->Logf(L"VertexCount : %d", vertexCount);
	//GLog->Logf(L"indexCount : %d", indexCount);


	//-------------------------------------------------------------------------
	//Save File 
	//-------------------------------------------------------------------------

	// -> File Dialog
	FString path;

	IMainFrameModule& mainFrame = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* hwnd = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();

	TArray<FString> fileNames;
	platform->SaveFileDialog(hwnd, "Save Mesh Data", path, "", "Mesh Binary File(*.bin)|*.bin", EFileDialogFlags::None, fileNames);
	if (fileNames.Num() < 1) return FReply::Unhandled();

	//GLog->Log(*fileNames[0]);


	//-> Vertex Data to Struct Data
	FBinaryData data;

	TArray<FColor> colors;
	colerBuffer.GetVertexColors(colors);
	if (colors.Num() < 1)
	{
		for (uint32 i = 0; i < vertexCount; i++)
			colors.Add(FColor::White);
	}

	for (uint32 i = 0; i < vertexCount; i++)
	{
		data.Positions.Add(positionBuffer.VertexPosition(i));
		data.Normals.Add(meshBuffer.VertexTangentZ(i));
		data.UVs.Add(meshBuffer.GetVertexUV(i, 0));
	}
	data.Colors = colors;


	TArray<uint32> indices;
	indexBuffer.GetCopy(indices);
	data.Indices.Insert((int32*)indices.GetData(), indexCount, 0);


	//-> Struct Data to Binary File Archive(HDD)
	FBufferArchive buffer;
	buffer << data;

	FFileHelper::SaveArrayToFile(buffer, *fileNames[0]);
	buffer.FlushCache();
	buffer.Empty();



	FString str;
	str.Append(FPaths::GetCleanFilename(fileNames[0]));
	str.Append(" Binary File Saved");
	GLog->Log(str);


	// -> Struct to Text File(HDD)
	FString text;
	for (int32 i = 0; i < data.Positions.Num(); i++)
	{
		text.Append(data.Positions[i].ToString() + ",");
		text.Append(data.Normals[i].ToString() + ",");
		text.Append(data.UVs[i].ToString() + ",");
		text.Append(data.Colors[i].ToString() + "\n");
	}

	FString textFileName = FPaths::GetBaseFilename(fileNames[0], false);
	FString textSaveName = textFileName + ".csv";

	FFileHelper::SaveStringToFile(text, *textSaveName);

	str = "";
	str.Append(FPaths::GetCleanFilename(textSaveName));
	str.Append(" CSV File Saved");
	GLog->Log(str);


	FFileHelper::SaveStringToFile(text, *textSaveName);



	return FReply::Handled();
}