// Fill out your copyright notice in the Description page of Project Settings.

#include "Botanalytics_Alpha.h"
#include "MusicCueUnitTest.h"

MusicCueUnitTest::MusicCueUnitTest()
{
}

MusicCueUnitTest::~MusicCueUnitTest()
{
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTestMusicCuePlayback, "Game.UnitTests.MusicCuePlayback",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

    bool FTestMusicCuePlayback::RunTest(const FString& Parameters)
{
    // Access the current game world
    UWorld* World = GEngine->GetWorldContexts()[0].World();
    if (!World)
    {
        AddError(TEXT("Failed to get the game world."));
        return false;
    }

    // Create an Audio Component
    UAudioComponent* AudioComponent = NewObject<UAudioComponent>(World);
    AudioComponent->RegisterComponent();

    // Load the SoundWave asset
    USoundWave* MusicCue = LoadObject<USoundWave>(nullptr, TEXT("/Game/Songs/Wild_Marionberries.Wild_Marionberries"));
    if (!MusicCue)
    {
        AddError(TEXT("Failed to load the SoundWave asset."));
        return false;
    }

    // Attach the SoundWave to the Audio Component
    AudioComponent->SetSound(MusicCue);

    // Start playing the music cue
    AudioComponent->Play();

    // Small delay to let playback initiate
    FPlatformProcess::Sleep(0.1f);

    // Check if the Audio Component is playing
    bool bIsPlaying = AudioComponent->IsPlaying();
    TestTrue(TEXT("Music cue should be playing"), bIsPlaying);

	// Stop the music cue
