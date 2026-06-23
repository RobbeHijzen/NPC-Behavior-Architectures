#include "BenchmarkController.h"
#include "ProfilingDebugging/TraceAuxiliary.h"
#include "Misc/Paths.h"
#include "HAL/PlatformTime.h"
#include "Kismet/GameplayStatics.h"
#include "PedestrianSpawner.h"
#include "ProfilingDebugging/CsvProfiler.h"

ABenchmarkController::ABenchmarkController()
{
    PrimaryActorTick.bCanEverTick = true;

}

void ABenchmarkController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("BenchmarkController: Warmup started. Trace begins in %.0f seconds."), WarmupDuration);

}

void ABenchmarkController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (_HasTraceStopped) return;

    _ElapsedTime += DeltaTime;

    if (!_HasTraceStarted && _ElapsedTime >= WarmupDuration)
    {
        _HasTraceStarted = true;

#if UE_TRACE_ENABLED

        auto spawner = Cast<APedestrianSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), APedestrianSpawner::StaticClass()));
        if (!spawner) return;

        FString benchmarkName{ spawner->GetSpawnClassName() + "_" + FString::FromInt(spawner->GetSpawnAmount()) };

        FString TraceFileName = FPaths::ProfilingDir() / benchmarkName;

        FTraceAuxiliary::FOptions Options;
        Options.bExcludeTail = true;

        FTraceAuxiliary::Start(
            FTraceAuxiliary::EConnectionType::File,
            *TraceFileName,
            TEXT("cpu,frame,bookmark"),
            &Options
        );
#endif

        UE_LOG(LogTemp, Display, TEXT("BenchmarkController: Warmup complete. Trace started. Recording for %.0f seconds."), CaptureDuration);
    }

    if (_HasTraceStarted && !_HasTraceStopped && _ElapsedTime >= WarmupDuration + CaptureDuration)
    {
        _HasTraceStopped = true;

#if UE_TRACE_ENABLED
        FTraceAuxiliary::Stop();
#endif

        UE_LOG(LogTemp, Display, TEXT("BenchmarkController: Trace complete. Quitting."));

        //FGenericPlatformMisc::RequestExit(false);
    }
}

