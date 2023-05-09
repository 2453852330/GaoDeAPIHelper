// Fill out your copyright notice in the Description page of Project Settings.


#include "GaoDe.h"

#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

// Sets default values
AGaoDe::AGaoDe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGaoDe::BeginPlay()
{
	Super::BeginPlay();
	LoadCityInfoOnBegin();
}

void AGaoDe::QueryWeather(FString CityCode, EWeatherQueryType Type)
{
	TSharedRef<IHttpRequest,ESPMode::ThreadSafe> HttpRequest =	FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("Get");
	HttpRequest->SetHeader("Connection","keep-alive");
	HttpRequest->SetHeader("Accept","*/*");
	HttpRequest->SetHeader("Accept-Encoding","gzip, deflate, br");
	HttpRequest->SetHeader("User-Agent","Meta Verse Query");
	
	FString Url = TEXT("https://restapi.amap.com/v3/weather/weatherInfo?");
	Url+=TEXT("key=")+WeatherKey+TEXT("&");
	Url+=TEXT("city=")+CityCode+TEXT("&");
	Url+=TEXT("extensions=")+GetWeatherTypeName(Type)+TEXT("&");
	Url+=TEXT("output=json");
	UE_LOG(LogTemp,Warning,TEXT("url:%s"),*Url);
	HttpRequest->SetURL(Url);
	HttpRequest->OnProcessRequestComplete().BindUObject(this,&AGaoDe::OnWeatherQueryFinish);
	HttpRequest->ProcessRequest();
}



// ip
void AGaoDe::QueryIp(FString Ip)
{
	TSharedRef<IHttpRequest,ESPMode::ThreadSafe> HttpRequest =	FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("Get");
	HttpRequest->SetHeader("Connection","keep-alive");
	HttpRequest->SetHeader("Accept","*/*");
	HttpRequest->SetHeader("Accept-Encoding","gzip, deflate, br");
	HttpRequest->SetHeader("User-Agent","Meta Verse Query");
	FString Url = TEXT("https://restapi.amap.com/v3/ip?");
	Url+=TEXT("key=")+WeatherKey+TEXT("&");
	Url+=TEXT("ip=")+Ip;
	UE_LOG(LogTemp,Warning,TEXT("url:%s"),*Url);
	HttpRequest->SetURL(Url);
	HttpRequest->OnProcessRequestComplete().BindUObject(this,&AGaoDe::OnIpQueryFinish);
	HttpRequest->ProcessRequest();
}




// private
void AGaoDe::OnWeatherQueryFinish(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		FString Result = Response->GetContentAsString();
		UE_LOG(LogTemp,Warning,TEXT("%s"),*Result);
		if (Request->GetURL().Find("base") != INDEX_NONE)
		{
			// is base data
			TSharedPtr<FJsonObject> RootObject;
			TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
			if (FJsonSerializer::Deserialize(JsonReader,RootObject))
			{
				FString status = RootObject->GetStringField("status");
				if (status != TEXT("1"))
				{
					BPReceiveErrorInfo(TEXT("Query Weather Failed"));
					return;
				}
				
				const TArray<TSharedPtr<FJsonValue>> lives_data = RootObject->GetArrayField("lives");
				if (lives_data.Num() <= 0)
				{
					BPReceiveErrorInfo(TEXT("Query Weather Failed"));
					return;
				}
				TSharedPtr<FJsonObject> live_obj = lives_data[0]->AsObject();
				FWeatherBase WeatherBase;
				WeatherBase.province = live_obj->GetStringField("province");
				WeatherBase.city = live_obj->GetStringField("city");
				WeatherBase.adcode = live_obj->GetStringField("adcode");
				WeatherBase.weather = live_obj->GetStringField("weather");
				WeatherBase.temperature = live_obj->GetStringField("temperature");
				WeatherBase.winddirection = live_obj->GetStringField("winddirection");
				WeatherBase.windpower = live_obj->GetStringField("windpower");
				WeatherBase.humidity = live_obj->GetStringField("humidity");
				WeatherBase.reporttime = live_obj->GetStringField("reporttime");
				BPQueryWeatherFinishBase(WeatherBase);
			}
		}
		else
		{
			// is all data
			TSharedPtr<FJsonObject> RootObject;
			TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
			if (FJsonSerializer::Deserialize(JsonReader,RootObject))
			{
				FString status = RootObject->GetStringField("status");
				if (status != TEXT("1"))
				{
					BPReceiveErrorInfo(TEXT("Query Weather Failed"));
					return;
				}
				const TArray<TSharedPtr<FJsonValue>> forecasts_data = RootObject->GetArrayField("forecasts");
				if (forecasts_data.Num() <= 0)
				{
					BPReceiveErrorInfo(TEXT("Query Weather Failed"));
					return;
				}
				TSharedPtr<FJsonObject> forecasts_obj = forecasts_data[0]->AsObject();
				FWeatherAll WeatherAll;
				WeatherAll.city = forecasts_obj->GetStringField("city");
				WeatherAll.adcode = forecasts_obj->GetStringField("adcode");
				WeatherAll.province = forecasts_obj->GetStringField("province");
				WeatherAll.reporttime = forecasts_obj->GetStringField("reporttime");
				const TArray<TSharedPtr<FJsonValue>> casts_data = forecasts_obj->GetArrayField("casts");
				for (TSharedPtr<FJsonValue>  it : casts_data)
				{
					TSharedPtr<FJsonObject> obj = it->AsObject();
					FWeatherCast cast;
					cast.date = obj->GetStringField("date");
					cast.week = obj->GetStringField("week");
					cast.dayweather = obj->GetStringField("dayweather");
					cast.nightweather = obj->GetStringField("nightweather");
					cast.daytemp = obj->GetStringField("daytemp");
					cast.nighttemp = obj->GetStringField("nighttemp");
					cast.daywind = obj->GetStringField("daywind");
					cast.nightwind = obj->GetStringField("nightwind");
					cast.daypower = obj->GetStringField("daypower");
					cast.nightpower = obj->GetStringField("nightpower");
					WeatherAll.casts.Add(cast);
				}
				BPQueryWeatherFinishAll(WeatherAll);
			}
		}
	}
	else
	{
		BPReceiveErrorInfo(TEXT("Query Weather Failed"));
	}
}

