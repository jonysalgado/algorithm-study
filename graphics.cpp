#ifndef GRAPHCS

#define GRAPHICS
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "pbPlots.hpp"
#include "supportLib.hpp"


using namespace std;


int randomNumber(int maxValue){
    return (rand()%(maxValue+1));
}

string randomWord(int length = randomNumber(100)){
    string word(length, 0);
    for(int i = 0; i < length; i++){
        word[i] = 33 + randomNumber(92);
    }
    return word;
}

void saveImage(string name, vector<double> x, vector<double> y){
    RGBABitmapImageReference* imageref = CreateRGBABitmapImageReference();

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();

    settings->width = 600;
    settings->height = 400;
    settings->scatterPlotSeries = new vector<ScatterPlotSeries*> (1.0);
    settings->scatterPlotSeries->at(0) = GetDefaultScatterPlotSeriesSettings();
    delete settings->scatterPlotSeries->at(0)->xs;
    settings->scatterPlotSeries->at(0)->xs = &x;
    delete settings->scatterPlotSeries->at(0)->ys;
    settings->scatterPlotSeries->at(0)->ys = &y;
    settings->autoBoundaries = true;
	settings->autoPadding = true;
    settings->xLabel = toVector(L"O(n)");
    settings->yLabel = toVector(L"t (s)");

    // DrawScatterPlot(imageref, 600, 400, &x, &y);
    DrawScatterPlotFromSettings(imageref, settings);

    vector<double>* pngdata = ConvertToPNG(imageref->image);

    WriteToFile(pngdata, "../plots/" + name);
    DeleteImage(imageref->image);

}

#endif