#include "CDataAssetFactory.h"
#include "CDataAsset.h"



UCDataAssetFactory::UCDataAssetFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UCDataAsset::StaticClass();
}


UObject* UCDataAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	UE_LOG(LogTemp, Error, TEXT("%s is created as uasset file"), *InParent->GetName());

	return NewObject<UCDataAsset>(InParent, InClass,InName, Flags);
}
