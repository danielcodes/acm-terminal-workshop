#include <QtGui>

#include "centralWidget.h"
#include "simulationWidget.h"


CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{
    setDefaultProperties();

    //creates 1st page of controls
    QVBoxLayout *layoutPage1 = new QVBoxLayout();
    layoutPage1->addWidget(this->createTransformControls());
    layoutPage1->addWidget(this->createSizeControls());
    layoutPage1->addWidget(this->createStyleControls());
    layoutPage1->addStretch();
    QWidget *page1 = new QWidget();
    page1->setLayout(layoutPage1);

    //creates 2nd page of controls
    QVBoxLayout *layoutPage2 = new QVBoxLayout();
    layoutPage2->addWidget(this->createInputSrcControls());
    layoutPage2->addWidget(this->createInputOptControls());
    layoutPage2->addStretch();
    QWidget *page2 = new QWidget();
    page2->setLayout(layoutPage2);

    //creates tab widget that holds controls
    QTabWidget *tabWidget = new QTabWidget();
    tabWidget->addTab(page1, "Basic Controls");
    tabWidget->addTab(page2, "Input Controls");

    //creates simulation and adds it to right layout
    QSize simulationSize(500, 500);
    this->simulationWidget =
        new SimulationWidget(this->defaultProperties);
    simulationWidget->setMinimumSize(simulationSize);
    QHBoxLayout *right = new QHBoxLayout();
    right->addWidget(simulationWidget);

    //adds controls and simulation to main layout
    QHBoxLayout *main = new QHBoxLayout();
    main->addWidget(tabWidget, 0);
    main->addLayout(right, 1);
    setLayout(main);

    //sets the signal/slot connections
    this->setConnections();

    //sets window title and icon
    this->setWindowTitle("Qbular");
    QIcon *icon_ptr = new QIcon(":/images/icon.png");
    const QIcon &icon_ref = *icon_ptr;
    this->setWindowIcon(icon_ref);
}//end constructor


void
CentralWidget::setDefaultProperties()
{
    this->defaultProperties = new Properties;

    this->defaultProperties->zoom = 2; 
    this->defaultProperties->xRot = 105;//15; 
    this->defaultProperties->yRot = 180;//60;
    this->defaultProperties->zRot = 80;//0;

    this->defaultProperties->length = 40;
    this->defaultProperties->width = 40;
    this->defaultProperties->height = 40;

    this->defaultProperties->spacing = 3.0;

    this->defaultProperties->color = "green";
    this->defaultProperties->draw = "points";
    this->defaultProperties->guide = "both";

    this->defaultProperties->source = "file";
    this->defaultProperties->function = "sine";
}//end setDefaultProperties


QGroupBox *
CentralWidget::createTransformControls()
{
    const int numOfSpinBoxes = 4, numOfProperties = 4;

    //Stores the text for each label. Each row represents a
    //different label.
    QString labelText[numOfSpinBoxes] = {
        "Zoom:",
        "X Rotation:",
        "Y Rotation:",
        "Z Rotation:"};

    //Stores the values of the spinbox properties. Each row
    //representes a different spinbox. The column 0 is the
    //min value, column 1 is the max value, and column
    //2 is the default value, column 3 is the step size.
    int spinBoxValues[numOfSpinBoxes][numOfProperties] = {
        {1,     400,    this->defaultProperties->zoom,    5},
        {0,     360,    this->defaultProperties->xRot,    5}, 
        {0,     360,    this->defaultProperties->yRot,    5}, 
        {0,     360,    this->defaultProperties->zRot,    5}};

    QGridLayout *grid = new QGridLayout();
    QLabel *label;
    QSlider *slider;
    QSpinBox *spinBoxes[numOfSpinBoxes];

    //for each spin box
    int i;
    for (i = 0; i < numOfSpinBoxes; i++)
    {
        //create label
        label = new QLabel(labelText[i]);
        grid->addWidget(label, i, 0);

        //create slider
        slider = new QSlider(Qt::Horizontal);
        slider->setMinimum(spinBoxValues[i][0]);
        slider->setMaximum(spinBoxValues[i][1]);
        slider->setValue(spinBoxValues[i][2]);
        slider->setSingleStep(spinBoxValues[i][3]);
        grid->addWidget(slider, i, 1);

        //create spin box
        spinBoxes[i] = new QSpinBox();
        spinBoxes[i]->setMinimum(spinBoxValues[i][0]);
        spinBoxes[i]->setMaximum(spinBoxValues[i][1]);
        spinBoxes[i]->setValue(spinBoxValues[i][2]);
        spinBoxes[i]->setSingleStep(spinBoxValues[i][3]);
        grid->addWidget(spinBoxes[i], i, 2);

        //set signal/slot connections
        QObject::connect(slider, SIGNAL(valueChanged(int)),
            spinBoxes[i], SLOT(setValue(int)));
        QObject::connect(spinBoxes[i], SIGNAL(valueChanged(int)),
            slider, SLOT(setValue(int)));
    }

    //stores spin boxes as member variables
    this->zoom = spinBoxes[0];
    this->xRot = spinBoxes[1];
    this->yRot = spinBoxes[2];
    this->zRot = spinBoxes[3];

    QGroupBox *groupBox = new QGroupBox("Transform");
    groupBox->setLayout(grid);
    groupBox->setFixedWidth(400);

    return groupBox;
}//end createTransformControls()


