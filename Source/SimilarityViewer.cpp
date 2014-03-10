/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "SimilarityViewer.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SimilarityViewer::SimilarityViewer (AudioAnalysisController &analysisController)
    : analysisController(analysisController)
{
    addAndMakeVisible (simControlsContainer = new Component());
    simControlsContainer->setName ("simControlsContainer");

    addAndMakeVisible (slider = new Slider ("new slider"));
    slider->setRange (0, 1, 0);
    slider->setSliderStyle (Slider::LinearHorizontal);
    slider->setTextBoxStyle (Slider::TextBoxLeft, true, 40, 20);
    slider->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Threshold")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (calcSimButton = new TextButton ("calcSimButton"));
    calcSimButton->setButtonText (TRANS("Calculate Similarity"));
    calcSimButton->addListener (this);
    calcSimButton->setColour (TextButton::buttonColourId, Colour (0xff97fc74));

    addAndMakeVisible (rmsFeatureToggle = new ToggleButton ("rmsFeatureToggle"));
    rmsFeatureToggle->setButtonText (TRANS("RMS"));
    rmsFeatureToggle->addListener (this);
    rmsFeatureToggle->setToggleState (true, dontSendNotification);

    addAndMakeVisible (sfFeatureToggle = new ToggleButton ("sfFeatureToggle"));
    sfFeatureToggle->setButtonText (TRANS("SF"));
    sfFeatureToggle->addListener (this);
    sfFeatureToggle->setToggleState (true, dontSendNotification);

    addAndMakeVisible (graphContainer = new Component());
    graphContainer->setName ("graphContainer");

    addAndMakeVisible (mfccFeatureToggle = new ToggleButton ("mfccFeatureToggle"));
    mfccFeatureToggle->setButtonText (TRANS("MFCC"));
    mfccFeatureToggle->addListener (this);
    mfccFeatureToggle->setToggleState (true, dontSendNotification);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 300);


    //[Constructor] You can add your own custom stuff here..

    calcSimButton->setVisible(false);

    addActionListener(&analysisController);
    //[/Constructor]
}

SimilarityViewer::~SimilarityViewer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    simControlsContainer = nullptr;
    slider = nullptr;
    label = nullptr;
    calcSimButton = nullptr;
    rmsFeatureToggle = nullptr;
    sfFeatureToggle = nullptr;
    graphContainer = nullptr;
    mfccFeatureToggle = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
//    thumbComponent = nullptr;
    //[/Destructor]
}

//==============================================================================
void SimilarityViewer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..

    drawThreshold(g);
    drawSimilarityFunction(g);

    //[/UserPaint]
}

void SimilarityViewer::resized()
{
    simControlsContainer->setBounds (0, 0, proportionOfWidth (1.0000f), 100);
    slider->setBounds (272, 40, 150, 24);
    label->setBounds (312, 16, 80, 24);
    calcSimButton->setBounds (proportionOfWidth (0.0087f), 16, 150, 24);
    rmsFeatureToggle->setBounds (getWidth() - 132, 16, 50, 24);
    sfFeatureToggle->setBounds (getWidth() - 68, 16, 50, 24);
    graphContainer->setBounds (0, 100, proportionOfWidth (1.0000f), 300);
    mfccFeatureToggle->setBounds (getWidth() - 188, 16, 50, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SimilarityViewer::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider)
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        threshold = slider->getValue();

        repaint();
        //[/UserSliderCode_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void SimilarityViewer::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == calcSimButton)
    {
        //[UserButtonCode_calcSimButton] -- add your button handler code here..
        if(analysisController.isReady()){
            distanceArray = analysisController.calculateDistances();
            repaint();
        }
        else{
            std::cout << "files not set in analysis controller";
        }
        //[/UserButtonCode_calcSimButton]
    }
    else if (buttonThatWasClicked == rmsFeatureToggle)
    {
        //[UserButtonCode_rmsFeatureToggle] -- add your button handler code here..
        //[/UserButtonCode_rmsFeatureToggle]
    }
    else if (buttonThatWasClicked == sfFeatureToggle)
    {
        //[UserButtonCode_sfFeatureToggle] -- add your button handler code here..
        //[/UserButtonCode_sfFeatureToggle]
    }
    else if (buttonThatWasClicked == mfccFeatureToggle)
    {
        //[UserButtonCode_mfccFeatureToggle] -- add your button handler code here..
        //[/UserButtonCode_mfccFeatureToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SimilarityViewer::setDistanceArray(Array<float> newArray){
    distanceArray = newArray;
    repaint();
};

void SimilarityViewer::drawThreshold(Graphics &g){

    g.setColour(Colours::blueviolet);
    g.drawHorizontalLine(graphContainer->getY() + graphContainer->getHeight() - threshold * graphContainer->getHeight(), getX(), getWidth());

}

void SimilarityViewer::drawSimilarityFunction(Graphics &g){

    g.setColour(Colours::green);

    int graphLengthInPixels = getWidth();
    
    int lastXPixel;
    int currentXPixel;
    
    for(int i=0; i<distanceArray.size() - 1; i++){

        int lastXPixel = i;
        int currentXPixel = floor((i+1) * graphLengthInPixels / distanceArray.size());
        
        g.drawLine(lastXPixel, distanceArray[i], currentXPixel, distanceArray[i+1]);
    }
}


void SimilarityViewer::setReadyToCompare(bool ready){
    calcSimButton->setVisible(ready);
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SimilarityViewer" componentName=""
                 parentClasses="public Component, public ActionBroadcaster" constructorParams="AudioAnalysisController &amp;analysisController"
                 variableInitialisers="analysisController(analysisController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="800" initialHeight="300">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="simControlsContainer" id="d7eb2493d0021c3d" memberName="simControlsContainer"
                    virtualName="" explicitFocusOrder="0" pos="0 0 100% 100" class="Component"
                    params=""/>
  <SLIDER name="new slider" id="2ddea841d6d652ab" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="272 40 150 24" min="0" max="1" int="0"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="0"
          textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="4f564f498f058971" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="312 16 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Threshold" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="calcSimButton" id="9ce3f6b1681a8658" memberName="calcSimButton"
              virtualName="" explicitFocusOrder="0" pos="0.873% 16 150 24"
              bgColOff="ff97fc74" buttonText="Calculate Similarity" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="rmsFeatureToggle" id="92a1f05376de0623" memberName="rmsFeatureToggle"
                virtualName="" explicitFocusOrder="0" pos="132R 16 50 24" buttonText="RMS"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="sfFeatureToggle" id="9eb603aec59d0a37" memberName="sfFeatureToggle"
                virtualName="" explicitFocusOrder="0" pos="68R 16 50 24" buttonText="SF"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <GENERICCOMPONENT name="graphContainer" id="a6f81aed259b1d6e" memberName="graphContainer"
                    virtualName="" explicitFocusOrder="0" pos="0 100 100% 300" class="Component"
                    params=""/>
  <TOGGLEBUTTON name="mfccFeatureToggle" id="f946313658ff3956" memberName="mfccFeatureToggle"
                virtualName="" explicitFocusOrder="0" pos="188R 16 50 24" buttonText="MFCC"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]