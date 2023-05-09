#pragma once

#include "GaoDeType.generated.h"

UENUM()
enum EWeatherQueryType
{
	EBase,EAll
};

USTRUCT(BlueprintType)
struct FWeatherBase
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString province;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString city;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString adcode;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString weather;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString temperature;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString winddirection;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString windpower;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString humidity;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString reporttime;
};

USTRUCT(BlueprintType)
struct FWeatherCast
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString date;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString week;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString dayweather;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString nightweather;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString daytemp;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString nighttemp;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString daywind;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString nightwind;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString daypower;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString nightpower;
};

USTRUCT(BlueprintType)
struct FWeatherAll
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString province;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString city;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString adcode;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString reporttime;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<FWeatherCast> casts;
};

USTRUCT(BlueprintType)
struct FIpType
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString infocode;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString province;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString city;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString adcode;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString rectangle;
};

USTRUCT(BlueprintType)
struct FCityCodeType
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString cityname;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString adcode;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString citycode;

	FCityCodeType(){}
	FCityCodeType(const TArray<FString> & InInfo)
	{
		cityname = InInfo[0];
		adcode = InInfo[1];
		citycode = InInfo[2];
	}
};
