// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WorldPartition/WorldPartitionBuilder.h"
#include "CustomWorldPartitionNavigationBuilder.generated.h"

/**
 * 
 */
UCLASS()
class WORLDPARTITIONCUSTOMBUILDER_API UCustomWorldPartitionNavigationBuilder : public UWorldPartitionBuilder
{
	GENERATED_UCLASS_BODY()

public:
	// UWorldPartitionBuilder interface begin
	virtual bool RequiresCommandletRendering() const override { return false; }
	virtual ELoadingMode GetLoadingMode() const override { return ELoadingMode::IterativeCells2D; }

protected:
	virtual bool PreRun(UWorld* World, FPackageSourceControlHelper& PackageHelper) override;
	virtual bool RunInternal(UWorld* World, const FCellInfo& InCellInfo, FPackageSourceControlHelper& PackageHelper) override;
	virtual bool PostRun(UWorld* World, FPackageSourceControlHelper& PackageHelper, const bool bInRunSuccess) override;
	// UWorldPartitionBuilder interface end

	bool GenerateNavigationData(UWorldPartition* WorldPartition, const FBox& LoadedBounds, const FBox& GeneratingBounds) const;

	bool SavePackages(const TArray<UPackage*>& PackagesToSave) const;
	bool DeletePackages(const FPackageSourceControlHelper& PackageHelper, const TArray<UPackage*>& PackagesToDelete) const;

	bool bCleanBuilderPackages = false;

	TMap<FString, int32> AddedPackagesToSubmitMap;
	TArray<FString> AddedPackagesToSubmit;
	TArray<FString> DeletedPackagesToSubmit;
};
