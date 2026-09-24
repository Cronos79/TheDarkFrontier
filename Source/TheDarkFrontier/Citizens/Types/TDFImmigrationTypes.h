// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Citizens/Data/CitizenDataObject.h"
#include "World/Systems/TDFTimeSubsystem.h"
#include "TDFImmigrationTypes.generated.h"

//-----------------------------------------------------------------------------
// Tavern Guest
//-----------------------------------------------------------------------------

USTRUCT(BlueprintType)
struct FTDFTavernGuest
{
	GENERATED_BODY()

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration|Guest")
	FGuid GuestID;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration|Guest")
	FString FirstName;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration|Guest")
	FString LastName;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration|Guest")
	ETDFCitizenGender Gender =
		ETDFCitizenGender::Male;

	//-------------------------------------------------------------------------
	// Family
	//-------------------------------------------------------------------------

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration|Guest")
	FGuid FamilyID;

	//-------------------------------------------------------------------------
	// Birthday
	//-------------------------------------------------------------------------

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration|Guest")
	int32 BirthYear =
		UTDFTimeSubsystem::StartingYear - 18;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration|Guest")
	ETDFSeason BirthSeason =
		ETDFSeason::Spring;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration|Guest")
	int32 BirthDayOfSeason =
		1;

	//-------------------------------------------------------------------------
	// Happiness
	//-------------------------------------------------------------------------

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration|Guest",
		meta = (
			ClampMin = "0.0",
			ClampMax = "100.0"))
	float Happiness =
		50.0f;
};

//-----------------------------------------------------------------------------
// Tavern Guest Group
//-----------------------------------------------------------------------------

USTRUCT(BlueprintType)
struct FTDFTavernGuestGroup
{
	GENERATED_BODY()

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration|Guest Group")
	FGuid GroupID;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration|Guest Group")
	TArray<FTDFTavernGuest>
		Guests;

	//-------------------------------------------------------------------------
	// Arrival
	//
	// Absolute settlement-calendar minute on which this group arrived.
	//
	// This is stable across save/load and allows guest stay duration to be
	// calculated without accumulating elapsed time.
	//-------------------------------------------------------------------------

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration|Guest Group")
	int64 ArrivalAbsoluteMinute =
		INDEX_NONE;

	//-------------------------------------------------------------------------
	// Meals
	//
	// Absolute settlement-calendar minute represented by the most recently
	// processed meal interval.
	//
	// The immigration manager advances this by exact meal intervals rather
	// than setting it directly to the current time. This allows missed meal
	// intervals to be processed correctly if simulation time advances by more
	// than one interval.
	//-------------------------------------------------------------------------

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration|Guest Group")
	int64 LastMealAbsoluteMinute =
		INDEX_NONE;
};

//-----------------------------------------------------------------------------
// Immigration State
//
// Persistent settlement-wide immigration scheduling state.
//-----------------------------------------------------------------------------

USTRUCT(BlueprintType)
struct FTDFImmigrationState
{
	GENERATED_BODY()

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration")
	bool bHasCompletedFirstArrival =
		false;

	//-------------------------------------------------------------------------
	// Scheduled Arrival
	//
	// Exact absolute settlement-calendar minute when the next visitor group
	// is due to arrive.
	//
	// This survives save/load and allows arrivals at daytime hours instead
	// of forcing them to happen on the midnight day boundary.
	//-------------------------------------------------------------------------

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration")
	int64 ScheduledArrivalAbsoluteMinute =
		INDEX_NONE;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration")
	int32 ScheduledArrivalSeasonSerial =
		INDEX_NONE;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Immigration")
	int32 LastArrivalSeasonSerial =
		INDEX_NONE;
};