#pragma once
#include <JuceHeader.h>

class Synth_LookAndFeel : public juce::LookAndFeel_V4
{
public:
    
    Synth_LookAndFeel()
    {
        //store image assets
        mSliderImage = juce::ImageCache::getFromMemory(BinaryData::knob_png,
                                                       BinaryData::knob_pngSize);
    }
    
    virtual ~Synth_LookAndFeel() {};
    
    //SLIDERS
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider& slider) override
    {
        const int numFrames = mSliderImage.getHeight() / mSliderImage.getWidth();
        const int frameIndex = (int)std::ceil(sliderPosProportional * (numFrames - 1));
        
        const float radius = fmin(width*0.5, height*0.5);
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        
        g.drawImage(mSliderImage,
                    rx,
                    ry,
                    2*radius,
                    2*radius,
                    0,
                    frameIndex*mSliderImage.getWidth(),
                    mSliderImage.getWidth(),
                    mSliderImage.getWidth());
    }
    
private:
    
    juce::Image mSliderImage;

};
