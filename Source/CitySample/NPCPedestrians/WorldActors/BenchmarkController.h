#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BenchmarkController.generated.h"

UCLASS()
class CITYSAMPLE_API ABenchmarkController : public AActor
{
    GENERATED_BODY()

public:

    ABenchmarkController();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

protected:

    UPROPERTY(EditAnywhere, Category = "Benchmark")
    float WarmupDuration = 30.f;

    UPROPERTY(EditAnywhere, Category = "Benchmark")
    float CaptureDuration = 60.f;

private:
    float _ElapsedTime = 0.f;
    bool _HasTraceStarted = false;
    bool _HasTraceStopped = false;

};
