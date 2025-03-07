#pragma once

#include "CoreMinimal.h"

#include "UiTheme.h"
#include "Components/Image.h"
#include "StevesHelperCommon.h"
#include "InputImage.generated.h"

/// A special widget containing an image which populates itself based on an input action / axis and can dynamically
/// change based on the active input method.
UCLASS()
class STEVESUEHELPERS_API UInputImage : public UImage
{
    GENERATED_BODY()

protected:
    /// What type of an input binding this image should look up
    UPROPERTY(EditAnywhere)
    EInputBindingType BindingType;

    /// If BindingType is Action/Axis, the name of it 
    UPROPERTY(EditAnywhere)
    FName ActionOrAxisName;
    
    /// Where there are multiple mappings, which to prefer 
    UPROPERTY(EditAnywhere)
    EInputImageDevicePreference DevicePreference = EInputImageDevicePreference::Auto;
    
    /// If BindingType is Key, the key 
    UPROPERTY(EditAnywhere)
    FKey Key;

    /// The player index for which the input should be looked up 
    UPROPERTY(EditAnywhere)
    int PlayerIndex = 0;

    /// Custom theme to use for this input image set; if not supplied will use UStevesGameSubsystem::DefaultUiTheme
    UPROPERTY(EditAnywhere)   
    UUiTheme* CustomTheme;

    bool bSubbedToInputEvents = false;
public:

    /// Tell this image to display the bound action for the current input method
    UFUNCTION(BlueprintCallable)
    virtual void SetFromAction(FName Name);

    /// Tell this image to display the bound axis for the current input method
    UFUNCTION(BlueprintCallable)
    virtual void SetFromAxis(FName Name);

    /// Tell this image to display a specific key image
    UFUNCTION(BlueprintCallable)
    virtual void SetFromKey(FKey K);

    /// Get the binding type that we'll use to populate the image
    UFUNCTION(BlueprintCallable)
    virtual EInputBindingType GetBindingType() const { return BindingType; }

    /// If BindingType is Action/Axis, get the name of the action or axis to look up the image for
    UFUNCTION(BlueprintCallable)
    virtual FName GetActionOrAxisName() const { return ActionOrAxisName; };

    /// If BindingType is Key, get the key 
    UFUNCTION(BlueprintCallable)
    virtual FKey GetKey() const { return Key; }

    /// Get the custom theme, if any
    virtual UUiTheme* GetCustomTheme() const { return CustomTheme; }
    /// Change the custom theme for this image
    virtual void SetCustomTheme(UUiTheme* Theme);
    
    virtual void BeginDestroy() override;

    virtual void SetVisibility(ESlateVisibility InVisibility) override;
    
protected:

    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void UpdateImage();
        
    UFUNCTION()
    void OnInputModeChanged(int ChangedPlayerIdx, EInputMode InputMode);
    
};
