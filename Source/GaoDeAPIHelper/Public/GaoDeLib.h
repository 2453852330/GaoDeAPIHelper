// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GaoDeType.h"
#include "GaoDeLib.generated.h"

/**
 * 
 */
UCLASS()
class GAODEAPIHELPER_API UGaoDeLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,BlueprintPure)
	static FString WeatherBaseToString(const FWeatherBase & Weather);
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	static FString IpToString(const FIpType & Ip);
};