QGroupBox *
CentralWidget::createSizeControls()
{
    const int numOfSpinBoxes = 3, numOfProperties = 4;
    QGridLayout *grid = new QGridLayout();
    QLabel *label;
    QSpinBox *spinBoxes[numOfSpinBoxes];

    //Stores the text for each label. Each row represents a
    //different label.
    QString labelText[numOfSpinBoxes] = {
        "Length:",
        "Width:",
        "Height:"};

    //Stores the values of the spinbox properties.  Each row
    //representes a different spinbox. Column 0 is the min
    //value, column 1 is the max value, column 2 is the
    //default value, and column 3 is the single step amount.
    int spinBoxValues[numOfSpinBoxes][numOfProperties] = {
        {1, 100, this->defaultProperties->length, 1},
        {1, 100, this->defaultProperties->width,  1},
        {1, 100, this->defaultProperties->height, 1}};

    //for each spin box
    int i;
    for (i = 0; i < numOfSpinBoxes; i++)
    {
        //create label
        label = new QLabel(labelText[i]);
        grid->addWidget(label, i % 2, i < 2 ? 0 : 2);

        //create spin box
        spinBoxes[i] = new QSpinBox();
        spinBoxes[i]->setMinimum(spinBoxValues[i][0]);
        spinBoxes[i]->setMaximum(spinBoxValues[i][1]);
        spinBoxes[i]->setValue(spinBoxValues[i][2]);
        spinBoxes[i]->setSingleStep(spinBoxValues[i][3]);
        grid->addWidget(spinBoxes[i], i % 2, i < 2 ? 1 : 3);
    }

    //create 4th label
    label = new QLabel("Spacing:");
    grid->addWidget(label, 1, 2);

    //create 4th spin box
    QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox();
    doubleSpinBox->setMinimum(2.0);
    doubleSpinBox->setMaximum(5.0);
    doubleSpinBox->setValue(this->defaultProperties->spacing);
    doubleSpinBox->setSingleStep(0.5);
    grid->addWidget(doubleSpinBox, 1, 3);

    //stores spin boxes as member variables
    this->length = spinBoxes[0];
    this->width= spinBoxes[1];
    this->height = spinBoxes[2];
    this->spacing = doubleSpinBox;

    QGroupBox *groupBox = new QGroupBox("Lattice Size");
    groupBox->setLayout(grid);
    groupBox->setFixedWidth(400);

    return groupBox;
}//end createSizeControls()


