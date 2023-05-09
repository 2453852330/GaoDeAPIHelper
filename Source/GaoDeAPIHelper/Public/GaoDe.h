// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "GaoDeType.h"
#include "GaoDe.generated.h"




UCLASS()
class GAODEAPIHELPER_API AGaoDe : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGaoDe();
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	FString WeatherKey;

	// weather
	UFUNCTION(BlueprintCallable)
	void QueryWeather(FString CityCode,EWeatherQueryType Type);
	UFUNCTION(BlueprintImplementableEvent)
	void BPReceiveErrorInfo(const FString & ErrorInfo);
	UFUNCTION(BlueprintImplementableEvent)
	void BPQueryWeatherFinishBase(const FWeatherBase & Weather);
	UFUNCTION(BlueprintImplementableEvent)
	void BPQueryWeatherFinishAll(const FWeatherAll & Weather);
	UFUNCTION(BlueprintImplementableEvent)
	void BPQueryIpFinish(const FIpType & IpInfo);
	// ip
	UFUNCTION(BlueprintCallable)
	void QueryIp(FString Ip);
	// get city info
	UFUNCTION(BlueprintCallable)
	const TArray<FCityCodeType>& GetCityList() const;
private:
	FString GetWeatherTypeName(EWeatherQueryType Type);
	void OnWeatherQueryFinish(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void OnIpQueryFinish(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void LoadCityInfoOnBegin();
	
	UPROPERTY()
	TArray<FCityCodeType> CityList;
};