void AGaoDe::OnIpQueryFinish(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		FString result = Response->GetContentAsString();
		// UE_LOG(LogTemp,Warning,TEXT("%s"),*result);
		TSharedPtr<FJsonObject> RootObj;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(result);
		if (FJsonSerializer::Deserialize(JsonReader,RootObj))
		{
			FString status = RootObj->GetStringField("status");
			FString info = RootObj->GetStringField("info");
			if (status == TEXT("1") && info.Compare(TEXT("ok"),ESearchCase::IgnoreCase) == 0)
			{
				FIpType ipinfo;
				ipinfo.infocode = RootObj->GetStringField("infocode");
				ipinfo.province = RootObj->GetStringField("province");
				ipinfo.city = RootObj->GetStringField("city");
				ipinfo.adcode = RootObj->GetStringField("adcode");
				ipinfo.rectangle = RootObj->GetStringField("rectangle");
				BPQueryIpFinish(ipinfo);
			}
			else
			{
				BPReceiveErrorInfo(TEXT("Query Ip Failed : Get Result Error"));
			}
		}
		else
		{
			BPReceiveErrorInfo(TEXT("Query Ip Failed : Json Read Error"));
		}
	}
	else
	{
		BPReceiveErrorInfo(TEXT("Query Ip Failed : Net Error"));
	}
}

void AGaoDe::LoadCityInfoOnBegin()
{
	FString FilePath = FPaths::ProjectPluginsDir();
	FilePath += TEXT("GaoDeAPIHelper/Files/AMap_adcode_citycode_20210406.csv");
	UE_LOG(LogTemp,Warning,TEXT("%s"),*FilePath);
	if (FPaths::FileExists(FilePath))
	{
		TArray<FString> CityInfo;
		if (FFileHelper::LoadFileToStringArray(CityInfo,*FilePath))
		{
			UE_LOG(LogTemp,Warning,TEXT("Load %d Line Data"),CityInfo.Num());
			for (int32 i = 1; i < CityInfo.Num();i++)
			{
				TArray<FString> CityItem;
				CityInfo[i].ParseIntoArray(CityItem,TEXT(","),false);
				if (CityItem.Num() == 3)
				{
					FCityCodeType CityCodeInfo(CityItem);
					CityList.Add(CityCodeInfo);
				}
			}
			UE_LOG(LogTemp,Warning,TEXT("Load %d City Info"),CityList.Num());
		}
	}
	
}

const TArray<FCityCodeType>& AGaoDe::GetCityList() const
{
	return CityList;
}

// helper 
FString AGaoDe::GetWeatherTypeName(EWeatherQueryType Type)
{
	return Type==EBase?TEXT("base"):TEXT("all");
}