QGroupBox *
CentralWidget::createStyleControls()
{
    QGridLayout *grid = new QGridLayout();

    //create color label
    QLabel *labelColor = new QLabel("Color:");
    grid->addWidget(labelColor, 0, 0);

    //create color combobox
    QComboBox *comboBoxColor = new QComboBox();
    QStringList stringListColor;
    stringListColor << "Red" << "Blue" << "Green" << "White";
    comboBoxColor->insertItems(0, stringListColor);
    grid->addWidget(comboBoxColor, 0, 1);

    //set color combobox default value
    int i;
    for (i = 0; i < stringListColor.size(); i++)
    {
        if (stringListColor.at(i).toLower() == this->defaultProperties->color)
            comboBoxColor->setCurrentIndex(i);
    }

    //create draw label
    QLabel *labelDraw = new QLabel("Draw:");
    grid->addWidget(labelDraw, 1, 0);

    //create draw combobox
    QComboBox *comboBoxDraw = new QComboBox();
    QStringList stringListDraw;
    stringListDraw << "Cubes" << "Points";
    comboBoxDraw->insertItems(0, stringListDraw);
    grid->addWidget(comboBoxDraw, 1, 1);

    //set draw combobox default value
    if (this->defaultProperties->draw == "cubes")
        comboBoxDraw->setCurrentIndex(0);
    else
        comboBoxDraw->setCurrentIndex(1);

    //create guide label
    QLabel *labelGuide = new QLabel("Guidelines:");
    grid->addWidget(labelGuide, 0, 2);

    //create guide combobox
    QComboBox *comboBoxGuide = new QComboBox();
    QStringList stringListGuide;
    stringListGuide << "None" << "Axis" << "Box" << "Both";
    comboBoxGuide->insertItems(0, stringListGuide);
    grid->addWidget(comboBoxGuide, 0, 3);

    //set color combobox default value
    for (i = 0; i < stringListGuide.size(); i++)
    {
        if (stringListGuide.at(i).toLower() == this->defaultProperties->guide)
            comboBoxGuide->setCurrentIndex(i);
    }

    //stores both comboboxes as member variables
    this->color = comboBoxColor;
    this->draw = comboBoxDraw;
    this->guide = comboBoxGuide;

    //create a groupbox to hold labels and comboboxes
    QGroupBox *groupBox = new QGroupBox("Lattice Style");
    groupBox->setLayout(grid);
    groupBox->setFixedWidth(400);

    return groupBox;
}//end createStyleControls()


QGroupBox *
CentralWidget::createInputSrcControls()
{
    const int numOfButtons = 3;
    QString sourceText;

    //stores the text for each label
    QString buttonText[numOfButtons] = { 
        "No input (turn on all LEDSs)",
        "Math function",
        "Point cloud file"};

    QGridLayout *grid = new QGridLayout();
    this->source = new QButtonGroup();
    QRadioButton *button[numOfButtons];

    //for each button
    int i;
    for (i = 0; i < numOfButtons; i++)
    {   
        //creates and adds button
        button[i] = new QRadioButton(buttonText[i]);
        this->source->addButton(button[i]);
        grid->addWidget(button[i], (i % 2), (i > 1));
    }

    //marks default button as checked
    if (this->defaultProperties->source == "none")
        i = 0; 
    else if (this->defaultProperties->source == "function")
        i = 1; 
    else    
        i = 2;
    button[i]->setChecked(true);

    //creates a groupbox to hold controls
    QGroupBox *groupBox = new QGroupBox("Input Sources");
    groupBox->setLayout(grid);
    groupBox->setFixedWidth(400);

    return groupBox;
}//end createInputSrcControls


QGroupBox *
CentralWidget::createInputOptControls()
{
    QGridLayout *top = new QGridLayout();

    //creates function label and combobox
    QLabel *labelFunction = new QLabel("Math Function:");
    top->addWidget(labelFunction, 0, 0);
    this->function = new QComboBox();
    QStringList stringListFunction;
    stringListFunction << "Sine" << "Sphere";
    this->function->insertItems(0, stringListFunction);
    top->addWidget(this->function, 0, 1);

    //sets default value for function combobox
    if (this->defaultProperties->function == "sine")
        this->function->setCurrentIndex(0);
    else
        this->function->setCurrentIndex(1);

    //sets default enable property for function combobox
    //...

    //creates animation buttons
    this->playAnim = new QPushButton("Play Animation");
    this->resetAnim = new QPushButton("Reset Animation");
    top->addWidget(this->playAnim, 1, 0);
    top->addWidget(this->resetAnim, 1, 1);

    //sets default enable property for animation buttons
    //...
 
    QGridLayout *bottom = new QGridLayout();

    //creates current file display
    QLabel *labelCurrentFile = new QLabel("Current File:");
    this->currentFile = new QLabel();
    bottom->addWidget(labelCurrentFile, 0, 0);
    bottom->addWidget(this->currentFile, 0, 1);

    //sets default values for filename label
    this->currentFile->setText("n/a");

    //creates choose file button
    this->chooseFile = new QPushButton("Choose a file...");
    bottom->addWidget(this->chooseFile, 1, 0);

    //sets default enable property for file button
    //...

    //creates horizontal line
    QFrame *line = new QFrame();
    line->setFixedHeight(10);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    //adds top and botton to main layout
    QVBoxLayout *main = new QVBoxLayout();
    main->addLayout(top);
    main->addWidget(line);
    main->addLayout(bottom);
    
    //creates a groupbox to hold controls 
    QGroupBox *groupBox = new QGroupBox("Input Options");
    groupBox->setLayout(main);
    groupBox->setFixedWidth(400);

    return groupBox;
}//end createInputOptControls


