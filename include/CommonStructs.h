#ifndef COMMONSTRUCTS_H
#define COMMONSTRUCTS_H

#include <QString>
#include <QDir>
#include <QFileInfo>

#include <iostream>

#define GUI_DEBUG_FLAG

#ifdef GUI_DEBUG_FLAG
    #define GUI_DEBUG(x) std::cout << x << std::endl;
#else
    #define GUI_DEBUG(x) {}
#endif

//namespace SpaceGUI{

static QStringList TableHeaders{"File", "Color", "LLR", "Quality", "Path"};

enum class ColorPrediction{
    Red = 0,
    Blue
};

struct TableData{
    TableData(const bool& isValid_ = true) : isValid(isValid_)
    {

    }
    QFileInfo fileName;
    ColorPrediction colorPrediction;
    float LLR;
    float reliability;
    QDir path;
    bool isValid;
};



#endif // COMMONSTRUCTS_H
