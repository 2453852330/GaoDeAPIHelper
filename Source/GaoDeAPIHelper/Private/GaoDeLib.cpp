// Fill out your copyright notice in the Description page of Project Settings.


#include "GaoDeLib.h"

FString UGaoDeLib::WeatherBaseToString(const FWeatherBase& Weather)
{
	FString result;
	result += TEXT("province:")+Weather.province+TEXT(" | ");
	result += TEXT("city:")+Weather.city+TEXT(" | ");
	result += TEXT("adcode:")+Weather.adcode+TEXT(" | ");
	result += TEXT("weather:")+Weather.weather+TEXT(" | ");
	result += TEXT("temperature:")+Weather.temperature+TEXT(" | ");
	result += TEXT("winddirection:")+Weather.winddirection+TEXT(" | ");
	result += TEXT("windpower:")+Weather.windpower+TEXT(" | ");
	result += TEXT("humidity:")+Weather.humidity+TEXT(" | ");
	result += TEXT("reporttime:")+Weather.reporttime;
	return result;
}

FString UGaoDeLib::IpToString(const FIpType& Ip)
{
	FString result;
	result += TEXT("") + Ip.adcode + TEXT(" | ");
	result += TEXT("") + Ip.infocode + TEXT(" | ");
	result += TEXT("") + Ip.province + TEXT(" | ");
	result += TEXT("") + Ip.city + TEXT(" | ");
	result += TEXT("") + Ip.rectangle;
	return result;
}