void
CentralWidget::setConnections()
{
    //connect zoom spinbox to simulationWidget
    connect(this->zoom, SIGNAL(valueChanged(int)),
        this->simulationWidget, SLOT(setZoom(int)));

    //connect xRot spinbox to centralWidget
    connect(this->xRot, SIGNAL(valueChanged(int)),
        this->simulationWidget, SLOT(setXRot(int)));
    connect(this->simulationWidget, SIGNAL(xRotChanged(int)),
        this->xRot, SLOT(setValue(int)));

    //connect zRot spinbox to simulationWidget
    connect(this->yRot, SIGNAL(valueChanged(int)),
        this->simulationWidget, SLOT(setYRot(int)));
    connect(this->simulationWidget, SIGNAL(yRotChanged(int)),
        this->yRot, SLOT(setValue(int)));

    //connect zRot spinbox to simulationWidget
    connect(this->zRot, SIGNAL(valueChanged(int)),
        this->simulationWidget, SLOT(setZRot(int)));
    connect(this->simulationWidget, SIGNAL(zRotChanged(int)),
        this->zRot, SLOT(setValue(int)));

    //connect size spinboxes to simulationWidget
    connect(this->length, SIGNAL(valueChanged(int)),
        this->simulationWidget, SLOT(setLength(int)));
    connect(this->width, SIGNAL(valueChanged(int)),
        this->simulationWidget, SLOT(setWidth(int)));
    connect(this->height, SIGNAL(valueChanged(int)),
        this->simulationWidget, SLOT(setHeight(int)));

    //connect spacing spinbox to simulationWidget
    connect(this->spacing, SIGNAL(valueChanged(double)),
        this->simulationWidget, SLOT(setSpacing(double)));

    //connect style comboboxes to simulationWidget
    connect(this->color, SIGNAL(currentIndexChanged(const QString &)),
        this->simulationWidget, SLOT(setColor(const QString &)));
    connect(this->draw, SIGNAL(currentIndexChanged(const QString &)),
        this->simulationWidget, SLOT(setDraw(const QString &)));
    connect(this->guide, SIGNAL(currentIndexChanged(const QString &)),
        this->simulationWidget, SLOT(setGuide(const QString &)));

    //connect source button group to simulationWidget
    connect(this->source, SIGNAL(buttonReleased(QAbstractButton *)),
        this->simulationWidget, SLOT(setSource(QAbstractButton *)));

    //connect input controls
    connect(this->function,
        SIGNAL(currentIndexChanged(const QString &)),
        this->simulationWidget, SLOT(setFunction(const QString &)));
    connect(this->chooseFile, SIGNAL(released()),
        this, SLOT(showFileDialog()));
    connect(this, SIGNAL(ptCloudFileChanged(QFile *)),
        this->simulationWidget, SLOT(scanPtCloud(QFile *)));
}//end setConnections


void
CentralWidget::showFileDialog()
{
    QString filename = QFileDialog::getOpenFileName(
        this,
        "Open Point Cloud File",
        QString(),
        "Point Cloud Files (*.xyz)");

    //if a file was chosen
    if (filename != "")
    {
        //displays filename
        QFileInfo *fileInfo = new QFileInfo(filename);

        //if a new file is chosen
        if (this->currentFile->text() != fileInfo->fileName())
        {
            this->currentFile->setText(fileInfo->fileName());

            //emit signal
            QFile *file = new QFile(filename);
            emit ptCloudFileChanged(file);
        }
    }
}//end showFileDialog
