#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

#include "properties.h"

class QSpinBox;
class QDoubleSpinBox;
class QComboBox;
class QButtonGroup;
class QPushButton;
class QLabel;
class SimulationWidget;
class QGroupBox;
class QFile;


class CentralWidget : public QWidget
{
    Q_OBJECT;
public:
    CentralWidget(QWidget *parent = 0);

private:
    Properties *defaultProperties;

    //transform controls
    QSpinBox *zoom;
    QSpinBox *xRot;
    QSpinBox *yRot;
    QSpinBox *zRot;

    //lattice size controls
    QSpinBox *length;
    QSpinBox *width;
    QSpinBox *height;
    QDoubleSpinBox *spacing;

    //lattice style controls
    QComboBox *color;
    QComboBox *draw;
    QComboBox *guide;

    //input source controls
    QButtonGroup *source;

    //input option controls
    QComboBox *function;
    QPushButton *playAnim;
    QPushButton *resetAnim;
    QLabel *currentFile;
    QPushButton *chooseFile;

    //simulation
    SimulationWidget *simulationWidget; 

    //helper functions for constructor
    void setDefaultProperties();
    QGroupBox *createTransformControls();
    QGroupBox *createSizeControls();
    QGroupBox *createStyleControls();
    QGroupBox *createInputSrcControls();
    QGroupBox *createInputOptControls();
    void setConnections();

signals:
    void ptCloudFileChanged(QFile *p);

public slots:
    void showFileDialog();
};
#endif
